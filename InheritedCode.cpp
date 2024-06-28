#include <iostream>
#include <string>
#include <sstream>
#include <exception>
using namespace std;


class BadLengthException : public exception
{
public:
    BadLengthException( int value_size ) : number_size(value_size), buffer(nullptr) {}

    const char* what()  
    {
		std::string temp_str = std::to_string(number_size).c_str();
		buffer = new char[temp_str.size() + 1];
		std::strcpy(buffer, temp_str.c_str());
        return buffer;
    }

private:
    int number_size;
	char* buffer;
};




bool checkUsername(string username) {
	bool isValid = true;
	int n = username.length();
	if(n < 5) {
		throw BadLengthException(n);
	}
	for(int i = 0; i < n-1; i++) {
		if(username[i] == 'w' && username[i+1] == 'w') {
			isValid = false;
		}
	}
	return isValid;
}

int main() {
	int T; cin >> T;
	while(T--) {
		string username;
		cin >> username;
		try {
			bool isValid = checkUsername(username);
			if(isValid) {
				cout << "Valid" << '\n';
			} else {
				cout << "Invalid" << '\n';
			}
		} catch (BadLengthException e) {
			cout << "Too short: " << e.what() << '\n';
		}
	}
	return 0;
}