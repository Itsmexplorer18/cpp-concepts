#include <iostream> 
#include "logger.hpp"
using namespace std;
#include <thread>
void getuser1(){
    Logger* logger1=Logger::getLogger();
  logger1->log("user one");
}
void getuser2(){
    Logger* logger2=Logger::getLogger();
  logger2->log("user two");
}
int main(){
  thread t1(getuser1);
  thread t2(getuser2);
  t1.join();
  t2.join();
};