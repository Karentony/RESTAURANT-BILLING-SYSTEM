#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

class LRUCache {
private:
    int capacity;
    std::list<std::pair<int, std::string>> cache; // Doubly linked list to store (orderID, orderDetails)
    std::unordered_map<int, std::list<std::pair<int, std::string>>::iterator> map; // HashMap to store orderID and its position in the list

public:
    LRUCache(int cap) : capacity(cap) {}

    // Access an order by its orderID
    std::string get(int orderID) {
        if (map.find(orderID) == map.end()) {
            return "Order not found"; // Return if orderID is not in the cache
        }
        // Move the accessed order to the front (most recent)
        cache.splice(cache.begin(), cache, map[orderID]);
        return map[orderID]->second; // Return the order details
    }

    // Add or update an order in the cache
    void put(int orderID, const std::string& orderDetails) {
        if (map.find(orderID) != map.end()) {
            // If the order is already in cache, update it and move to front
            cache.splice(cache.begin(), cache, map[orderID]);
            map[orderID]->second = orderDetails;
        } else {
            // If the cache is full, remove the least recently used order
            if (cache.size() == capacity) {
                // Remove the least recently used order (back of the list)
                int oldOrderID = cache.back().first;
                map.erase(oldOrderID);
                cache.pop_back();
            }
            // Insert the new order at the front
            cache.push_front({orderID, orderDetails});
            map[orderID] = cache.begin();
        }
    }

    // Display the cache (for testing purposes)
    void displayCache() {
        for (const auto& pair : cache) {
            std::cout << "Order ID: " << pair.first << ", Details: " << pair.second << std::endl;
        }
    }
};

int main() {
    // Create an LRU cache with capacity 3 for restaurant orders
    LRUCache orderCache(3);

    // Add some orders to the cache
    orderCache.put(101, "Burger, Fries, Soda - $12.50");
    orderCache.put(102, "Pasta, Salad, Wine - $18.00");
    orderCache.put(103, "Pizza, Garlic Bread - $14.30");

    // Display the cache
    std::cout << "Current cache:" << std::endl;
    orderCache.displayCache();

    // Access an order (this will move it to the front)
    std::cout << "\nAccessing Order 101: " << orderCache.get(101) << std::endl;

    // Add another order, which will evict the least recently used one (Order 102)
    orderCache.put(104, "Steak, Mashed Potatoes - $22.00");

    // Display the updated cache
    std::cout << "\nUpdated cache after adding Order 104:" << std::endl;
    orderCache.displayCache();

    // Access another order
    std::cout << "\nAccessing Order 103: " << orderCache.get(103) << std::endl;

    // Add another order, which will evict the least recently used one (Order 103)
    orderCache.put(105, "Chicken Tacos, Guacamole - $16.00");

    // Final cache display
    std::cout << "\nFinal cache after adding Order 105:" << std::endl;
    orderCache.displayCache();

    return 0;
}
