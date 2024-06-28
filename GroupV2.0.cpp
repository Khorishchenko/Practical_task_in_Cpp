#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;



//  створений масив об'єктів класу за допомогою контейнеру vector;
// - заповнення вектору інформацією (не менше 10 об'єктів);
// - реалізоване меню користувача для роботи з інформацією. Меню має передбачати вибір/введення команд (не менше 5 команд) користувачем із подальшим відображенням на 
// екрані результату виконання;
// - збереження остаточного вмісту вектора у текстовому файлі, кожен рідок - інформація про окремий об'єкт вектора.
// Приклади команд, які можуть бути реалізовані: додавання елемента вектора, видалення елемента вектора, пошук елемента по певному критерію, підрахунок середнього 
// значення по певному параметру, 
// відображення вмісту вектора, сортування вмісту вектору за певним критерієм тощо



struct Student
{
    string Name;
    string Surname;
    double AverageG;
};

struct Faculty{
    string name;
    string profile;

    Faculty() {}

    Faculty( std::string NameFaculty, std::string Profile )
    {
        name = NameFaculty;
        profile = Profile;
    }
};

class StudentGroup 
{
    Student *ListStudents;
    string  GroupName;
    Faculty Facultet;
    int     size;
public:
    StudentGroup();
    StudentGroup ( Faculty obj, string GroupName );
    ~StudentGroup();
    StudentGroup(const StudentGroup& other); // Конструктор копіювання
    void printNameGroupAndFaculty (); /////////////// #1
    void AverageGradeIdenticalStudentsName ( string StudentName ); //////////// #3
    bool belongsToFaculty(const string& facultyName) const; // Метод, що перевіряє, чи належить група до факультету з заданою назвою \\\\\\\\\\\\\\\\\\ #2
    void addStudent(const Student& student); // Метод для прийому нового студента в групу       \\\\\\\\\\\\\\\\\\ #4
    void deleteStudent(const Student& studentName); //////////// #5
    void FindStudentAboveAverage (); //////////// #6
    void AverageInputStudent  ( const string  InputStudent ); //////////// #7
    void Print();

    // Перевантаження оператора виведення <<
    friend ostream& operator<<(ostream& os, const StudentGroup& group);
    StudentGroup operator+(const StudentGroup& other) const; // Перевантажений оператор +
};

// StudentGroup::StudentGroup() : Facultet("no name", "no name"),  GroupName("no name"), ListStudents(nullptr), size(0) {}

StudentGroup::StudentGroup ( Faculty obj, string GroupName )
{
    Facultet.name = obj.name;
    Facultet.profile = obj.profile;
    this->GroupName = GroupName;

    ListStudents = nullptr;
    size = 0;
}


// Реалізація конструктора копіювання
StudentGroup::StudentGroup(const StudentGroup& other) {
    this->Facultet = other.Facultet;
    this->GroupName = other.GroupName;
    this->size = other.size;

    if (size > 0) {
        this->ListStudents = new Student[size];
        for (int i = 0; i < size; ++i) {
            this->ListStudents[i] = other.ListStudents[i];
        }
    } else {
        this->ListStudents = nullptr;
    }
}

void StudentGroup::printNameGroupAndFaculty() /////////////// #1
{
    cout << "Group : " << GroupName << endl;
    cout << "Faculty : " << Facultet.name << endl << "Facultet Profile: " << Facultet.profile << endl;
}

void StudentGroup::AverageGradeIdenticalStudentsName(string StudentName) //////////// #3
{
    int Sum = 0;
    int Counter = 0;
    int Average = 0;

    for (int n = 0; n < size; n++)
    {
        if (StudentName == ListStudents[n].Name)
        {
            Sum = Sum + ListStudents[n].AverageG;
            Counter++;
        }
    }

    if (Counter < 1)
    {
        cout << "Students with name " << StudentName << " not found.";
    }
    else
    {
        Average = Sum / Counter;
        cout << "Average grade : " << Average << endl;
    }
}

bool StudentGroup::belongsToFaculty(const string& facultyName) const
{
    return ( Facultet.name == facultyName );
}

void StudentGroup::addStudent( const Student& student )
{
    Student* newStudents = new Student[size + 1];
    if (size > 0)
    {
        for (int i = 0; i < size; ++i)
        {
            newStudents[i] = ListStudents[i];
        }
        delete[] ListStudents;
    }
    newStudents[size] = student;
    ListStudents = newStudents;
    size++;
}

