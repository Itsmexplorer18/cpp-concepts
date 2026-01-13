
#include <bits/stdc++.h>
using namespace std;
//can be any data type in pur implementation even a user defined data type as we have used tempelates
template <typename t>
class uniqueptr{
    private:
     t* res;
    public:
    uniqueptr(t* a=nullptr):res(a){
        cout<<"constructor";
    }
    uniqueptr(const uniqueptr<t> &ptr)=delete;//as we dont want this to happen
    uniqueptr& operator=(const uniqueptr<t> &ptr)=delete;
    //move copy
    uniqueptr(uniqueptr<t> &&ptr){
        
        res=ptr.res;
        ptr.res=nullptr;
    }
    uniqueptr& operator=(uniqueptr<t> &&ptr){
        if(this!=&ptr){
            if(res) delete res;
             res=ptr.res;
        ptr.res=nullptr;
        }
        return *this;
    }
    t* operator->(){
        return res;
    }
    t& operator*(){
        return *res;
    }
    t* get(){
        return res;
    }
    void reset(t* newres=nullptr){
        if(res){
            delete res;
        }
        res=newres;
        
    }
    ~uniqueptr(){
        if(res){
            delete res;
            res=nullptr;
        }
    }
    
};

int main() {
  uniqueptr<int> ptr1(new int(10));
  uniqueptr<int> ptr2(ptr1);//compilation error becuase this is unique ptr cant be shared
  uniqueptr<int> ptr3=ptr1;//also compilation error
  uniqueptr<int> ptr4(new int(40));
  ptr4=ptr3;//compilation error assigment not allowed
  ptr4=std::move(ptr3);
  ptr1->func();//implement the arrow overload it basically
  cout<<*ptr1;//implement the * deallocator again by overloading 
  ptr1.get();//will give the resource
  ptr1.reset()
  

}
