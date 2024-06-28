#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <iterator>
#include <map>
#include <numeric> // для accumulate
using namespace std;



// 1.1 Завдання на лабораторну роботу
// Створити контейнер об'єктів класів, реалізованих в лабораторній 
// роботі 1 (студентів, гуртожитків, викладачів і т.д.) Контейнер реалізувати 
// як вектор. Перетворити класи для вирішення даного завдання

// ВАРІАНТ 7
// Необхідні завдання такі:
// 1. забезпечити для контейнера можливість зчитування з файлу і
// запису в файл з використанням ітераторів потоків (за бажанням).
// 2. забезпечити для контейнера сортування за назвою групи, а також 
// сортування за середнім балом для всіх студентів.
// 3. винести в окремий вектор всі групи, починаючи з групи, число 
// студентів якої більше 4
// 4. зберегти всі імена студентів з вектора кроку 3 в новому векторі.
// 5. Визначити число студентів з іменами , які йдуть в алфавітному
// порядку за заданим в векторі, отриманому на кроці 4.
// 6. знайти середній бал для всіх груп.



class Student {
public:
    string name;
    string group;
    double averageGrade;

    Student(string n = "", string g = "", double ag = 0.0) : name(n), group(g), averageGrade(ag) {}

    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    friend std::istream& operator>>(std::istream& is, Student& student);
};



std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << student.name << " " << student.group << " " << student.averageGrade;
        return os;
}

std::istream& operator>>(std::istream& is, Student& student) {
        is >> student.name >> student.group >> student.averageGrade;
        return is;
}


// Функция readFromFile считывает данные о студентах из файла и сохраняет их в векторе
void readFromFile(const std::string& filename, std::vector<Student>& students) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for reading" << endl;
        return;
    }
    Student temp;

    while (file >> temp) {
        students.push_back(temp);
    }
    file.close();
}


// Функция writeToFile записывает содержимое вектора студентов в файл с заданным именем
void writeToFile(const std::string& filename, const std::vector<Student>& students) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for writing" << endl;
        return;
    }
    copy(students.begin(), students.end(), ostream_iterator<Student>(file, "\n"));
    file.close();
}






// 2. забезпечити для контейнера сортування за назвою групи, а також сортування за середнім балом для всіх студентів.
void sortByGroup(vector<Student>& students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.group < b.group;
    });
}

void sortByAverageGrade(vector<Student>& students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.averageGrade < b.averageGrade;
    });
}



// 3. винести в окремий вектор всі групи, починаючи з групи, число студентів якої більше 4
vector<string> extractGroupsWithMoreThanNStudents(const vector<Student>& students, int n) {
    map<string, int> groupCounts;
    for (const auto& student : students) {
        groupCounts[student.group]++;
    }

    vector<string> groups;
    for (const auto& pair : groupCounts) {
        if (pair.second > n) {
            groups.push_back(pair.first);
        }
    }
    return groups;
}


 // 4. зберегти всі імена студентів з вектора кроку 3 в новому векторі
vector<string> extractStudentNamesFromGroups(const vector<Student>& students, const vector<string>& groups) {
    vector<string> names;
    for (const auto& student : students) {
        if (find(groups.begin(), groups.end(), student.group) != groups.end()) {
            names.push_back(student.name);
        }
    }
    return names;
}




// 5. Визначити число студентів з іменами , які йдуть в алфавітному порядку за заданим в векторі, отриманому на кроці 4
int countStudentsWithAlphabeticalNames(const vector<string>& studentNames ) {
    if (is_sorted(studentNames.begin(), studentNames.end())) {
        return studentNames.size();
    }
    return 0;
}



// 6. знайти середній бал для всіх груп
void calculateAverageGrades(const vector<Student>& students, map<string, double>& groupAverageGrades) {
    map<string, vector<double>> groupGrades;

    // Collect grades for each group
    for (const auto& student : students) {
        groupGrades[student.group].push_back(student.averageGrade);
    }

    // Calculate average grade for each group
    for (const auto& pair : groupGrades) {
        double sum = accumulate(pair.second.begin(), pair.second.end(), 0.0);
        groupAverageGrades[pair.first] = sum / pair.second.size();
    }
}

int main() {



    // std::vector < Student > students;

    // Student student("John",  "Computer Science", 20);

    // // Додавання кількох студентів вручну
    // students.push_back( student );
    // students.push_back( Student ("Alice",  "Mathematics", 22  ) );

    // // Запис студентів у файл
    // writeToFile("students.txt", students);

    // // Очистка вектора перед зчитуванням з файлу
    // students.clear();

    // // Зчитування студентів з файлу
    // readFromFile("students.txt", students);

    // // Виведення зчитаних студентів
    // for (const auto& student : students) {
    //     std::cout << student << std::endl;
    // }



    vector < Student > students = {
        {"Alice", "CS101", 3.5},
        {"Bob", "CS102", 3.7},
        {"Charlie", "CS101", 3.9},
        {"Dave", "CS101", 2.9},
        {"Eve", "CS102", 3.8},
        {"Frank", "CS101", 3.6},
        {"Grace", "CS103", 3.1}
    };

    writeToFile( "students.txt", students);

    vector< Student > loadedStudents;
    readFromFile( "students.txt", loadedStudents );

    cout << "Students loaded from file:" << endl;
    for (const auto& student : loadedStudents) {
        cout << student << endl;
    }






    sortByGroup(loadedStudents);
    cout << "\nStudents sorted by group:" << endl;
    for (const auto& student : loadedStudents) {
        cout << student << endl;
    }

    sortByAverageGrade(loadedStudents);
    cout << "\nStudents sorted by average grade:" << endl;
    for (const auto& student : loadedStudents) {
        cout << student << endl;
    }



    vector<string> groups = extractGroupsWithMoreThanNStudents(loadedStudents, 1);
    cout << "\nGroups with more than 4 students:" << endl;
    for (const auto& group : groups) {
        cout << group << endl;
    }



    // 4. зберегти всі імена студентів з вектора кроку 3 в новому векторі
    vector<string> studentNames = extractStudentNamesFromGroups(loadedStudents, groups);
    cout << "\nStudent names from groups with more than 4 students:" << endl;
    for (const auto& name : studentNames) {
        cout << name << endl;
    }



   


    // 5. Визначити число студентів з іменами , які йдуть в алфавітному порядку за заданим в векторі, отриманому на кроці 4.
    int alphabeticalCount = countStudentsWithAlphabeticalNames(studentNames);
    cout << "\nNumber of students with names in alphabetical order: " << alphabeticalCount << endl;



    // знайти середній бал для всіх груп
    map<string, double> groupAverageGrades;
    calculateAverageGrades(loadedStudents, groupAverageGrades);
    cout << "\nAverage grades for each group:" << endl;
    for (const auto& pair : groupAverageGrades) {
        cout << "Group " << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
