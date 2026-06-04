#include <bits/stdc++.h>
using namespace std;
class Movie{
    public:
    string name;
    string genre;
    float rating;
    Movie(){};
    Movie(string name,string genre,float rating){
        this->name=name;
        this->genre=genre;
        this->rating=rating;
    }
    Movie(const Movie&original){
        cout<<"copy ctor called"<<endl;
        name=original.name;
        genre=original.genre;
        rating=original.rating;
    }
    //WHY NOT JUST VOID WHY MOVIE AND RETURN *THIS BECAUSE IF WE DO A=(B=C) THEN THIS WILL GIVE ERROR AS B=C IS GIVING A VOID RETURN AND THAT CANNOT BE ASSIGNED TO A SO WE NEED TO RETURN MOVIE SO IT CAN ASSIGN CHAINING
    // void operator=(const Movie& original){
    //      cout<<"copy assignment called"<<endl;
    //     name=original.name;
    //     genre=original.genre;
    //     rating=original.rating;
    //     //return *this;
    // }
    // NOW WHY IS & IMPORTANT BECAUSE WITHOUT THIS IT WILL RETURN A COPY AND THEN COPY
    // REASON 1:CONSTRCTOR IS CALLED WHICH IS UNECESSARY COPIES BEING CREATED UNCOMMENT THIS AND YOU WILL SEE CTOR BEING CALLED MULTIPLE TIMES FOR EACH ASSIGNMENT 
    // REASON 2: SEE THE SHREK EXAMPLE COMMENTED OUT (A=B)=C WHEN WE DO A=B WE GET A COPY RETURNED WHICH IS A TEMP COPY SO IT GETS DISCARDED AND WE DONT GET THE RESULTS
    // Movie operator=(const Movie& original){
    //      cout<<"copy assignment called"<<endl;
    //     name=original.name;
    //     genre=original.genre;
    //     rating=original.rating;
    //     return *this;
    // }
     Movie &operator=(const Movie& original){
         cout<<"copy assignment called"<<endl;
        name=original.name;
        genre=original.genre;
        rating=original.rating;
        return *this;
    }
    
};
int main() {
	Movie one("lion king","comedy",8.9);
	Movie two("princess and barbie","animated",9.9);
	Movie three=two;//constructor same as movie three(two)
    // this is copy ctor even tho = might be confusing cause an entrily new obj is being make so the copy ctor is caleed only when the object existis and then assigned will the assignment be called;
	Movie four;
	four=two;//calling assignment;
	four=one;//calling assignment
	Movie five(one);//copy constructor
	five=(one=two);
	
// 	  Movie one("lion king","comedy",8.9);
//     Movie two("princess and barbie","animated",9.9);
//     Movie three("shrek","action",7.5);

//     // we want: after (one=two)=three
//     // one should be shrek, two should stay princess and barbie
//     (one=two)=three;

//     cout<<"one: "<<one.name<<endl;  // prints princess and barbie (WRONG, wanted shrek)
//     cout<<"two: "<<two.name<<endl;  // prints princess and barbie
//     cout<<"three: "<<three.name<<endl; // prints shrek
}
