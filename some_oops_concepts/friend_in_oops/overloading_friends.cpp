#include <iostream>
//remmeber as friend doesnt have a caller object +1 number of arguments have to be passed to the overloading implementation 
class Vec2 {
    double x, y;
public:
    Vec2(double x, double y) : x(x), y(y) {}
    // UNARY OPERATOR-  —  member version   
    // As a member, the single operand IS the object (this).
    //   -v   →   v.operator-()
    Vec2 operator-() const {
        return Vec2(-x, -y);
    }

    // BINARY OPERATOR+  —  member version
    // Binary means two operands: a + b
    // As a member, the LEFT operand is the object (this).
    // The RIGHT operand is passed as the argument.
    //
    //   a + b   →   a.operator+(b)
    //
    Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }

    // FRIEND VERSIONS — declared here so they can access x, y
    // As a friend FREE function, there is no "this" at all.
    // BOTH operands must be passed explicitly as parameters.
    // The class grants these functions private access.
    //   -v     →   operator-(v)          — one parameter
    //   a + b  →   operator+(a, b)       — two parameters
    friend Vec2 operator-(const Vec2& v);              // unary
    friend Vec2 operator+(const Vec2& a, const Vec2& b); // binary (shadows member above for demo)

    friend std::ostream& operator<<(std::ostream& os, const Vec2& v);
};


// FRIEND UNARY OPERATOR-  —  free function definition
// No object calls this. It is a plain function.
// The single operand is passed in as a parameter.
Vec2 operator-(const Vec2& v) {
    //       v.x  not  this->x  — because there is no this
    return Vec2(-v.x, -v.y);
}

// FRIEND BINARY OPERATOR+  —  free function definition
// No object calls this. Both sides are explicit parameters.
// Member version:  x + other.x  where x came from this
// Friend version:  a.x + b.x   — both sides named explicitly
Vec2 operator+(const Vec2& a, const Vec2& b) {
    //        a.x          b.x  — both are parameters, neither is 'this'
    return Vec2(a.x + b.x, a.y + b.y);
}

// FRIEND operator<<  —  same rule: both operands are parameters
// ostream is on the left so it cannot be a member of Vec2.
// As a friend free function both os and v are explicit parameters.
std::ostream& operator<<(std::ostream& os, const Vec2& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}
int main() {
    Vec2 a(1.0, 2.0);
    Vec2 b(3.0, 4.0);

    // Unary minus
    // member call :   a.operator-()
    // friend call :   operator-(a)
    Vec2 neg = -a;
    std::cout << "  -a = " << neg << "\n";   // (-1, -2)

    // Binary plus
    // member call :   a.operator+(b)
    // friend call :   operator+(a, b)
    Vec2 sum = a + b;
    std::cout << "a+b = " << sum << "\n";   // (4, 6)

    return 0;
}
/*
WHERE WOULD YOU WANT TO USE THIS OVER MEMBER??
class Meters {
    double val;
public:
    Meters(double v) : val(v) {}   // implicit conversion from double

    // member operator+
    Meters operator+(const Meters& other) const {
        return Meters(val + other.val);
    }
};

Meters m(5.0);

m + 2.0;    // works — 2.0 implicitly converts to Meters, sits on the right
2.0 + m;    // FAILS — 2.0 is on the left, compiler tries 2.0.operator+(m)
            //         double has no operator+ that knows about Meters

fRIEND FIXES THAT -------------------------------------------------------------------------

class Meters {
    double val;
public:
    Meters(double v) : val(v) {}

    friend Meters operator+(const Meters& a, const Meters& b) {
        return Meters(a.val + b.val);
    }
};

Meters m(5.0);

m + 2.0;    // works — 2.0 converts to Meters for parameter b
2.0 + m;    // works — 2.0 converts to Meters for parameter a
            // both sides are just parameters now, treated symmetrically
UNCOMMENT THE CODE AND TRY 
*/
