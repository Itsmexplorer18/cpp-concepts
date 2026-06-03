#include <iostream>
#include <vector>

template <typename T>
void Print(T number) {
    std::cout << number << std::endl;
}

template <typename T>
void Print(T* ptr) {
    std::cout << "pointer: " << *ptr << std::endl;
}

template <typename T>
void Print(const std::vector<T>& vec) {
    std::cout << "vector: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    Print(42);
    int number{23};
    Print(&number);
    Print(std::vector{1, 2, 3});
    return 0;
}
