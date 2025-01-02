#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>
#include <cstring>

#define PORT 8080
#define MAX_CLIENTS 5

// Sample menu data
struct MenuItem {
    std::string name;
    float price;
};

class RestaurantBillingServer {
public:
    void start() {
        int serverSocket, clientSocket;
        struct sockaddr_in serverAddr, clientAddr;
        socklen_t addrSize;

        // Sample menu items
        std::vector<MenuItem> menu = {
            {"Burger", 8.99},
            {"Pizza", 12.49},
            {"Pasta", 10.99},
            {"Salad", 6.49},
            {"Soda", 1.99}
        };

        // Create socket
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0) {
            std::cerr << "Socket creation failed!" << std::endl;
            return;
        }

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(PORT);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        // Bind socket to address
        if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            std::cerr << "Binding failed!" << std::endl;
            return;
        }

        // Listen for incoming connections
        if (listen(serverSocket, MAX_CLIENTS) == 0) {
            std::cout << "Server listening on port " << PORT << std::endl;
        } else {
            std::cerr << "Listening failed!" << std::endl;
            return;
        }

        addrSize = sizeof(clientAddr);
        while (true) {
            // Accept client connection
            clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);
            if (clientSocket < 0) {
                std::cerr << "Connection failed!" << std::endl;
                continue;
            }

            std::cout << "Client connected!" << std::endl;

            // Receive request from the client
            char buffer[1024] = {0};
            read(clientSocket, buffer, sizeof(buffer));

            // If client requests the menu
            if (strcmp(buffer, "view_menu") == 0) {
                std::string menuDetails = "Menu:\n";
                for (size_t i = 0; i < menu.size(); ++i) {
                    menuDetails += std::to_string(i+1) + ". " + menu[i].name + " - $" + std::to_string(menu[i].price) + "\n";
                }
                send(clientSocket, menuDetails.c_str(), menuDetails.length(), 0);
            }
            // If client requests to calculate the bill (e.g., "calculate_bill 1 2")
            else if (strncmp(buffer, "calculate_bill", 14) == 0) {
                // Extract item indices and calculate bill
                int totalItems = 0;
                float totalAmount = 0.0;
                char* token = strtok(buffer + 15, " ");
                while (token != nullptr) {
                    int itemIndex = std::stoi(token) - 1;
                    if (itemIndex >= 0 && itemIndex < menu.size()) {
                        totalAmount += menu[itemIndex].price;
                        ++totalItems;
                    }
                    token = strtok(nullptr, " ");
                }

                // Send bill to client
                std::string billMessage = "Total items: " + std::to_string(totalItems) + "\nTotal Bill: $" + std::to_string(totalAmount);
                send(clientSocket, billMessage.c_str(), billMessage.length(), 0);
            } else {
                std::string errorMessage = "Invalid request.";
                send(clientSocket, errorMessage.c_str(), errorMessage.length(), 0);
            }

            close(clientSocket);
            std::cout << "Client disconnected!" << std::endl;
        }

        close(serverSocket);
    }
};

int main() {
    RestaurantBillingServer server;
    server.start();
    return 0;
}
