#ifndef logger_h
#define lohher_h

#include <string>
using namespace std;

class Logger{
    static int counter;
  public:
  Logger();
  void log(string msg);
};

#endif