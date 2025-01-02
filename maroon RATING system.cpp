#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class RestaurantRatingSystem {
private:
    struct Rating {
        std::string customerName;
        int foodRating;     // Rating for food (1-5)
        int serviceRating;  // Rating for service (1-5)
        int ambianceRating; // Rating for ambiance (1-5)
    };
    
    std::vector<Rating> ratingList;

public:
    // Method for a customer to submit a rating
    void submitRating() {
        std::string name;
        int foodRating, serviceRating, ambianceRating;

        std::cout << "Enter your name: ";
        std::cin.ignore();  // Clear the input buffer
        std::getline(std::cin, name);

        // Collecting ratings for food, service, and ambiance (must be between 1 and 5)
        do {
            std::cout << "Enter your food rating (1-5): ";
            std::cin >> foodRating;
        } while (foodRating < 1 || foodRating > 5);
        
        do {
            std::cout << "Enter your service rating (1-5): ";
            std::cin >> serviceRating;
        } while (serviceRating < 1 || serviceRating > 5);
        
        do {
            std::cout << "Enter your ambiance rating (1-5): ";
            std::cin >> ambianceRating;
        } while (ambianceRating < 1 || ambianceRating > 5);
        
        // Store the rating in the rating list
        Rating newRating = {name, foodRating, serviceRating, ambianceRating};
        ratingList.push_back(newRating);

        std::cout << "Thank you for your ratings!\n" << std::endl;
    }

    // Method for viewing all customer ratings (for the admin)
    void viewRatings() {
        if (ratingList.empty()) {
            std::cout << "No ratings have been submitted yet.\n" << std::endl;
        } else {
            std::cout << "\nAll Customer Ratings:\n";
            std::cout << "-------------------------------------------------\n";
            for (const auto& rating : ratingList) {
                std::cout << "Customer: " << rating.customerName << "\n";
                std::cout << "Food Rating: " << rating.foodRating << " stars\n";
                std::cout << "Service Rating: " << rating.serviceRating << " stars\n";
                std::cout << "Ambiance Rating: " << rating.ambianceRating << " stars\n";
                std::cout << "-------------------------------------------------\n";
            }
        }
    }

    // Method to calculate and display average ratings
    void displayAverageRatings() {
        if (ratingList.empty()) {
            std::cout << "No ratings available to calculate averages.\n" << std::endl;
            return;
        }

        int foodSum = 0, serviceSum = 0, ambianceSum = 0;

        // Calculate the sum of ratings for each category
        for (const auto& rating : ratingList) {
            foodSum += rating.foodRating;
            serviceSum += rating.serviceRating;
            ambianceSum += rating.ambianceRating;
        }

        // Calculate and display average ratings for food, service, and ambiance
        double avgFood = static_cast<double>(foodSum) / ratingList.size();
        double avgService = static_cast<double>(serviceSum) / ratingList.size();
        double avgAmbiance = static_cast<double>(ambianceSum) / ratingList.size();

        std::cout << "Average Ratings:\n";
        std::cout << "Food: " << avgFood << " stars\n";
        std::cout << "Service: " << avgService << " stars\n";
        std::cout << "Ambiance: " << avgAmbiance << " stars\n" << std::endl;
    }

    // Method to save ratings to a file
    void saveRatingsToFile() {
        std::ofstream outFile("restaurant_ratings.txt", std::ios::app);

        if (!outFile) {
            std::cout << "Error opening file to save ratings.\n" << std::endl;
            return;
        }

        // Save each rating to the file
        for (const auto& rating : ratingList) {
            outFile << "Customer: " << rating.customerName << "\n";
            outFile << "Food Rating: " << rating.foodRating << " stars\n";
            outFile << "Service Rating: " << rating.serviceRating << " stars\n";
            outFile << "Ambiance Rating: " << rating.ambianceRating << " stars\n";
            outFile << "-------------------------------------------------\n";
        }

        std::cout << "Ratings have been saved!\n" << std::endl;
    }

    // Method to load ratings from a file
    void loadRatingsFromFile() {
        std::ifstream inFile("restaurant_ratings.txt");

        if (!inFile) {
            std::cout << "No previous ratings found.\n" << std::endl;
            return;
        }

        std::string name;
        int foodRating, serviceRating, ambianceRating;

        // Read ratings from the file
        while (std::getline(inFile, name)) {
            inFile >> foodRating;
            inFile >> serviceRating;
            inFile >> ambianceRating;
            inFile.ignore();  // Ignore the newline character after reading ratings
            inFile.ignore();  // Ignore the separator line

            Rating newRating = {name.substr(10), foodRating, serviceRating, ambianceRating};  // Remove "Customer: "
            ratingList.push_back(newRating);
        }

        std::cout << "Ratings loaded from file.\n" << std::endl;
    }
};

int main() {
    RestaurantRatingSystem system;
    int choice;

    // Load ratings from the file at the start
    system.loadRatingsFromFile();

    while (true) {
        std::cout << "Restaurant Billing System\n";
        std::cout << "1. Submit Rating\n";
        std::cout << "2. View All Ratings (Admin)\n";
        std::cout << "3. Display Average Ratings (Admin)\n";
        std::cout << "4. Save Ratings to File\n";
        std::cout << "5. Exit\n";
        std::cout << "Please select an option (1-5): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                system.submitRating();
                break;
            case 2:
                system.viewRatings();
                break;
            case 3:
                system.displayAverageRatings();
                break;
            case 4:
                system.saveRatingsToFile();
                break;
            case 5:
                std::cout << "Exiting the system. Thank you for using the service!\n";
                return 0;
            default:
                std::cout << "Invalid option, please try again.\n";
                break;
        }
    }
}
