#include "ProxyLogger.h"
#include <iostream>
#include "MyTools.h"
namespace ProxyLoggerNSP
{
   /* MyTools::LoggerSingleton* _realLogger = &(MyTools::LoggerSingleton::getLoggerSingleton());
    int ProxyLogger::counter = 0;

    ProxyLogger::ProxyLogger()
    {
        _realLogger = &(MyTools::LoggerSingleton::getLoggerSingleton());
    }
    ProxyLogger::~ProxyLogger()
    {
        std::cout << "Kolichestvo logov " << counter;
        delete _realLogger;
    }*/
    
    /*void __fastcall ProxyLogger::WriteToLog(const std::string& str)
    {
        _realLogger->WriteToLog(str);
        counter++;
    }
    void __fastcall ProxyLogger::WriteToLog(const std::string& str, int n)
    {
        _realLogger->WriteToLog(str, n);
        counter++;
    }
    void __fastcall ProxyLogger::WriteToLog(const std::string& str, double d)
    {
        _realLogger->WriteToLog(str, d);
        counter++;
    }*/
}