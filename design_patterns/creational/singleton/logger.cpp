#include <iostream>
#include "logger.hpp"
using namespace std;

int Logger::counter=0;
Logger::Logger(){
    counter++;
    cout<<"new instance of logger created"<<" "<<counter<<endl;
}

void Logger::log(string msg){
    cout<<msg<<endl;
}