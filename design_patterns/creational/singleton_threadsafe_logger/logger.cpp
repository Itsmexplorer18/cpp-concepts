#include <iostream>
#include "logger.hpp"
using namespace std;

int Logger::counter=0;
Logger* Logger::loggerinstance=nullptr;
mutex Logger::mtx;

Logger::Logger(){
    counter++;
    cout<<"new instance of logger created"<<" "<<counter<<endl;
}

void Logger::log(string msg){
    cout<<msg<<endl;
}
Logger* Logger::getLogger(){
    if(loggerinstance==nullptr){
    mtx.lock();
   if(loggerinstance==nullptr){
    loggerinstance=new Logger();
   }
   mtx.unlock();
}
   return loggerinstance;
}