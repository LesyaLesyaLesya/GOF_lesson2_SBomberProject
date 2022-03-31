#pragma once

#include <stdint.h>
#include <string>
#include <fstream>


namespace MyTools 
{
   
    enum ConsoleColor
    {
        CC_Black = 0,
        CC_Blue,
        CC_Green,
        CC_Cyan,
        CC_Red,
        CC_Magenta,
        CC_Brown,
        CC_LightGray,
        CC_DarkGray,
        CC_LightBlue,
        CC_LightGreen,
        CC_LightCyan,
        CC_LightRed,
        CC_LightMagenta,
        CC_Yellow,
        CC_White
    };
	//=============================================================================================
    class ScreenSingleton
    {
    public:
        static ScreenSingleton& getInstance()
        { 
            static ScreenSingleton theInstance;
            return theInstance;
        }
        void ClrScr();
        void __fastcall GotoXY(double x, double y);
        uint16_t GetMaxX();
        uint16_t GetMaxY();
        void SetColor(ConsoleColor color);

    private:
       
        ScreenSingleton(){};
        ScreenSingleton(const ScreenSingleton&) = delete;
        ScreenSingleton& operator=(const ScreenSingleton&) = delete;
        ScreenSingleton(ScreenSingleton&&) = delete;
        ScreenSingleton& operator=(const ScreenSingleton&&) = delete;

    };

	
	//=============================================================================================
    class LoggerInterface
    {
    public:
        virtual ~LoggerInterface() = default;
        virtual void __fastcall OpenLogFile(const std::string& FN) = 0;
        virtual void CloseLogFile() = 0;
        virtual void __fastcall WriteToLog(const std::string& str) = 0;
        virtual void __fastcall WriteToLog(const std::string& str, int n) = 0;
        virtual void __fastcall WriteToLog(const std::string& str, double d) = 0;
    private:
       
    };

    class LoggerSingleton : public LoggerInterface
    {
    public:
        static LoggerSingleton& getLoggerSingleton()
        {
            static LoggerSingleton myLoggerSingleton;
            return myLoggerSingleton;
        }

        void __fastcall OpenLogFile(const std::string& FN) override;
        void CloseLogFile() override;
        void __fastcall WriteToLog(const std::string& str) override;
        void __fastcall WriteToLog(const std::string& str, int n) override;
        void __fastcall WriteToLog(const std::string& str, double d) override;

    private:
        LoggerSingleton() {};
        LoggerSingleton(const LoggerSingleton&) = delete;
        LoggerSingleton& operator=(LoggerSingleton&) = delete;
        LoggerSingleton(LoggerSingleton&&) = delete;
        LoggerSingleton& operator=(LoggerSingleton&&) = delete;

        static std::string GetCurDateTime();

        std::ofstream logOut;
    };

    class ProxyLogger : public LoggerInterface
    {
    public:
        ProxyLogger(LoggerInterface& realLogger) :_realLogger(realLogger) {};
        ~ProxyLogger() override;

        void __fastcall OpenLogFile(const std::string& FN) override;
        void CloseLogFile() override;
        void __fastcall WriteToLog(const std::string& str) override;
        void __fastcall WriteToLog(const std::string& str, int n) override;
        void __fastcall WriteToLog(const std::string& str, double d) override;

    private:
  
        //std::unique_ptr<LoggerInterface> _realLogger;
        LoggerInterface& _realLogger;
        int _counter{0};
    };
    
   
	//=============================================================================================

};