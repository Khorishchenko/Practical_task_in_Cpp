#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    std::vector<int> vec;
    
    int size = 0;
    std::cin >> size;
    vec.reserve(size); // зарезервируем память заранее
    for( int i = 0, value = 0; i < size; i++ )
    {
        std::cin >> value;
        vec.push_back( value ); 
    }

    std::sort( vec.begin(), vec.end() );

    for ( const auto& element : vec )
        std::cout << element << ' ';
    std::cout << '\n';

    return 0;
}
