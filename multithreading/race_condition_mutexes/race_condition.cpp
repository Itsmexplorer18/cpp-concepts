#include <bits/stdc++.h>
using namespace std;
int cnt=0;
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
//classic exmaple of race condition expected output=2000000 not matching with the output(it might match its not necessary it will give wrong answer making race condition even 
//more dangerous as they are difficult to find and debug
