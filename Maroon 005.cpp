#include <iostream>
#include <string>

using namespace std;


bool validateLogin(const string& username, const string& password) {
    const string correctUsername = "admin";
    const string correctPassword = "1234";

    
    return (username == correctUsername && password == correctPassword);
}

int main() {
    string username, password;
    int attempts = 3;  

    cout << "Welcome to Maroon Restaurant !" << endl;

    while (attempts > 0) {
      
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

       
        if (validateLogin(username, password)) {
            cout << "Login successful! Welcome, " << username << "!" << endl;
            break;  
        } else {
            attempts--;
            cout << "Invalid username or password. You have " << attempts << " attempt(s) remaining." << endl;

            if (attempts == 0) {
                cout << "Too many failed attempts. Access denied." << endl;
            }
        }
    }

    return 0;
}
