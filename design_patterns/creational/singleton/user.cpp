#include <iostream> 
#include "logger.hpp"
using namespace std;

int main(){
  Logger* logger1=new Logger();
  logger1->log("user one");
  
  Logger* logger2=new Logger();
  logger2->log("user two");

};