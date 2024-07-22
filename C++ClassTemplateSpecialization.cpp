#include <iostream>
#include <string>
#include <map>
#include <type_traits>
using namespace std;

enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };

// template <typename T>
// struct Traits
// {
//     T enumValue;

//     static std::string name(int index)
//     {
//         if  (std::is_same<T, Fruit>::value )
//         {
//             switch ( index )
//             {
//                 case 0:
//                     return "apple";
//                 case 1:
//                     return "orange";
//                 case 2:
//                     return "pear";
//                 default:
//                     return "unknown";
//             }
//         }
//         else if ( std::is_same<T, Color>::value )
//         {
//             switch ( index )
//             {
//                 case 0:
//                     return "red";
//                 case 1:
//                     return "green";
//                 case 2:
//                     return "orange";
//                 default:
//                     return "unknown";
//             }
//         }
//     }
// };


template <typename T>
struct Traits {
    static std::string name(int index) {
        const std::map< int, std::string >& names = getNames();
        auto it = names.find(index);
        return it != names.end() ? it->second : "unknown";
    }

private:
    static const std::map<int, std::string>& getNames() {
        static std::map<int, std::string> names;
        if  (std::is_same<T, Fruit>::value) {
            names = {
                {0, "apple"},
                {1, "orange"},
                {2, "pear"}
            };
        } else if  (std::is_same<T, Color>::value) {
            names = {
                {0, "red"},
                {1, "green"},
                {2, "orange"}
            };
        }
        return names;
    }
};





int main()
{
	int t = 0; std::cin >> t;

    for (int i=0; i!=t; ++i) {
        int index1; std::cin >> index1;
        int index2; std::cin >> index2;
        cout << Traits<Color>::name(index1) << " ";
        cout << Traits<Fruit>::name(index2) << "\n";
    }
}