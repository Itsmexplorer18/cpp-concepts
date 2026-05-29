/*
Why it can't be a member function
When you write a member function operator<<, C++ calls it as:
cppleft.operator<<(right)
So for cout << t to work as a member, it would have to be a member of ostream — because cout is on the left. You don't own ostream. You can't add methods to it.
you can make it public getter  member function but then everyone would be able to call it 
// Problem: getCelsius() is now callable by ANY code everywhere.
// You've widened access to the whole world just to serve operator<<.
  */
class Temperature {
    double celsius;
public:
    Temperature(double c) : celsius(c) {}
    friend std::ostream& operator<<(std::ostream& os, const Temperature& t);
};

std::ostream& operator<<(std::ostream& os, const Temperature& t) {
    os << t.celsius << "°C";   // granted directly — no getter needed
    return os;
}
// Only this specific function gets in.
// No getter polluting the public interface.
// Outside code still cannot read celsius.
