#include <iostream>
#include <vector>
#include <string>


struct MenuItem {
    int id;
    std::string name;
    float price;
};


struct Reservation {
    std::string customerName;
    int tableNumber;
    int numOfPeople;
};

class RestaurantBillingSystem {
private:
    std::vector<MenuItem> menu;

public:

    RestaurantBillingSystem() {
        menu.push_back({1, "Burger", 8.99});
        menu.push_back({2, "Pizza", 12.49});
        menu.push_back({3, "Pasta", 10.99});
        menu.push_back({4, "Salad", 6.49});
        menu.push_back({5, "Soda", 1.99});
    }

    
    void displayMenu() {
        std::cout << "Available Menu Items:\n";
        std::cout << "--------------------------------------------\n";
        for (const auto& item : menu) {
            std::cout << item.id << ". " << item.name << " - $" << item.price << "\n";
        }
        std::cout << "--------------------------------------------\n";
    }

    
    Reservation makeReservation() {
        Reservation reservation;
        std::cout << "Enter your name: ";
        std::cin.ignore();  
        std::getline(std::cin, reservation.customerName);

        std::cout << "Enter table number: ";
        std::cin >> reservation.tableNumber;

        std::cout << "Enter number of people: ";
        std::cin >> reservation.numOfPeople;

        return reservation;
    }

    
    float placeOrder() {
        displayMenu();

        int choice;
        float totalAmount = 0.0;
        std::vector<int> selectedItems;

        std::cout << "Enter the IDs of the items you want to order (0 to finish):\n";
        while (true) {
            std::cout << "Item ID: ";
            std::cin >> choice;
            if (choice == 0) {
                break;  
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

        return totalAmount;
    }

    
    void displayBill(const Reservation& reservation, float totalAmount) {
        std::cout << "\nReservation Confirmation:\n";
        std::cout << "--------------------------------------------\n";
        std::cout << "Customer Name: " << reservation.customerName << "\n";
        std::cout << "Table Number: " << reservation.tableNumber << "\n";
        std::cout << "Number of People: " << reservation.numOfPeople << "\n";
        std::cout << "--------------------------------------------\n";
        std::cout << "Order Summary:\n";
        for (int itemId : reservation.selectedItems) {
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

int main() {
    RestaurantBillingSystem system;

    std::cout << "Welcome to the Restaurant Billing System\n";
    std::cout << "--------------------------------------------\n";

    
    Reservation reservation = system.makeReservation();

    
    float totalAmount = system.placeOrder();

    
    system.displayBill(reservation, totalAmount);

    return 0;
}
