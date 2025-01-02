#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

// Define message types for the restaurant billing system
enum class MessageType {
    OrderReceived,
    BillGenerated,
    PaymentProcessed
};

// Structure to represent a message in the queue
struct Message {
    MessageType type;
    std::string data;
};

// Message Queue class
class MessageQueue {
private:
    std::queue<Message> queue;
    std::mutex mtx;
    std::condition_variable cv;

public:
    // Push a message to the queue
    void push(const Message& msg) {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(msg);
        cv.notify_all();
    }

    // Pop a message from the queue
    Message pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return !queue.empty(); });
        
        Message msg = queue.front();
        queue.pop();
        return msg;
    }
};

// Order taking process (worker thread)
void orderTakingWorker(MessageQueue& msgQueue) {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulating order taking delay
    Message msg = {MessageType::OrderReceived, "Order received for 2 Burgers and 1 Fries"};
    msgQueue.push(msg);
    std::cout << "Order received, message added to queue\n";
}

// Bill generation process (worker thread)
void billGenerationWorker(MessageQueue& msgQueue) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulating bill generation delay
    Message msg = {MessageType::BillGenerated, "Total bill: $18.50"};
    msgQueue.push(msg);
    std::cout << "Bill generated, message added to queue\n";
}

// Payment processing process (worker thread)
void paymentProcessingWorker(MessageQueue& msgQueue) {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulating payment processing delay
    Message msg = {MessageType::PaymentProcessed, "Payment of $18.50 processed successfully"};
    msgQueue.push(msg);
    std::cout << "Payment processed, message added to queue\n";
}

// Message handling process (consumer thread)
void messageHandler(MessageQueue& msgQueue) {
    while (true) {
        Message msg = msgQueue.pop();
        
        switch (msg.type) {
            case MessageType::OrderReceived:
                std::cout << "Handling order message: " << msg.data << "\n";
                break;
            case MessageType::BillGenerated:
                std::cout << "Handling bill message: " << msg.data << "\n";
                break;
            case MessageType::PaymentProcessed:
                std::cout << "Handling payment message: " << msg.data << "\n";
                break;
            default:
                std::cout << "Unknown message type\n";
        }
        
        // For simulation, let's assume we're done when all messages have been handled
        if (msg.data == "Payment of $18.50 processed successfully") {
            break;
        }
    }
}

int main() {
    MessageQueue msgQueue;

    // Start worker threads (simulate order taking, bill generation, and payment processing)
    std::thread orderTakingThread(orderTakingWorker, std::ref(msgQueue));
    std::thread billGenerationThread(billGenerationWorker, std::ref(msgQueue));
    std::thread paymentProcessingThread(paymentProcessingWorker, std::ref(msgQueue));

    // Start message handler thread (consume messages from the queue)
    std::thread messageHandlerThread(messageHandler, std::ref(msgQueue));

    // Wait for threads to finish
    orderTakingThread.join();
    billGenerationThread.join();
    paymentProcessingThread.join();
    messageHandlerThread.join();

    std::cout << "Restaurant billing system completed successfully.\n";

    return 0;
}
