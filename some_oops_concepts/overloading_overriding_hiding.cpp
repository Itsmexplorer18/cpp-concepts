#include <bits/stdc++.h>
using namespace std;
class parent{
  public:  
  virtual void function1(){
      cout<<"parents called"<<endl;
  };
  void function1(int x){
      cout<<x<<endl;
  }
   void function2(int x){
      cout<<x<<endl;
  }
};
class child:public parent{
    public:
   // using parent::function2;
    void function1(){
        cout<<"childs called"<<endl;
    };
    void function2(int a,int b){
        cout<<a+b<<endl;
    }
};
int main() {
	// your code goes here
	parent p1;
	child c1;
	parent *ptr1=&c1;
	ptr1->function1();// this is overriding becuase even if base class pointer as the fucntion is virtual it will override  if you remove virtual from definition of base function1 then it will print parents called;overriding only happens when base class is virtual function
	p1.function1();//overloading
	p1.function1(5);//this is overloading same name different arguments overloaded in the base class
	//function2 in the child class is not overloading the base class function2 overloading only happens in the same class or scope
	child c2;
	//METHOD HIDING
	c2.function2(5);//this will give error so if the derived class defined the fucntion all the function with same name getshidden if the base class so c2 can no longer access the fucntion2(int x) as it gets hidden this is method hiding EVEN IF SIGNATURE IS DIFFERENT AS WE CAN SEE IN THE EXAMPLE ALL BASE CLASS GETS HIDDEN 
	//this can be solved by using keyword will bring all fucntions to the child class scope and then we can use uncomment the using part in child and check it will work then
	

}
