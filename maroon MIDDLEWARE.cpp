#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>

// Class to represent a Menu Item
class MenuItem {
public:
    int itemID;
    std::string name;
    double price;

    MenuItem(int id, std::string name, double price) : itemID(id), name(name), price(price) {}

    // Display menu item details
    void display() {
        std::cout << "Item ID: " << itemID << ", Name: " << name << ", Price: $" << price << std::endl;
    }
};

// Class for the restaurant's menu (simulated database)
class MenuDatabase {
private:
    std::unordered_map<int, MenuItem> menuItems;

public:
    MenuDatabase() {
        // Sample menu items
        menuItems[1] = MenuItem(1, "Burger", 8.99);
        menuItems[2] = MenuItem(2, "Pizza", 12.49);
        menuItems[3] = MenuItem(3, "Pasta", 10.99);
        menuItems[4] = MenuItem(4, "Salad", 6.49);
        menuItems[5] = MenuItem(5, "Soda", 1.99);
    }

    // Retrieve a menu item by its ID
    MenuItem* getItem(int itemID) {
        if (menuItems.find(itemID) != menuItems.end()) {
            return &menuItems[itemID];
        }
        return nullptr; // Item not found
    }

    // List all menu items
    void listAllMenuItems() {
        for (const auto& pair : menuItems) {
            pair.second.display();
        }
    }
};

// Class for the middleware (handles order processing and billing logic)
class RestaurantBillingMiddleware {
private:
    MenuDatabase& menuDB;
    double discountPercentage = 0.0;  // Discount (in percent)
    double taxRate = 0.08;            // Tax rate (8%)

public:
    RestaurantBillingMiddleware(MenuDatabase& db) : menuDB(db) {}

    // Set discount percentage
    void setDiscount(double discount) {
        discountPercentage = discount;
    }

    // Calculate the total bill for an order (without discount)
    double calculateBill(const std::unordered_map<int, int>& order) {
        double total = 0.0;
        for (const auto& pair : order) {
            int itemID = pair.first;
            int quantity = pair.second;
            MenuItem* item = menuDB.getItem(itemID);
            if (item != nullptr) {
                total += item->price * quantity;
            }
        }
        return total;
    }

    // Apply discount and tax to the total bill
    double applyDiscountAndTax(double total) {
        double discountAmount = total * (discountPercentage / 100);
        double discountedTotal = total - discountAmount;
        double taxAmount = discountedTotal * taxRate;
        double finalAmount = discountedTotal + taxAmount;
        return finalAmount;
    }

    // Process an order and return the final bill
    void processOrder(const std::unordered_map<int, int>& order) {
        // Calculate the total bill
        double total = calculateBill(order);
        std::cout << "\nTotal before discount and tax: $" << std::fixed << std::setprecision(2) << total << std::endl;

        // Apply discount and tax
        double finalAmount = applyDiscountAndTax(total);
        std::cout << "Final amount after discount and tax: $" << std::fixed << std::setprecision(2) << finalAmount << std::endl;
    }
};

// User interface class (simulates user interaction)
class RestaurantBillingSystem {
private:
    RestaurantBillingMiddleware& middleware;

public:
    RestaurantBillingSystem(RestaurantBillingMiddleware& mw) : middleware(mw) {}

    // Simulate user actions
    void run() {
        int choice;
        std::unordered_map<int, int> order;  // Stores itemID and quantity for the order

        while (true) {
            std::cout << "\n==== Restaurant Billing System ====" << std::endl;
            std::cout << "1. List All Menu Items" << std::endl;
            std::cout << "2. Add Item to Order" << std::endl;
            std::cout << "3. Set Discount" << std::endl;
            std::cout << "4. Process Order and Generate Bill" << std::endl;
            std::cout << "5. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "\nAvailable Menu Items:\n";
                middleware.menuDB.listAllMenuItems();
            }
            else if (choice == 2) {
                int itemID, quantity;
                std::cout << "\nEnter item ID to add: ";
                std::cin >> itemID;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                // Add item to order
                order[itemID] += quantity;
                std::cout << "Item added to the order." << std::endl;
            }
            else if (choice == 3) {
                double discount;
                std::cout << "\nEnter discount percentage: ";
                std::cin >> discount;
                middleware.setDiscount(discount);
                std::cout << "Discount set to " << discount << "%" << std::endl;
            }
            else if (choice == 4) {
                std::cout << "\nProcessing order...\n";
                middleware.processOrder(order);
            }
            else if (choice == 5) {
                std::cout << "Exiting the system. Thank you!" << std::endl;
                break;
            }
            else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }
};

int main() {
    // Initialize database and middleware
    MenuDatabase db;
    RestaurantBillingMiddleware middleware(db);

    // Initialize the system and run
    RestaurantBillingSystem system(middleware);
    system.run();

    return 0;
}
