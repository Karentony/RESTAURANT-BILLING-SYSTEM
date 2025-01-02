#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>

// User class representing a system user (admin or customer)
class User {
public:
    std::string username;
    std::string password;
    std::string role; // "admin" or "customer"

    User(std::string username, std::string password, std::string role)
        : username(username), password(password), role(role) {}

    bool checkPassword(const std::string& passwordInput) {
        return password == passwordInput;
    }
};

// Simple User Authentication and Authorization System
class AuthSystem {
private:
    std::unordered_map<std::string, User> users;

public:
    AuthSystem() {
        // Pre-populate the system with users (admin and customer)
        users["admin"] = User("admin", "admin123", "admin");
        users["customer1"] = User("customer1", "customer123", "customer");
        users["customer2"] = User("customer2", "customer123", "customer");
    }

    // Authenticate a user by username and password
    User* authenticate(const std::string& username, const std::string& password) {
        if (users.find(username) != users.end() && users[username].checkPassword(password)) {
            return &users[username];
        }
        return nullptr; // Invalid credentials
    }
};

// Class for the restaurant billing system
class RestaurantBillingSystem {
private:
    AuthSystem& authSystem;
    User* loggedInUser = nullptr;

public:
    RestaurantBillingSystem(AuthSystem& authSys) : authSystem(authSys) {}

    // Login method
    bool login(const std::string& username, const std::string& password) {
        loggedInUser = authSystem.authenticate(username, password);
        return loggedInUser != nullptr;
    }

    // Logout method
    void logout() {
        loggedInUser = nullptr;
        std::cout << "Logged out successfully!" << std::endl;
    }

    // Check if the current user is an admin
    bool isAdmin() {
        return loggedInUser && loggedInUser->role == "admin";
    }

    // Function available only for admins
    void manageMenu() {
        if (!isAdmin()) {
            std::cout << "You do not have permission to manage the menu." << std::endl;
            return;
        }
        std::cout << "Managing menu... (only accessible by admins)" << std::endl;
        // Admin specific tasks like adding or removing menu items
    }

    // Function available for both customers and admins
    void viewMenu() {
        std::cout << "Displaying menu..." << std::endl;
        // Display the menu items (simulating a simple menu)
        std::cout << "1. Burger - $8.99" << std::endl;
        std::cout << "2. Pizza - $12.49" << std::endl;
        std::cout << "3. Pasta - $10.99" << std::endl;
        std::cout << "4. Salad - $6.49" << std::endl;
        std::cout << "5. Soda - $1.99" << std::endl;
    }

    // Function available only for customers
    void placeOrder() {
        if (isAdmin()) {
            std::cout << "Admins cannot place orders." << std::endl;
            return;
        }
        std::cout << "Placing an order... (only accessible by customers)" << std::endl;
        // Simulate customer placing an order
    }

    // Function to display menu based on the role
    void displayMenu() {
        if (loggedInUser == nullptr) {
            std::cout << "Please log in to access the system." << std::endl;
            return;
        }

        std::cout << "\n==== Restaurant Billing System ====" << std::endl;
        if (isAdmin()) {
            std::cout << "Hello Admin! You have the following options:" << std::endl;
            std::cout << "1. Manage Menu" << std::endl;
            std::cout << "2. View Menu" << std::endl;
        } else {
            std::cout << "Hello " << loggedInUser->username << "! You have the following options:" << std::endl;
            std::cout << "1. View Menu" << std::endl;
            std::cout << "2. Place Order" << std::endl;
        }
        std::cout << "3. Logout" << std::endl;
        std::cout << "Enter your choice: ";
    }

    // Execute the chosen option
    void executeChoice(int choice) {
        if (choice == 1) {
            if (isAdmin()) {
                manageMenu();
            } else {
                viewMenu();
            }
        } else if (choice == 2) {
            if (isAdmin()) {
                manageMenu();
            } else {
                placeOrder();
            }
        } else if (choice == 3) {
            logout();
        } else {
            std::cout << "Invalid choice, please try again." << std::endl;
        }
    }
};

int main() {
    // Initialize authentication system
    AuthSystem authSystem;
    RestaurantBillingSystem system(authSystem);

    std::string username, password;
    int choice;

    // Simulate user login
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (!system.login(username, password)) {
        std::cout << "Invalid username or password!" << std::endl;
        return 1;
    }

    // Loop for menu after login
    while (true) {
        system.displayMenu();
        std::cin >> choice;
        system.executeChoice(choice);
        if (choice == 3) {
            break;
        }
    }

    return 0;
}
