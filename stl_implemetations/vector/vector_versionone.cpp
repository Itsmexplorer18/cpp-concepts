#include<string>
#include<iostream>
using namespace std;

template<typename T> 
class vector{
   private:
    T *arr; 
    size_t sz;
    size_t capacity;
    void reallocmemory(int newcapacity){
        T* newarr=new T[newcapacity];
        //why we cant use memcpy
        for(int i=0;i<sz;i++){
            newarr[i]=arr[i];
        }
        delete[] arr;
        arr=newarr;
        capacity=newcapacity;
    }
   public:
   vector():arr(nullptr),sz(0),capacity(0){};
   vector(int n):arr(new T[n]),sz(n),capacity(2*n){};
   //why const t &value SO THAT RVALUE CAN BIND TO IT U PASSED "C++" PRVLAUE
  void push_back(const T &value){
      if(sz==capacity){
          reallocmemory(capacity==0?1:capacity*2);
      }
      arr[sz++]=value;
      
  }
  size_t size() const{
      return sz;
  }
  //why both const and non const version? ONE FOR CONST ACCESS ONE V[5]="300"
  T& operator[](size_t index){
      return arr[index];
  }
  const T& operator[](size_t index) const{
      return arr[index];
  }
  ~vector(){
      delete[] arr;
  }
};
#include <iostream>
#include <utility>
using namespace std;

struct vector3 {
    float x = 0, y = 0, z = 0;

    vector3() { }
    explicit vector3(float s) : x(s), y(s), z(s) { }
    vector3(float x, float y, float z) : x(x), y(y), z(z) {  }

    // copy
    vector3(const vector3& o) : x(o.x), y(o.y), z(o.z) { cout << "copy ctor\n"; }
    vector3& operator=(const vector3& o) {
        cout << "copy assign\n";
        if (this != &o) {
            x = o.x;
            y = o.y;
            z = o.z;
        }
        return *this;
    }

    // move
    vector3(vector3&& o) noexcept : x(o.x), y(o.y), z(o.z) { cout << "move ctor\n"; }
    vector3& operator=(vector3&& o) noexcept {
        cout << "move assign\n";
        if (this != &o) {
            x = o.x;
            y = o.y;
            z = o.z;
        }
        return *this;
    }
friend ostream& operator<<(ostream& os, const vector3& v) {
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}
    ~vector3() { cout << "destroy\n"; }
};
template<typename T>
void printvector(const vector<T> &vector){
    for(size_t i=0;i<vector.size();i++){
        cout<<vector[i]<<endl;
    }
}
int main() {
	// your code goes here
	vector<vector3> vec;
	vec.push_back(vector3(1.0));
	vec.push_back(vector3(1.1,1.3,1.5));
	vec.push_back(vector3(1.0));
//	vec.push_back(vector3(1.0));

	printvector(vec);
// 	vector<string> another=vec;//copying all elements copy constructor
// 	vector<string> vec2(1);
// 	vec2.push_back("8");
// 	vec2=vec2;//copy assignment
// 	vec2.resize(100);
	//cout<<vec.size()<<endl;//capacity;

}
/*
copy assign
destroy becuase we are creating prvalue ctor and destroyed 
copy assign
destroy
copy assign
destroy
copy assign
copy assign
destroy
destroy
copy assign
destroy
(1, 1, 1)
(1.1, 1.3, 1.5)
(1, 1, 1)
destroy
destroy
destroy
destroy   4th destroy as capacity is four so now unused also destroyed
EXPLANATION OF 
copy assign        ← push 1: arr[0] = value
destroy            ← temporary vector3(1.0) dies
copy assign        ← push 2: realloc copies old element
destroy            ← old array deleted
copy assign        ← arr[1] = value
destroy            ← temporary dies
copy assign        ← push 3: realloc copies 2 old elements
copy assign
destroy            ← old array deleted (2 slots)
destroy
copy assign        ← arr[2] = value
destroy            ← temporary dies
(1, 1, 1) ...      ← printvector
destroy ×4         ← end of main: delete[] arr, all 4 slots including the unused one
*/
