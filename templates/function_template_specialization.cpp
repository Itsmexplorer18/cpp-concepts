#include <iostream>

struct Object {
    Object() = default;
    Object(const Object& other) { std::cout << "copy happened\n"; }
};

template <typename T>
void Process(T object) {
    std::cout << "base template\n";
}

template <>
void Process(const Object& object) {
    std::cout << "specialization\n";
}

int main() {
    const Object object;

    // deduction picks T=Object, so Process(Object) by value
    // specialization is Process(const Object&) - different signature, ignored
    // result: copy + base template called
    Process(object);

    // forcing T=const Object& manually, now matches specialization exactly
    // result: no copy, specialization called
    Process<const Object&>(object);

    return 0;
}
