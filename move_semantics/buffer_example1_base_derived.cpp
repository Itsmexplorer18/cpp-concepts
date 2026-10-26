#include <bits/stdc++.h>
using namespace std;

class Buffer {
    int*   data_;
    size_t size_;
public:
    explicit Buffer(size_t n) : data_(new int[n]), size_(n) {}
    ~Buffer() { delete[] data_; }

    Buffer(const Buffer&)            = delete;
    Buffer& operator=(const Buffer&) = delete;

    Buffer(Buffer&& other) noexcept : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
    }

    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    size_t size() const { return size_; }
};

class DerivedBuffer : public Buffer {
    std::string name_;
    int         id_;
public:
    DerivedBuffer(size_t n, std::string name, int id)
        : Buffer(n), name_(std::move(name)), id_(id) {}

    DerivedBuffer(DerivedBuffer&& other) noexcept
        : Buffer(std::move(other)),
          name_(std::move(other.name_)),
          id_(other.id_) {}

    DerivedBuffer& operator=(DerivedBuffer&& other) noexcept {
        if (this != &other) {
            Buffer::operator=(std::move(other));   // Buffer:: because Derived's = hides it
            name_ = std::move(other.name_);
            id_   = other.id_;
        }
        return *this;
    }
};