void StudentGroup::deleteStudent(const Student& studentName)
{
    int index = -1;
    for (int i = 0; i < size; ++i)
    {
        if (ListStudents[i].Name == studentName.Name)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        Student* newStudents = new Student[size - 1];
        for (int i = 0, j = 0; i < size; ++i)
        {
            if ( i != index )
            {
                newStudents[j++] = ListStudents[i];
            }
        }
        delete[] ListStudents;
        ListStudents = newStudents;
        --size;
        cout << "Student \'" << studentName.Name << "\' buv inclusions from the group." << endl;
    }
    else
    {
        cout << "Студент " << studentName.Name << " не знайдений у групі." << endl;
    }
}

void StudentGroup::Print()
{
    std::cout << "GroupName: " << GroupName << "   Facultet: " << Facultet.name << ".  Facultet Profile: " << Facultet.profile << std::endl;
    if (size > 0)
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << "Student #[" << i + 1 << "] Name: " << ListStudents[i].Name << ". Surname: " << ListStudents[i].Surname << std::endl;
        }
    }
    else
    {
        std::cout << "ListStudents is empty" << std::endl;
    }
}

StudentGroup::~StudentGroup()
{
    if (ListStudents != nullptr)
        delete[] ListStudents;
}

void StudentGroup::FindStudentAboveAverage ()
{
        int counter = 0;
        double Sum = 0;
        int Counter = 0;
        for (int n = 0; n < size; n++)
        {
            Sum += ListStudents[n].AverageG;
            Counter++;
        }
        double Average = Sum / Counter;

        for (int n = 0; n < size; n++)
        {
            if (ListStudents[n].AverageG > Average)
            {
                counter++;
            }
        }
        cout << "Amount of students with grades higher than average : " << counter << endl;
}

void StudentGroup::AverageInputStudent ( const string  StudentName )
{
    for (int n = 0; n < size; n++)
    {
        if ( StudentName == ListStudents[n].Name )
        {
            cout << ListStudents[n].AverageG;
        }
    }
}

// Перевантаження оператора виведення для класу StudentGroup
ostream& operator<<(ostream& os, const StudentGroup& group) {
    os << "GroupName: " << group.GroupName << "   Facultet: " << group.Facultet.name << ".  Facultet Profile: " << group.Facultet.profile << endl;
    if (group.size > 0) {
        for (int i = 0; i < group.size; i++) {
            os << "Student #[" << i + 1 << "] Name: " << group.ListStudents[i].Name << ". Surname: " << group.ListStudents[i].Surname << endl;
        }
    } else {
        os << "ListStudents is empty" << endl;
    }
    return os;
}

StudentGroup StudentGroup::operator+(const StudentGroup& other) const {
    StudentGroup result = *this; // Створюємо копію поточної групи
    for (int i = 0; i < other.size; ++i) {
        result.addStudent(other.ListStudents[i]); // Додаємо студентів з іншої групи до копії
    }
    return result; // Повертаємо об'єднану групу
}

