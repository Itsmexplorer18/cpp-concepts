#include <bits/stdc++.h>
using namespace std;

class value{
    public:
    int x;
    value() : x(0) {}  
    value(int x){
        this->x=x;
    }
    int operator()(int val){
        x*=val;
        return x;
    }
};
int main() {
	value v(1);
	cout<<v(42)<<endl;
	cout<<v(42)<<endl;
	cout<<v(42)<<endl;

	return 0;

   
}
//a functor is a function object that stores the state and is implemented or we can say a class that defines the () overloads the () operator is a functor they are the bulding blocks behind lamdas and used in stl
