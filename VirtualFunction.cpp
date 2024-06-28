#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Person    {
        protected:
                int age;
                string name;
        public:
                virtual void getdata() = 0;
                virtual void putdata() = 0;
};
class Professor : public Person {
        private:
                int  publications, cur_id;
                static int pp;
        public:
                void getdata()  {
                        cin>>name>>age>>publications;
                        cur_id = ++pp;
                }
                void putdata()  {
                        cout<<name<<" "<<age<<" "<<publications<<" "<<cur_id<<endl;
                }
};int Professor::pp=0;

class Student : public Person   {
        private:
                int Arr[6];
                static int count;
                int cur_id;
        public:
                void getdata()  {
                        cin>>name>>age;
                        for(int x = 0; x<6; x++)
                                cin>>Arr[x];
                        cur_id = ++count;
                }
                void putdata()  {
                        int sum =0;
                        for(int x = 0; x<6; sum+=Arr[x], x++);
                        cout<<name<<" "<<age<<" "<<sum<<" "<<cur_id<<endl;
                }
};

int Student::count=0;

int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}