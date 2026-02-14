#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
//fetch_add when in memeory ordering 
const int ITERATIONS = 100000000;

// WITH FALSE SHARING - counters share same cache line
struct WithFalseSharing {
    std::atomic<int> counter1;
    std::atomic<int> counter2;  // On same cache line as counter1
};

// WITHOUT FALSE SHARING - counters padded to separate cache lines
struct WithoutFalseSharing {
    alignas(64) std::atomic<int> counter1;
    char padding[64 - sizeof(std::atomic<int>)];  // Padding to next cache line
    alignas(64) std::atomic<int> counter2;
};

void testWithFalseSharing() {
    WithFalseSharing data;
    data.counter1=0;//.store(0);
    data.counter2=0;//.store(0);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    std::thread t1([&]() {
        for (int i = 0; i < ITERATIONS; i++) {
            data.counter1++;//.fetch_add(1, std::memory_order_relaxed);
        }
    });
    
    std::thread t2([&]() {
        for (int i = 0; i < ITERATIONS; i++) {
            data.counter2++;//.fetch_add(1, std::memory_order_relaxed);
        }
    });
    
    t1.join();
    t2.join();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "WITH FALSE SHARING:\n";
    std::cout << "  Time: " << duration.count() << " ms\n";
    std::cout << "  Counter1: " << data.counter1.load() << "\n";
    std::cout << "  Counter2: " << data.counter2.load() << "\n\n";
}

void testWithoutFalseSharing() {
    WithoutFalseSharing data;
    data.counter1=0;//.store(0);
    data.counter2=0;//.store(0);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    std::thread t1([&]() {
        for (int i = 0; i < ITERATIONS; i++) {
            data.counter1++;//.fetch_add(1, std::memory_order_relaxed);
        }
    });
    
    std::thread t2([&]() {
        for (int i = 0; i < ITERATIONS; i++) {
            data.counter2++;//fetch_add(1, std::memory_order_relaxed);
        }
    });
    
    t1.join();
    t2.join();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "WITHOUT FALSE SHARING (with padding):\n";
    std::cout << "  Time: " << duration.count() << " ms\n";
    std::cout << "  Counter1: " << data.counter1.load() << "\n";
    std::cout << "  Counter2: " << data.counter2.load() << "\n\n";
}

int main() {
    std::cout << "Running " << ITERATIONS << " iterations per thread...\n\n";
    // Run with false sharing
    testWithFalseSharing();
    
    // Run without false sharing
    testWithoutFalseSharing();

    return 0;
}
