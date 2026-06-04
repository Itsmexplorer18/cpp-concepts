#include <bits/stdc++.h>
using namespace std;
class Movie{
    public:
    string name;
    string genre;
    float rating;
    int actorcount;
    string *actors;
    Movie(){
        actors=nullptr;
    };
    Movie(string name,string genre,float rating,int count,string *actors){
        this->name=name;
        this->genre=genre;
        this->rating=rating;
        this->actorcount=count;
        if(count!=0){
            this->actors=new string[count];
            for(int i=0;i<count;i++){
                this->actors[i]=actors[i];
            }
        }
        else actors=nullptr;
    }
    Movie(const Movie&original){
        cout<<"copy ctor called"<<endl;
        name=original.name;
        genre=original.genre;
        rating=original.rating;
        actorcount=original.actorcount;
        if(actorcount>0){
        actors=new string[actorcount];
        for(int i=0;i<actorcount;i++){
            actors[i]=original.actors[i];
        }
        }
        else actors=nullptr;
    }
     Movie &operator=(const Movie& original){
         if(this!=&original){
         cout<<"copy assignment called"<<endl;
        name=original.name;
        genre=original.genre;
        rating=original.rating;
        actorcount=original.actorcount;
        delete[] actors;
        actors=new string[actorcount];
        for(int i=0;i<actorcount;i++){
            actors[i]=original.actors[i];
        }
         }
         return *this;
    }
    ~Movie(){
        cout<<"calling destructor"<<endl;
        delete[] actors;
        actors=nullptr;
    }
    
};
int main() {
    string lionkingactors[]={"voice actor 1","voice actor 2"};
    string princessactors[]={"voice actor princess 1","voice actors princess2"};
   Movie one("lion king","comedy",8.9,2,lionkingactors);
	Movie two("princess and barbie","animated",9.9,2,princessactors);
	Movie three=two;
	Movie four;
	four=two;//calling assignment;
	four=one;//calling assignment
	Movie five(one);//copy constructor
	five=(one=two);

	
return 0;
}
