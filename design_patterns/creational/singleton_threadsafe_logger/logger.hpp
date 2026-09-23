#ifndef logger_h
#define lohher_h
#include <mutex>

#include <string>
using namespace std;

class Logger{
    static mutex mtx;
    static int counter;
    static Logger* loggerinstance;
    Logger();
  public:
  static Logger* getLogger();
  void log(string msg);
};

#endif