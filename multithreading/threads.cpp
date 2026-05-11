
#include <bits/stdc++.h>
using namespace std;

void work(long long start, long long end){
    double result = 0;
    for(long long i = start; i <= end; i++)
        result += sin((double)i);
    cout << result << "\n";
}

int main() {
    const long long N = 500000000LL;

    auto t1 = chrono::high_resolution_clock::now();
    work(1,N);
    work(N+1,2*N);
    // thread th1(work, 1, N);
    // thread th2(work, N+1, 2*N); work here is passed as a function pointer refer to function pointers in pointers
    // th1.join();
    // th2.join();
    //try running both to compare
    auto t2 = chrono::high_resolution_clock::now();

    cout << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms\n";
    return 0;
}
