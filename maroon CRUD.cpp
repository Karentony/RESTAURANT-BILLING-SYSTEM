#include <iostream>
#include <vector>
#include <string>

using namespace std
struct MenuItem {
    int id;
    string name;
    double price;
};


struct Order {
    int orderId;
    MenuItem item;
    int quantity;

void displayMenu(const vector<MenuItem>& menu) {
    cout << "\n===== Restaurant Menu =====\n";
    for (const auto& item : menu) {
        cout << "ID: " << item.id << " | " << item.name << " | Price: $" << item.price << endl;
    }
    cout << "==========================\n";
}


void addMenuItem(vector<MenuItem>& menu) {
    MenuItem newItem;
    cout << "Enter Menu ID: ";
    cin >> newItem.id;
    cin.ignore(); 
    cout << "Enter Menu Item Name: ";
    getline(cin, newItem.name);
    cout << "Enter Price: $";
    cin >> newItem.price;
    menu.push_back(newItem);
    cout << "Menu item added successfully!\n";
}


void addOrder(vector<Order>& orders, const vector<MenuItem>& menu) {
    int itemId, quantity;
    cout << "Enter Menu Item ID: ";
    cin >> itemId;
    cout << "Enter Quantity: ";
    cin >> quantity;

    for (const auto& item : menu) {
        if (item.id == itemId) {
            Order newOrder = {orders.size() + 1, item, quantity};
            orders.push_back(newOrder);
            cout << "Order placed successfully!\n";
            return;
        }
    }
    cout << "Item ID not found in menu.\n";
}


void displayOrders(const vector<Order>& orders) {
    cout << "\n===== Orders =====\n";
    for (const auto& order : orders) {
        cout << "Order ID: " << order.orderId 
             << " | Item: " << order.item.name 
             << " | Quantity: " << order.quantity 
             << " | Total Price: $" << order.item.price * order.quantity << endl;
    }
    cout << "==================\n";
}


void updateMenuItem(vector<MenuItem>& menu) {
    int id;
    cout << "Enter Menu Item ID to update: ";
    cin >> id;
    
    for (auto& item : menu) {
        if (item.id == id) {
            cin.ignore(); 
            cout << "Enter new Name: ";
            getline(cin, item.name);
            cout << "Enter new Price: $";
            cin >> item.price;
            cout << "Menu item updated successfully!\n";
            return;
        }
    }
    cout << "Item not found.\n";
}


void deleteMenuItem(vector<MenuItem>& menu) {
    int id;
    cout << "Enter Menu Item ID to delete: ";
    cin >> id;
    
    for (auto it = menu.begin(); it != menu.end(); ++it) {
        if (it->id == id) {
            menu.erase(it);
            cout << "Menu item deleted successfully.\n";
            return;
        }
    }
    cout << "Item not found.\n";
}


void deleteOrder(vector<Order>& orders) {
    int orderId;
    cout << "Enter Order ID to delete: ";
    cin >> orderId;
    
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        if (it->orderId == orderId) {
            orders.erase(it);
            cout << "Order deleted successfully.\n";
            return;
        }
    }
    cout << "Order not found.\n";
}


void displayBill(const vector<Order>& orders) {
    double totalBill = 0;
    cout << "\n===== Bill =====\n";
    for (const auto& order : orders) {
        double orderTotal = order.item.price * order.quantity;
        cout << "Item: " << order.item.name << " | Quantity: " << order.quantity
             << " | Total: $" << orderTotal << endl;
        totalBill += orderTotal;
    }
    cout << "================\n";
    cout << "Total Bill: $" << totalBill << endl;
}

int main() {
    vector<MenuItem> menu;  
    vector<Order> orders;   

    int choice;
    while (true) {
        cout << "\n===== Restaurant Billing System =====\n";
        cout << "1. Add Menu Item\n";
        cout << "2. Add Order\n";
        cout << "3. Display Menu\n";
        cout << "4. Display Orders\n";
        cout << "5. Update Menu Item\n";
        cout << "6. Delete Menu Item\n";
        cout << "7. Delete Order\n";
        cout << "8. Display Bill\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addMenuItem(menu);
                break;
            case 2:
                addOrder(orders, menu);
                break;
            case 3:
                displayMenu(menu);
                break;
            case 4:
                displayOrders(orders);
                break;
            case 5:
                updateMenuItem(menu);
                break;
            case 6:
                deleteMenuItem(menu);
                break;
            case 7:
                deleteOrder(orders);
                break;
            case 8:
                displayBill(orders);
                break;
            case 9:
                cout << "Exiting the system...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}
