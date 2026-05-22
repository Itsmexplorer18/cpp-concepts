#include <bits/stdc++.h>
using namespace std;
class printer{
    string _name;
    int _paper_available;
    public:
    printer(string name,int paper){
        this->_name=name;
        this->_paper_available=paper;
    }
    void print(string text){
        int req=text.size()/10;
        // if(_paper_available<req){
        //     throw "not enough paper";
        //     //no need to return throw will do that
        // }
        if(_paper_available<req){
            throw 101;
            //no need to return throw will do that
        }
        cout<<"printing"<<" "<<text<<endl;
        _paper_available-=req;
    }
};
int main() {
	// your code goes here
	printer p1("hp43",2);
	try{
	p1.print("my name is harshita");
	p1.print("my name is harshita");
	p1.print("my name is harshita");
	p1.print("my name is harshita");
	}
// 	catch(const char * text){
// 	    cout<<"exception"<<" "<<text<<endl;
// 	}
// 	catch(int exeptioncode){
// 	    cout<<"exception"<<" "<<exeptioncode<<endl;
// 	}
	catch(...){
	    cout<<"exception happened"<<endl;
	}

}
