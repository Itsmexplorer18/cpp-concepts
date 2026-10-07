#include <bits/stdc++.h>
using namespace std;
struct T {
    const char* n;
    T(const char* n) : n(n) { std::cout << "ctor " << n << '\n'; }
    ~T()                    { std::cout << "dtor " << n << '\n'; }
};

void c() {
    T c1("c1");
    throw std::runtime_error("boom");
    T c2("c2");                 // never reached, never constructed
}
void b() {
    T b1("b1");
    c();
    std::cout << "unreachable\n";
}
void a() {
    T a1("a1");
    try {
        T a2("a2");
        b();
    } catch (const std::exception& e) {
        std::cout << "caught: " << e.what() << '\n';
    }
    std::cout << "a continues\n";
}
int main() { a(); }
// output:
// ctor a1
// ctor a2
// ctor b1
// ctor c1
// dtor c1
// dtor b1
// dtor a2
// caught: boom
// a continues
// dtor a1 
// Things to notice:

// c2 never gets a destructor call because it was never constructed. Only fully constructed objects are destroyed.
// a2 is destroyed before the catch body runs. Don't expect to use it inside catch.
// a1 is outside the try, so unwinding stops short of it.

//MULTIPLE LEVEL OF TRY CATCH BLOCKS
void f() {
    T f1("f1");
    try {
        T f2("f2");
        throw std::logic_error("x");
    } catch (const std::runtime_error&) {      // type doesn't match
        std::cout << "wrong handler\n";
    }
}
int main() {
    try { f(); }
    catch (const std::logic_error&) { std::cout << "main caught\n"; }
}