int main() {

    // Faculty faculty("Faculty of Computer Science", "Computer Science");

    // StudentGroup group( faculty, "Group A1" );

    //  // Перевірка, чи група належить до певного факультету
    // string facultyName = "Faculty of Computer Science";

    // if ( group.belongsToFaculty( facultyName ) ) {
    //     cout << "The group belongs to the " << facultyName << endl;
    // } else {
    //     cout << "The group does not belong to the " << facultyName << endl;
    // }

    // group.Print();

    // Student Anton { "Anton", "Dubinkov", 4.5 };
    // Student Sergii { "Sergii", "Makarenko", 4.2 };
    // Student Maria { "Maria", "Ivanova", 5.0 };

    // group.addStudent ( Anton );
    // group.addStudent ( Sergii );

    // group.Print();

    // group.deleteStudent ( Anton );
    // group.Print();

    // std::cout << "=====================================" << std::endl;
    // group.printNameGroupAndFaculty();

    // group.addStudent ( Maria );
    // group.FindStudentAboveAverage();
    // group.Print();

    // group.AverageInputStudent( Anton.Name );

    //  std::cout << "=====================================" << std::endl;
    // StudentGroup group1(faculty, "Group A1");
    // StudentGroup group2(faculty, "Group A2");

    // // Додамо студентів до першої групи
    // Student student1{"John", "Doe", 4.5};
    // Student student2{"Alice", "Smith", 4.2};
    // group1.addStudent(student1);
    // group1.addStudent(student2);

    // // Додамо студентів до другої групи
    // Student student3{"Bob", "Johnson", 3.8};
    // Student student4{"Emily", "Brown", 4.0};
    // group2.addStudent(student3);
    // group2.addStudent(student4);

    // // Об'єднаємо дві групи
    // StudentGroup combinedGroup = group1 + group2;

    // // Виведемо об'єднану групу на екран
    // combinedGroup.Print();


    

    // Створюємо вектор для зберігання об'єктів StudentGroup
    vector<StudentGroup> groups;

    // Заповнення вектору інформацією
    // Наприклад, створимо та додамо 10 об'єктів StudentGroup
    for (int i = 0; i < 10; ++i) {
        Faculty faculty("Faculty of Computer Science", "Computer Science");
        StudentGroup group(faculty, "Group A" + to_string(i + 1));
        // Додавання об'єкту вектору
        groups.push_back(group);
    }

    // Реалізоване меню користувача для роботи з інформацією
    // Ваше меню повинно містити не менше 5 команд, наприклад:
    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Show all student groups" << endl;
        cout << "2. Add a student group" << endl;
        cout << "3. Delete a student group" << endl;
        cout << "4. Save groups to a file" << endl;
        cout << "5. Add a student to a group" << endl;
        cout << "6. Exit" << endl; // Новий пункт меню
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Відображення вмісту вектора
                for (const auto& group : groups) {
                    cout << group << endl;
                }
                break;
            case 2:
                // Додавання студентської групи
                // Наприклад, користувач може ввести дані для нової групи та додати її до вектора groups
                 {
                    string facultyName, facultyProfile, groupName;
                    cout << "Enter faculty name: ";
                    cin >> facultyName;
                    cout << "Enter faculty profile: ";
                    cin >> facultyProfile;
                    cout << "Enter group name: ";
                    cin >> groupName;

                    Faculty faculty(facultyName, facultyProfile);
                    StudentGroup newGroup(faculty, groupName);
                    groups.push_back(newGroup);
                    cout << "New student group added successfully." << endl;
                }
                break;
            case 3:
                // Видалення студентської групи
                // Наприклад, користувач може вибрати групу для видалення, і видалити її з вектора groups
                 {
                    int index;
                    cout << "Enter the index of the group you want to delete: ";
                    cin >> index;

                    if (index >= 0 && index < groups.size()) {
                        groups.erase(groups.begin() + index);
                        cout << "Student group at index " << index << " deleted successfully." << endl;
                    } else {
                        cout << "Invalid index. Please enter a valid index between 0 and " << (groups.size() - 1) << "." << endl;
                    }
                }
                break;
            case 4:
                // Збереження остаточного вмісту вектора у текстовому файлі
                {
                    ofstream outFile("groups.txt");
                    if (outFile.is_open()) {
                        for (const auto& group : groups) {
                            outFile << group << endl;
                        }
                        outFile.close();
                        cout << "Groups saved to file." << endl;
                    } else {
                        cout << "Unable to open file." << endl;
                    }
                }
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            case 5:
            // Додавання студента до групи
            {
                int groupIndex;
                cout << "Enter the index of the group you want to add a student to: ";
                cin >> groupIndex;

                if (groupIndex > 0 && groupIndex <= groups.size()) {
                    string studentName, studentSurname;
                    double averageGrade;
                    cout << "Enter student name: ";
                    cin >> studentName;
                    cout << "Enter student surname: ";
                    cin >> studentSurname;
                    cout << "Enter student's average grade: ";
                    cin >> averageGrade;

                    Student newStudent;
                    newStudent.Name = studentName;
                    newStudent.Surname = studentSurname;
                    newStudent.AverageG = averageGrade;

                    groups[groupIndex - 1].addStudent(newStudent);
                    cout << "Student added to group successfully." << endl;
                } else {
                    cout << "Invalid group index. Please enter a valid index between 0 and " << (groups.size()) << "." << endl;
                }
            }
            break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
        }
    } while (choice != 6);

    return 0;
}
