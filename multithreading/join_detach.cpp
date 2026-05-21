#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void run(int count)
{
    while (count-- > 0)
    {
        cout << "print somethin" << endl;
        this_thread::sleep_for(chrono::seconds(5));
    }

    cout << "thread finished" << endl;
}

int main()
{
    thread t1(run, 5);

    cout << "main" << endl;


    // JOIN example:
    if (t1.joinable()) //to make sure we dont double join or detach it will lead to crash so we can check in a more complex code by using joinable
    {
        t1.join();
    }

    // DETACH example:
    // if (t1.joinable()) //detach makes this a independant thread and the main no longer waits for this and if main threads end this one gets terminated by itself 
    // {
    //     t1.detach();
    // }

    cout << "main after" << endl;

    return 0;
}
