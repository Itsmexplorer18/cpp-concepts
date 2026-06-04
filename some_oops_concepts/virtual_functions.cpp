#include <bits/stdc++.h>
using namespace std;
class parent{
    public:
 virtual void func(){
      cout<<"calling parent class"<<endl;
  }  
};
class child:public parent{
    public:
    void func(){
        cout<<"calling child class"<<endl;
    }
};

int main() {
	// your code goes here
	parent p1;
	child c1;
	parent *ptr1;
	child *ptr2;
	ptr1=&c1; //ptr1=&c1 will call parent without virual
//	ptr2=&c1;
	ptr1->func();
//	ptr2->func();
	return 0;
	
// 	running the code without virtual keyword we will see pt1 pointing to child object will still print the parent funcion not the child because in early binding or compile time the type of the pointer or object calling the function is 
// 	seen here out intention was to call the child class so we will have a way of telling the compiler that we need the child function to be called which is the virtual key word
//  that does an runtime/late binding and sees the object type instead of pointer type
	

}
