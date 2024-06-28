#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;

// Some C++ data types, their format specifiers, and their most common bit widths are as follows:
// Int ("%d"): 32 Bit integer
// Long ("%ld"): 64 bit integer
// Char ("%c"): Character type
// Float ("%f"): 32 bit real value
// Double ("%lf"): 64 bit real value

int main()
{
    int value;
    float valueFloat;
    char valueChar;
    double valueDauble;
    long valueLong;

    scanf(" %d %ld %c %f %lf", &value, &valueLong, &valueChar, &valueFloat, &valueDauble );

    printf(" %d\n %ld\n %c\n %.3f\n %.9lf\n", value, valueLong, valueChar, valueFloat, valueDauble );



    int d;
    int long ld;
    char c;
    float f;
    double lf;
    cin>>d;
    cin>>ld;
    cin>> c;
    cin>>f;
    cin>>lf;

    cout<<d<<endl;
    cout<<ld<<endl;
    cout<<c<<endl; 
    cout<<fixed<<setprecision(3)<<f<<endl; // using manipulators
    cout<<fixed<<setprecision(9)<<lf<<endl;
}