#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct MenuItem {
    string name;
    float price;
};

bool login() {
    string username, password;
    string correctUsername = "admin";  
    string correctPassword = "admin123";  

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username == correctUsername && password == correctPassword) {
        return true; 
    } else {
        return false; 
    }
}

void displayMenu(const vector<MenuItem>& menu) {
    cout << "\nRestaurant Menu:\n";
    for (int i = 0; i < menu.size(); ++i) {
        cout << i + 1 << ". " << menu[i].name << " - $" << menu[i].price << endl;
    }
}

void generateBill(const vector<MenuItem>& menu, vector<int>& orderedItems) {
    float totalBill = 0;
    cout << "\n----- BILL -----\n";
    for (int i = 0; i < orderedItems.size(); ++i) {
        int itemIndex = orderedItems[i] - 1;
        cout << menu[itemIndex].name << " - $" << menu[itemIndex].price << endl;
        totalBill += menu[itemIndex].price;
    }
    cout << "-----------------\n";
    cout << "Total Bill: $" << totalBill << endl;
}

void homePage(const vector<MenuItem>& menu) {
    vector<int> orderedItems;  
    int choice;
    
    while (true) {
        cout << "\nWelcome to the Restaurant Billing System!\n";
        cout << "1. View Menu\n";
        cout << "2. Order Item\n";
        cout << "3. View Bill\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayMenu(menu);
                break;
            case 2: {
                int itemNumber;
                cout << "\nEnter the number of the item you want to order: ";
                cin >> itemNumber;
                if (itemNumber > 0 && itemNumber <= menu.size()) {
                    orderedItems.push_back(itemNumber);
                    cout << "Item added to your order.\n";
                } else {
                    cout << "Invalid item number. Please try again.\n";
                }
                break;
            }
            case 3:
                generateBill(menu, orderedItems);
                break;
            case 4:
                cout << "\nThank you for visiting! Goodbye!\n";
                return;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }
}

int main() {
    vector<MenuItem> menu = {
        {"Burger", 5.99},
        {"Pizza", 8.99},
        {"Pasta", 7.49},
        {"Salad", 4.49},
        {"Soup", 3.99}
    };

    cout << "Restaurant Billing System\n";

    while (true) {
        if (login()) {
            cout << "\nLogin successful!\n";
            break;
        } else {
            cout << "\nInvalid credentials. Please try again.\n";
        }
    }

    homePage(menu);

    return 0;
}
