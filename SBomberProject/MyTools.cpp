
#include <conio.h>
#include <windows.h> 
#include <iostream>
#include <chrono>
#include "MyTools.h"
#include <time.h>

using namespace std;

namespace MyTools
{
    //============================================================================================
    void ScreenSingleton::ClrScr()
    {
        system("cls");
    }
        
    void __fastcall ScreenSingleton::GotoXY(double x, double y)
    {
        const COORD cc = { short(x), short(y) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cc);
    }
    uint16_t ScreenSingleton::GetMaxX()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Right;
                int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
            }
        }

        return 0;
    }
    uint16_t ScreenSingleton::GetMaxY()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Bottom;
            }
        }

        return 0;
    }
    void ScreenSingleton::SetColor(ConsoleColor color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color); // color =  (WORD)((BackgroundColor << 4) | TextColor))
    }
    //=============================================================================================


    void __fastcall LoggerSingleton::OpenLogFile(const std::string& FN)
    {
        this->logOut.open(FN, ios_base::out);
    }

    void LoggerSingleton::CloseLogFile()
    {
        if (this->logOut.is_open())
        {
            this->logOut.close();
        }
    }

    std::string LoggerSingleton::GetCurDateTime()
    {
        auto cur = std::chrono::system_clock::now();
        time_t time = std::chrono::system_clock::to_time_t(cur);
        char buf[64] = { 0 };
        ctime_s(buf, 64, &time);
        buf[strlen(buf) - 1] = '\0';
        return std::string(buf);
    }

    void __fastcall LoggerSingleton::WriteToLog(const std::string& str)
    {
        if (this->logOut.is_open())
        {
            this->logOut << GetCurDateTime() << " - " << str << endl;
        }
    }

    void __fastcall LoggerSingleton::WriteToLog(const std::string& str, int n)
    {
        if (this->logOut.is_open())
        {
            this->logOut << GetCurDateTime() << " - " << str << n << endl;
        }
    }

    void __fastcall LoggerSingleton::WriteToLog(const std::string& str, double d)
    {
        if (this->logOut.is_open())
        {
            this->logOut << GetCurDateTime() << " - " << str << d << endl;
        }
    }

    ProxyLogger::~ProxyLogger()
    {
        //delete _realLogger;
        std::cout << "Kolichestvo logov " << _counter;
    }

    void __fastcall ProxyLogger::WriteToLog(const std::string& str)
    {
        _realLogger.WriteToLog(str);
        _counter++;
    }
    void __fastcall ProxyLogger::WriteToLog(const std::string& str, int n)
    {
        _realLogger.WriteToLog(str, n);
        _counter++;
    }
    void __fastcall ProxyLogger::WriteToLog(const std::string& str, double d)
    {
        _realLogger.WriteToLog(str, d);
        _counter++;
    }

    void __fastcall ProxyLogger::OpenLogFile(const std::string& FN)
    {
        _realLogger.OpenLogFile(FN);
    }
    void ProxyLogger::CloseLogFile()
    {
        _realLogger.CloseLogFile();
    }
}


    //=============================================================================================
