#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <iterator>
#include <map>
#include <numeric> // для accumulate

#include <regex>
using namespace std;

// Реалізувати телефонний довідник, використовуючи контейнер map.
// Ключем має бути номер телефону абонента в форматі +38(0--)-------, перевірка коректності формату обов'язкова.
// Значенням має бути інформація про абонента, яка складається з Прізвища, ініціалів, дати народження в форматі --.--.--.
// Інформацію про абонента бажано реалізувати у вигляді об'єкта класу (у спрощеному вигляді допустимо представити інформацію про абонента у вигляді рядка).
// Забезпечити виконання таких операцій:
// - додавання абонента;
// - видалення абонента;
// - редагування будь-яких даних про абонента;
// - вибірка абонентів, день народження яких припадає на місяць, введений з клавіатури;
// - пошук абонента за прізвищем та за номером телефону.
// Результати виконання подати у вигляді звіту про виконання лабораторної роботи.








// Клас для зберігання інформації про абонента
class SubscriberInfo {
private:
    string surname;
    string initials;
    string birthdate;

public:
    SubscriberInfo() = default;
    
    SubscriberInfo(const string& surname, const string& initials, const string& birthdate)
        : surname(surname), initials(initials), birthdate(birthdate) {}

    // Метод для встановлення даних
    void setInfo(const string& surname, const string& initials, const string& birthdate) {
        this->surname = surname;
        this->initials = initials;
        this->birthdate = birthdate;
    }

   // Метод для отримання даних
    string getInfo() const {
        return "Surname: " + surname + ", Initials: " + initials + ", Birthdate: " + birthdate;
    }

    // Метод для отримання місяця народження
    string getBirthMonth() const {
        return birthdate.substr(3, 2); // Витягує місяць з дати народження
    }

    // Друк інформації про абонента
    void print() const {
        cout << "Surname: " << surname << ", Initials: " << initials << ", Birthdate: " + birthdate << endl;
    }

    // Метод для отримання прізвища
    string getSurname() const {
        return surname;
    }
};

// Клас для телефонного довідника
class PhoneBook {
private:
    map< string, SubscriberInfo> phoneBook;

    // Функція для перевірки коректності номера телефону
    bool isValidPhoneNumber(const string& phoneNumber) {
        regex phoneRegex(R"(\+38\(0\d{2}\)\d{7})");
        return regex_match(phoneNumber, phoneRegex);
    }

public:
    void addSubscriber(const string& phoneNumber, const SubscriberInfo& info);
    void removeSubscriber(const string& phoneNumber);
    void editSubscriber(const string& phoneNumber, const SubscriberInfo& newInfo);
    vector<SubscriberInfo> getSubscribersByBirthMonth(const string& month) const;
    vector<string> searchBySurname(const string& surname) const;
    SubscriberInfo* searchByPhoneNumber(const string& phoneNumber);
    void printAll() const;
    void saveToFile(const string& filename) const;
};

 // Додавання абонента
void PhoneBook::addSubscriber(const string& phoneNumber, const SubscriberInfo& info) {
        if (isValidPhoneNumber(phoneNumber)) {
            phoneBook[phoneNumber] = info;
            cout << "Subscriber added successfully." << endl;
        } else {
            cout << "Invalid phone number format: " << phoneNumber << endl;
        }
}

// Видалення абонента
void PhoneBook::removeSubscriber(const string& phoneNumber) {
        if (phoneBook.erase(phoneNumber)) {
            cout << "Subscriber removed successfully." << endl;
        } else {
            cout << "Subscriber with phone number " << phoneNumber << " not found." << endl;
        }
}

// Редагування абонента
void PhoneBook::editSubscriber(const string& phoneNumber, const SubscriberInfo& newInfo) {
        auto it = phoneBook.find(phoneNumber);
        if (it != phoneBook.end()) {
            it->second = newInfo;
            cout << "Subscriber edited successfully." << endl;
        } else {
            cout << "Subscriber with phone number " << phoneNumber << " not found." << endl;
        }
}

// Вибірка абонентів за місяцем народження
vector<SubscriberInfo> PhoneBook::getSubscribersByBirthMonth(const string& month) const {
        vector<SubscriberInfo> result;
        for (const auto& entry : phoneBook) {
            if (entry.second.getBirthMonth() == month) {
                result.push_back(entry.second);
            }
        }
        return result;
}

// Пошук абонента за прізвищем
vector<string> PhoneBook::searchBySurname(const string& surname) const {
        vector<string> result;
        for (const auto& entry : phoneBook) {
            if (entry.second.getSurname() == surname) {
                result.push_back(entry.first);
            }
        }
        return result;
}

// Пошук абонента за номером телефону
SubscriberInfo* PhoneBook::searchByPhoneNumber(const string& phoneNumber) {
        auto it = phoneBook.find(phoneNumber);
        if (it != phoneBook.end()) {
            return &it->second;
        }
        return nullptr;
}

// Друк всіх абонентів
void PhoneBook::printAll() const {
        for (const auto& entry : phoneBook) {
            cout << "Phone Number: " << entry.first << " -> ";
            entry.second.print();
        }
}

// Збереження телефонного довідника у файл
void PhoneBook::saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& entry : phoneBook) {
                file << entry.first << ": " << entry.second.getInfo() << endl;
            }
            file.close();
            cout << "Phone book saved to " << filename << endl;
        } else {
            cout << "Unable to open file " << filename << endl;
        }
}




int main() 
{
    // Створення телефонного довідника
    PhoneBook phoneBook;

    // Додавання абонентів
    phoneBook.addSubscriber("+38(067)1234567", SubscriberInfo("Ivanov", "I.I.", "01.01.1990"));
    phoneBook.addSubscriber("+38(050)7654321", SubscriberInfo("Petrov", "P.P.", "15.01.1985"));

    // phoneBook.printAll();

    // // Редагування абонента
    // phoneBook.editSubscriber("+38(067)1234567", SubscriberInfo("Ivanov", "I.I.", "01.01.1991"));

    // std::cout << " ============================================== " << std::endl;
    // phoneBook.printAll();


    // // Видалення абонента
    // phoneBook.removeSubscriber("+38(050)7654321");


    // std::cout << " ============================================== " << std::endl;
    // phoneBook.printAll();


    // Пошук абонентів за місяцем народження
    string month ;
    std::cout << "Enter month: ";
    std::cin >> month;

    vector<SubscriberInfo> januarySubscribers = phoneBook.getSubscribersByBirthMonth(month);
    cout << "Subscribers born in January:" << endl;
    for (const auto& subscriber : januarySubscribers) {
        subscriber.print();
    }
    
    std::cout << " ============================================== " << std::endl;
    // Пошук абонентів за прізвищем
    string surname = "Ivanov";
    vector<string> phoneNumbers = phoneBook.searchBySurname(surname);
    cout << "Phone numbers for surname Ivanov:" << endl;
    for (const auto& phoneNumber : phoneNumbers) {
        cout << phoneNumber << endl;
    }

    // std::cout << " ============================================== " << std::endl;

    // Пошук абонента за номером телефону
    string searchPhoneNumber = "+38(050)7654321";
    SubscriberInfo* subscriber = phoneBook.searchByPhoneNumber(searchPhoneNumber);
    if (subscriber) {
        cout << "Subscriber with phone number " << searchPhoneNumber << ":" << endl;
        subscriber->print();
    } else {
        cout << "Subscriber with phone number " << searchPhoneNumber << " not found." << endl;
    }

    // std::cout << " ============================================== " << std::endl;

    // Друк всіх абонентів
    cout << "All subscribers:" << endl;
    phoneBook.printAll();

    return 0;
}