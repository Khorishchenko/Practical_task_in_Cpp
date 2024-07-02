#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;


int main() {
    // std::vector<int> vec;
    
    // int size = 0;
    // std::cin >> size;
    // vec.reserve(size);
    // for( int i = 0, value = 0; i < size; i++ )
    // {
    //     std::cin >> value;
    //     vec.push_back( value ); 
    // }

    // int deleteIndex = 0;
    // int rangeFirst = 0;
    // int rangeLast = 0;

    // std::cout << "Enter index: ";
    // std::cin >> deleteIndex;
    // std::cout << "Enter firts and last range: ";
    // std::cin >> rangeFirst >> rangeLast;

    // if (rangeFirst >= 0 && rangeLast <= vec.size() && rangeFirst < rangeLast) {
    //     vec.erase(vec.begin() + rangeFirst, vec.begin() + rangeLast);
    // } else {
    //     std::cerr << "Неправильний діапазон індексів" << std::endl;
    // }

    // std::cout << vec.size() << std::endl;

    // for ( const auto& element :  vec )
    //     std::cout << element << ' ';
    // std::cout << "\n"; 





    vector<int> v;
    int x, a, b;  //x=elem to remove, a and b=range to remove

    int size; //size of vector
    cin >> size;
		
    //fill vector
    for ( int i = 0; i < size; ++i ) 
    {
        int num;
        cin >> num;
        v.push_back(num);
    }    
	// or
    copy_n(istream_iterator<int>(cin), size, back_inserter(v));  

    cin >> x;  //insert element to remove
    v.erase(v.begin() + (--x));

    cin >> a >> b;  //insert range to remove
    v.erase(v.begin() + (--a), v.begin() + (--b));

    cout << v.size() << endl;  //output size of vector
		
	//output vect
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 
   

    return 0;
}