#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>


struct MenuItem {
    std::string name;
    double price;
    
    MenuItem(const std::string& name, double price) : name(name), price(price) {}
};


struct MenuItemHash {
    std::size_t operator()(const MenuItem& item) const {
        std::hash<std::string> hash_fn;
        return hash_fn(item.name);
    }
};


class MenuCache {
private:
    std::unordered_map<MenuItem, double, MenuItemHash> cache;
    
public:
    
    bool isCached(const MenuItem& item) {
        return cache.find(item) != cache.end();
    }

    
    double getCache(const MenuItem& item) {
        return cache[item];
    }

    void addToCache(const MenuItem& item, double price) {
        cache[item] = price;
    }

    
    void printCache() {
        std::cout << "Cached Menu Items:\n";
        for (const auto& pair : cache) {
            std::cout << pair.first.name << ": $" << pair.second << "\n";
        }
    }
};


double fetchItemPrice(const MenuItem& item) {
    std::cout << "Fetching price for item: " << item.name << "...\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));

    
    if (item.name == "Burger") return 5.99;
    if (item.name == "Pasta") return 8.99;
    if (item.name == "Pizza") return 10.99;
    if (item.name == "Salad") return 4.99;
    
    return 0.0;
}


double calculateTotal(const std::vector<MenuItem>& order, MenuCache& cache) {
    double total = 0.0;
    
    for (const auto& item : order) {
        
        if (cache.isCached(item)) {
            std::cout << "Item " << item.name << " found in cache. Price: $" << cache.getCache(item) << "\n";
            total += cache.getCache(item);
        } else {
            
            double price = fetchItemPrice(item);
            cache.addToCache(item, price);  
            total += price;
            std::cout << "Item " << item.name << " not in cache. Fetched price: $" << price << "\n";
        }
    }
    
    return total;
}

int main() {
    
    MenuCache menuCache;

    
    std::vector<MenuItem> menu = {
        MenuItem("Burger", 0.0),  
        MenuItem("Pasta", 0.0),   
        MenuItem("Pizza", 0.0),   
        MenuItem("Salad", 0.0)    
    };

    
    std::vector<MenuItem> order = {
        MenuItem("Burger", 0.0),  
        MenuItem("Pasta", 0.0),   
        MenuItem("Pizza", 0.0)    
    };

    
    double total = calculateTotal(order, menuCache);
    
    
    std::cout << "\nTotal Bill: $" << std::fixed << std::setprecision(2) << total << "\n";
    
    
    menuCache.printCache();

    return 0;
}
