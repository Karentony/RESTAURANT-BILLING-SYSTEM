#include <iostream>
#include <vector>
#include <string>
#include <iomanip>  

using namespace std;


struct MenuItem {
    string name;
    float price;
};


void displayMenu(const vector<MenuItem>& menu) {
    cout << "------ Restaurant Menu ------\n";
    for (int i = 0; i < menu.size(); i++) {
        cout << i + 1 << ". " << menu[i].name << " - $" << menu[i].price << endl;
    }
}


void takeOrder(const vector<MenuItem>& menu, vector<int>& order) {
    int choice, quantity;
    while (true) {
        cout << "\nEnter the item number to order (0 to finish): ";
        cin >> choice;
        
        if (choice == 0) break; 
        
        if (choice < 1 || choice > menu.size()) {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        cout << "Enter quantity: ";
        cin >> quantity;

        for (int i = 0; i < quantity; i++) {
            order.push_back(choice - 1);  
        }
        
        cout << "Item added to your order.\n";
    }
}

void printBill(const vector<MenuItem>& menu, const vector<int>& order) {
    float total = 0;
    cout << "\n------ Your Bill ------\n";
    for (int i = 0; i < order.size(); i++) {
        int index = order[i];
        cout << menu[index].name << " - $" << fixed << setprecision(2) << menu[index].price << endl;
        total += menu[index].price;
    }
    
    cout << "\nTotal: $" << fixed << setprecision(2) << total << endl;
    
    float discount = 0;
    if (total > 50) {
        discount = total * 0.1;  
        cout << "Discount applied: -$" << discount << endl;
    }
    
    float finalAmount = total - discount;
    cout << "Final amount to pay: $" << fixed << setprecision(2) << finalAmount << endl;
}

int main() {
    vector<MenuItem> menu = {
        {"Burger", 8.99},
        {"Pizza", 12.49},
        {"Pasta", 9.99},
        {"Salad", 5.49},
        {"Soda", 2.49}
    };

    vector<int> order;  

    int choice;
    do {
        cout << "\n------ Restaurant Billing System ------\n";
        cout << "1. View Menu\n";
        cout << "2. Place Order\n";
        cout << "3. Print Bill\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayMenu(menu);
                break;
            case 2:
                takeOrder(menu, order);
                break;
            case 3:
                printBill(menu, order);
                break;
            case 4:
                cout << "Thank you for visiting! Goodbye.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
