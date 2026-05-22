#include <bits/stdc++.h>
using namespace std;
std::atomic<int> cnt{0};//now this variable is atomically increase no need for lock mutex 
void increase(){
     for (int i = 0; i < 1000000; i++) {
        cnt++;
    }
}
int main() {
	// your code goes here
	thread t1(increase);
	thread t2(increase);
	t1.join();
	t2.join();
	cout<<cnt<<endl;
	return 0;

}
