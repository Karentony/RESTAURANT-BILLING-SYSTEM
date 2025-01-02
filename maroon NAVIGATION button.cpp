#include <iostream>
#include <vector>
#include <string>

// Structure to represent menu items
struct MenuItem {
    int id;
    std::string name;
    float price;
};

// Class representing the Restaurant Billing System
class RestaurantBillingSystem {
private:
    std::vector<MenuItem> menu;

public:
    // Constructor to initialize sample menu items
    RestaurantBillingSystem() {
        menu.push_back({1, "Burger", 8.99});
        menu.push_back({2, "Pizza", 12.49});
        menu.push_back({3, "Pasta", 10.99});
        menu.push_back({4, "Salad", 6.49});
        menu.push_back({5, "Soda", 1.99});
    }

    // Method to display the menu
    void displayMenu() {
        std::cout << "\nAvailable Menu Items:\n";
        std::cout << "--------------------------------------------\n";
        for (const auto& item : menu) {
            std::cout << item.id << ". " << item.name << " - $" << item.price << "\n";
        }
        std::cout << "--------------------------------------------\n";
    }

    // Method to place an order and calculate the total bill
    void placeOrder() {
        int choice;
        float totalAmount = 0.0;
        std::vector<int> selectedItems;

        displayMenu();

        std::cout << "Enter the IDs of the items you want to order (0 to finish):\n";
        while (true) {
            std::cout << "Item ID: ";
            std::cin >> choice;
            if (choice == 0) {
                break;  // Exit the loop when the user enters 0
            }

            bool itemFound = false;
            for (const auto& item : menu) {
                if (item.id == choice) {
                    selectedItems.push_back(choice);
                    totalAmount += item.price;
                    itemFound = true;
                    break;
                }
            }

            if (!itemFound) {
                std::cout << "Invalid item ID, please try again.\n";
            }
        }

        // Display the bill
        std::cout << "\nBill Summary:\n";
        for (int itemId : selectedItems) {
            for (const auto& item : menu) {
                if (item.id == itemId) {
                    std::cout << item.name << " - $" << item.price << "\n";
                }
            }
        }
        std::cout << "--------------------------------------------\n";
        std::cout << "Total Amount: $" << totalAmount << "\n";
        std::cout << "--------------------------------------------\n";
    }
};

// Main function to display navigation
int main() {
    RestaurantBillingSystem system;
    int choice;

    std::cout << "Welcome to the Restaurant Billing System\n";
    while (true) {
        std::cout << "\nNavigation Menu:\n";
        std::cout << "1. View Available Menu\n";
        std::cout << "2. Place an Order\n";
        std::cout << "3. Exit\n";
        std::cout << "Please select an option (1-3): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                system.displayMenu();
                break;
            case 2:
                system.placeOrder();
                break;
            case 3:
                std::cout << "Exiting the system. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid option, please try again.\n";
                break;
        }
    }
}
