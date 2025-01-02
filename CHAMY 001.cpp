#include <iostream>
#include <string>
#include <limits>
using namespace std;

bool validateCredentials(const string& username, const string& password) {
    
    const string correctUsername = "user123";
    const string correctPassword = "pass123";
    
    return (username == correctUsername && password == correctPassword);
}

int main() {
    string username, password;

    cout << "WELCOME TO AIR TAXI!" << endl;

    for (int attempts = 0; attempts < 3; ++attempts) {
        
        cout << "Enter your username: ";
        cin >> username;

        cout << "Enter your password: ";
        cin >> password;

        if (validateCredentials(username, password)) {
            cout << "Login successful!" << endl;
            break; 
        } else {
            cout << "Invalid username or password. Please try again." << endl;
        }

        if (attempts == 2) {
            cout << "Too many failed attempts. Exiting..." << endl;
        }
    }  
}
void displayHomePage() {
    cout << "\n--------------------------------------------\n";
    cout << "             Welcome to the Home Page!      \n";
    cout << "        You have successfully logged in.    \n";
    cout << "--------------------------------------------\n";
}


bool login(const string& username, const string& password) {
   
    const string correctUsername = "user";
    const string correctPassword = "password";


    if (username == correctUsername && password == correctPassword) {
        return true;
    }
    return false;
}

int main() {
    string username;
    string password;
    bool loggedIn = false;

    cout << "===========================================\n";
    cout << "             Welcome to the Login Page     \n";
    cout << "===========================================\n";

   
    while (!loggedIn) {
        cout << "\nEnter your username: ";
        getline(cin, username);

        cout << "Enter your password: ";
        getline(cin, password);

       
        if (login(username, password)) {
            loggedIn = true;  
            cout << "\nLogin successful! Redirecting to Home Page...\n";
        } else {
            cout << "\nInvalid username or password. Please try again.\n";
        }
    }
    displayHomePage();

    return 0;
}
