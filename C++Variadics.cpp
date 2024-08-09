#include <iostream>
using namespace std;

// Enter your code for reversed_binary_value<bool...>()


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


template <bool... digits> 
int reversed_binary_value()
{
    return BinaryValue<digits...>::value;
}


template <int n, bool...digits>
struct CheckValues {
  	static void check(int x, int y)
  	{
    	CheckValues<n-1, 0, digits...>::check(x, y);
    	CheckValues<n-1, 1, digits...>::check(x, y);
  	}
};

template <bool...digits>
struct CheckValues<0, digits...> {
  	static void check(int x, int y)
  	{
    	int z = reversed_binary_value<digits...>();
    	std::cout << (z+64*y==x);
  	}
};

int main()
{
  	int t; std::cin >> t;

  	for (int i=0; i!=t; ++i) {
		int x, y;
    	cin >> x >> y;
    	CheckValues<6>::check(x, y);
    	cout << "\n";
  	}

	CheckValues<7>::check(1, 3);
	CheckValues<7>::check(1, 2);
	return 0;
}