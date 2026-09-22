#ifndef logger_h
#define logger_h

#include <string>
using namespace std;

class Logger{
    static int counter;
  public:
  Logger();
  void log(string msg);
};

#endif
