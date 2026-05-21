#include <bits/stdc++.h>
using namespace std;
int cnt=0;
std::mutex m; //protect the critical section only one of them can enter mutual exclusion as the name suggests
void increase(){
    m.lock();
     for (int i = 0; i < 1000000; i++) {
        cnt++;
    }
    m.unlock();
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
