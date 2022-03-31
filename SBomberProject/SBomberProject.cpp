
#include <conio.h>
#include<memory>
#include <stdlib.h>

#include "SBomber.h"
#include "MyTools.h"

using namespace std;

//========================================================================================================================

int main(void)
{
    //MyTools::LoggerSingleton::getLoggerSingleton().OpenLogFile("log.txt");
    //  MyTools::ProxyLogger logger(&(MyTools::LoggerSingleton::getLoggerSingleton()));
    auto logger = std::make_shared<MyTools::ProxyLogger>(MyTools::LoggerSingleton::getLoggerSingleton());

    logger->OpenLogFile("log.txt");


    SBomber game(logger);

    do {
        game.TimeStart();

        if (_kbhit())
        {
            game.ProcessKBHit();
        }

        MyTools::ScreenSingleton::getInstance().ClrScr();

        game.DrawFrame();
        game.MoveObjects();
        game.CheckObjects();

        game.TimeFinish();

    } while (!game.GetExitFlag());

    //MyTools::LoggerSingleton::getLoggerSingleton().CloseLogFile();
    logger->CloseLogFile();

    return 0;
}
