#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

constexpr size_t N = 1'000'000;

void linearAccess(std::vector<int>& data) {
    for (size_t i = 0; i < data.size(); ++i)
        data[i] *= 2;
}

void stridedAccess(std::vector<int>& data, size_t stride) {
    for (size_t i = 0; i < data.size(); i += stride)
        data[i] *= 2;
}

struct Node {
    int value;
    Node* next;
};

Node* createLinkedList(size_t n) {
    std::vector<Node*> nodes(n);
    for (auto& ptr : nodes)
        ptr = new Node{0, nullptr};

    std::shuffle(nodes.begin(), nodes.end(), std::mt19937{std::random_device{}()});

    for (size_t i = 0; i < n - 1; ++i)
        nodes[i]->next = nodes[i + 1];
    nodes[n - 1]->next = nullptr;
    return nodes[0];
}

void pointerChasing(Node* head) {
    while (head) {
        head->value *= 2;
        head = head->next;
    }
}

int main() {
    std::vector<int> data(N, 1);

    auto start = std::chrono::high_resolution_clock::now();
    linearAccess(data);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Linear access: "
              << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    std::vector<size_t> strides = {64, 128, 256, 512};
    for (size_t stride : strides) {
        data.assign(N, 1);
        start = std::chrono::high_resolution_clock::now();
        stridedAccess(data, stride);
        end = std::chrono::high_resolution_clock::now();
        std::cout << "Stride " << stride << ": "
                  << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";
    }

    Node* head = createLinkedList(1'000'000);
    start = std::chrono::high_resolution_clock::now();
    pointerChasing(head);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Pointer chasing: "
              << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";
}
