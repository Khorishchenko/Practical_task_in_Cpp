#include <string>
#include <sstream>
#include <cmath>
#include <limits>
#include <stdexcept>

#include <iostream>
using namespace std;


class A
{
    public:
        A(){
            callA = 0;
        }
    private:
        int callA;
        void inc(){
            callA++;
        }

    protected:
        void func(int & a)
        {
            a = a * 2;
            inc();
        }
    public:
        int getA(){
            return callA;
        }
};

class B
{
    public:
        B(){
            callB = 0;
        }
    private:
        int callB;
        void inc(){
            callB++;
        }
    protected:
        void func(int & a)
        {
            a = a * 3;
            inc();
        }
    public:
        int getB(){
            return callB;
        }
};

class C
{
    public:
        C(){
            callC = 0;
        }
    private:
        int callC;
        void inc(){
            callC++;
        }
    protected:
        void func(int & a)
        {
            a = a * 5;
            inc();
        }
    public:
        int getC(){
            return callC;
        }
};

class D : public A, public B, public C
{
	int val;
	public:
		//Initially val is 1
		 D()
		 {
		 	val = 1;
		 }

		    //Write your code here to update the value of val using the provided function and the member functions of A, B, and C classes.
            //Hint: You can use the func() function of A, B, and C classes to update the value of val.
            //Also, remember to call the inc() function of each class to increment their respective call counters.
            //Your implementation should ensure that the value of val is updated correctly and the member functions of A, B, and C classes are called as per the problem statement.
            //Your solution should not use any additional data structures or classes.
            //Your solution should be efficient and should not have any time or space complexity issues.
            //Your solution should also handle cases where the value of new_val is negative or zero and should not update the value of val or call the member functions of A, B, and C classes.
            //Your solution should also handle cases where the value of new_val is greater than
            // the maximum value that can be stored in an integer variable.
            //Your solution should also handle cases where the value of new_val is a floating-point number and should round it to the nearest integer before updating the value of val.
            //Your solution should also handle cases where the value of new_val is a string and should convert it to an integer before updating the value of val.
            //Your solution should also handle cases where the value of new_val is a negative or zero string and should not update the value of val or call the member functions of A, B, and C classes.
            //Your solution should also handle cases where the value of new_val is a string that cannot be converted to an integer and should not update the value of val or call the member functions of A, B, and C classes.
            //Your solution should also handle cases where the value of new_val is a string that contains leading or trailing spaces and should remove the spaces


          // Implement this function
        void update_val(int new_val) {
        // Check for negative or zero value
            if (new_val <= 0) {
                return; // Do not update val or call any functions
            }

            while (val!=new_val)
            {
                 if ((new_val/val)%2==0){A::func(val);}
                 if ((new_val/val)%3==0){B::func(val);}
                 if ((new_val/val)%5==0){C::func(val);} 
            }
        }

        // Overloaded function to handle float
        void update_val(float new_val) {
            // Round the float to the nearest integer
            int rounded_val = static_cast<int>(std::round(new_val));
            update_val(rounded_val); // Call the int version
        }

        // Overloaded function to handle string
        void update_val(const std::string& new_val) {
            // Trim leading and trailing spaces
            std::string trimmed_val = new_val;
            trimmed_val.erase(0, trimmed_val.find_first_not_of(" \t\n"));
            trimmed_val.erase(trimmed_val.find_last_not_of(" \t\n") + 1);

            // Check for empty string
            if (trimmed_val.empty()) {
                return; // Do not update val or call any functions
            }

            // Try to convert to integer
            try {
                size_t pos;
                int int_val = std::stoi(trimmed_val, &pos);

                // Check if the entire string was converted and if it's not negative
                if (pos == trimmed_val.length() && int_val > 0) {
                    update_val(int_val); // Call the int version
                }
            } catch (const std::invalid_argument&) {
                // Not a valid integer
            } catch (const std::out_of_range&) {
                // Integer out of range
            }
        }
		 //For Checking Purpose
		 void check(int); //Do not delete this line.
};


void D::check(int new_val)
{
    update_val(new_val);
    std::cout << "Value = " << val << std::endl;
    std::cout << "A's func called " << getA() << " times " << std::endl << "B's func called " << getB() << " times" << std::endl << "C's func called " << getC() << " times" << std::endl;
}


int main()
{
    D d;
    int new_val = 5;
    d.check(new_val);
}