#include <iostream>

// // Основний шаблон
template <int N, bool... digits>
struct CheckValues {
    static void print() {
        std::cout << "General template with N = " << N << std::endl;
    }
};

// Часткова спеціалізація для N = 0
template <bool... digits>
struct CheckValues<0, digits...> {
    static void print() {
        std::cout << "Specialized template for N = 0" << std::endl;
        std::cout << "Number of bools: " << sizeof...(digits) << std::endl;
    }
};

int main() {
    CheckValues<5, true, false>::print(); // Використовує основний шаблон
    CheckValues<0, true, true, false>::print(); // Використовує часткову спеціалізацію

    return 0;
}





// Приклад 1: Обчислення двійкового числа
// У цьому прикладі ми використовуємо параметр-пакет digits для обчислення двійкового числа, де кожен bool значення представляє один біт.
#include <iostream>

// Шаблон класу для обчислення двійкового числа з булевих значень
template <bool... digits>
struct BinaryValue;

// Спеціалізація для пустого пакета (базовий випадок рекурсії)
template <>
struct BinaryValue<> {
    static constexpr int value = 0;
};

// Часткова спеціалізація для непустого пакета
template <bool first, bool... rest>
struct BinaryValue<first, rest...> {
    static constexpr int value = (first ? 1 : 0) << sizeof...(rest) | BinaryValue<rest...>::value;
};

int main()  {
    // Обчислюємо двійкове значення 101 (у двійковій системі)
    constexpr int value = BinaryValue<true, false, true>::value;

    std::cout << "Binary value: " << value << std::endl; // Виводить: Binary value: 5

    return 0;
}







// Приклад 2: Підрахунок кількості значень true
// У цьому прикладі ми використаємо параметр-пакет digits для підрахунку кількості значень true у пакеті.

#include <iostream>

// Шаблон класу для підрахунку кількості true у параметр-пакеті
template <bool... digits>
struct CountTrue;

// Спеціалізація для пустого пакета
template <>
struct CountTrue<> {
    static constexpr int value = 0;
};

// Часткова спеціалізація для непустого пакета
template <bool first, bool... rest>
struct CountTrue<first, rest...> {
    static constexpr int value = (first ? 1 : 0) + CountTrue<rest...>::value;
};

int main() {
    // Підрахунок кількості true
    constexpr int count = CountTrue<true, false, true, true>::value;

    std::cout << "Number of true values: " << count << std::endl; // Виводить: Number of true values: 3

    return 0;
}





// Приклад 3: Генерація масиву значень
// Використаємо параметр-пакет digits для ініціалізації масиву значень.

#include <iostream>
#include <array>

// Шаблон класу для створення масиву булевих значень
template <bool... digits>
struct BoolArray {
    static constexpr std::array<bool, sizeof...(digits)> value = {digits...};
};

int main() {
    // Створення масиву з параметр-пакету
    constexpr auto bools = BoolArray<true, false, true, false, true>::value;

    std::cout << "Bool array: ";
    for (bool b : bools) {
        std::cout << b << " "; // Виводить: 1 0 1 0 1 
    }
    std::cout << std::endl;

    return 0;
}






// Приклад 4: Використання з рекурсивними шаблонними функціями
// Іноді параметр-пакет використовується для виконання рекурсивних операцій.

#include <iostream>

// Рекурсивна функція для обчислення добутку чисел у параметр-пакеті
template <typename T, T... numbers>
constexpr T product() {
    return (numbers * ... * 1); // fold expression для обчислення добутку
}

int main() {
    // Обчислення добутку чисел
    constexpr int result = product<int, 2, 3, 4>();

    std::cout << "Product: " << result << std::endl; // Виводить: Product: 24

    return 0;
}






// Так, ви правильно зрозуміли! Параметр-пакет в C++ може бути будь-якого типу. 
// Це означає, що ви можете використовувати параметр-пакети для прийому будь-якої кількості аргументів будь-якого типу. 
// Давайте розглянемо декілька прикладів використання параметр-пакетів з різними типами.

#include <iostream>

// Функція для обчислення суми чисел у параметр-пакеті
template <int... numbers>
constexpr int sum() {
    return (numbers + ... + 0); // Fold expression для обчислення суми
}

int main() {
    constexpr int result = sum<1, 2, 3, 4, 5>();
    std::cout << "Sum: " << result << std::endl; // Виводить: Sum: 15
    return 0;
}





// Функція для виведення значень різних типів
template <typename... Args>
void printValues(const Args&... args) {
    (std::cout << ... << args) << std::endl; // Fold expression для виведення значень
}

int main() {
    printValues(1, 2.5, "Hello", 'A', true); // Виводить: 12.5HelloA1
    return 0;
}







// Функція для підрахунку кількості значень true у параметр-пакеті
template <bool... values>
constexpr int countTrue() {
    return (0 + ... + values); // Fold expression для підрахунку
}

int main() {
    constexpr int trueCount = countTrue<true, false, true, true>();
    std::cout << "Number of true values: " << trueCount << std::endl; // Виводить: Number of true values: 3
    return 0;
}






// Функція для виведення типів та їх значень
template <typename... Args>
void showTypesAndValues(const Args&... args) {
    ((std::cout << typeid(args).name() << ": " << args << std::endl), ...); // Виводить типи та значення
}

int main() {
    showTypesAndValues(10, 3.14, "text", true); 
    // Виводить:
    // int: 10
    // double: 3.14
    // PKc: text (const char* в залежності від компілятора)
    // bool: 1
    return 0;
}






// Fold expression - це спеціальний синтаксис у C++, який дозволяє зручно виконувати операції над елементами в параметр-пакеті. Введені в стандарті C++17, fold expressions значно спрощують роботу з параметр-пакетами, зводячи розгортання виразів до одного рядка коду.

// Основи роботи fold expression
// Fold expressions дозволяють застосувати певну операцію до всіх елементів параметр-пакету. Є кілька видів fold expressions:

// Унарні ліві fold вирази: (op ... args)
// Унарні праві fold вирази: (args ... op)
// Бінарні ліві fold вирази: (init op ... op args)
// Бінарні праві fold вирази: (args op ... op init)
// Де:

// op - це будь-який бінарний оператор (+, -, *, &&, ||, тощо).
// args - це параметр-пакет.