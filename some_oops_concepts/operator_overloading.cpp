//code inspired for practice from codebeauty youtube
#include <bits/stdc++.h>
using namespace std;
//creater youtube channel with name and subs count
//cout youtube channel overload the << operator
//make mycollections class collections of youtube channel
//overload the << of that too and the += will add more channel to the list inside mychannel
class Youtubechannel{
    public:
    string name;
    int subscribers_count;
    Youtubechannel(){};
    Youtubechannel(string name,int count){
        this->name=name;
        this->subscribers_count=count;
    }
};
//void operator<< no chaining 
ostream& operator<<(ostream &cout,Youtubechannel &ytchannel){
    cout<<"name "<<ytchannel.name<<endl;
    cout<<"subscribers "<<ytchannel.subscribers_count<<endl;
    return cout;
}
class mycollection{
  public:
  vector<Youtubechannel> mylist;
  void operator+=(const Youtubechannel& ytchannel){
      mylist.push_back(ytchannel);
  }
};
ostream& operator<<(ostream &cout,mycollection &collection){
    for(auto channel:collection.mylist){
        cout<<channel;
    }
    return cout;
}
int main() {
	Youtubechannel y1=Youtubechannel("harshita",5);
	Youtubechannel y2=Youtubechannel("second",4);
	cout<<y1<<y2;
	mycollection newcollection;
	newcollection+=y1;
	newcollection+=y2;
	cout<<newcollection;

}
