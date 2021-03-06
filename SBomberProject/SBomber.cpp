
#include <conio.h>
#include <windows.h>
#include <utility>
#include <stdexcept>

#include "ProxyLogger.h"
#include "MyTools.h"
#include "SBomber.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"

using namespace std;

using namespace MyTools;

//ProxyLogger proxyLog(&(LoggerSingleton::getLoggerSingleton()));
   
   
DeleteDynamicObjCommand::DeleteDynamicObjCommand()
{
    this->pObj = nullptr;  
}
DeleteDynamicObjCommand::~DeleteDynamicObjCommand()
{
    //delete this->pObj;
    
}
void DeleteDynamicObjCommand::SetParams(DynamicObject* pObj, std::vector<DynamicObject*>& vecDynamicObj)
{
    this->pObj = pObj;
    this->vecDynamicObj = vecDynamicObj;
}
void DeleteDynamicObjCommand::Execute()
{
    auto it = vecDynamicObj.begin();
    for (; it != vecDynamicObj.end(); it++)
    {
        if (*it == pObj)
        {
            auto temp_ptr = *it;
            vecDynamicObj.erase(it);
            delete temp_ptr;
            break;
        }
    }
}


DeleteStaticObjCommand::DeleteStaticObjCommand()
{
    this->pObj = nullptr;
}
DeleteStaticObjCommand::~DeleteStaticObjCommand()
{
    //delete this->pObj;
    
}
void DeleteStaticObjCommand::SetParams(GameObject* pObj, std::vector<GameObject*>& vecStaticObj)
{
    this->pObj = pObj;
    this->vecStaticObj = vecStaticObj;
}
void DeleteStaticObjCommand::Execute()
{
    auto it = vecStaticObj.begin();
    for (; it != vecStaticObj.end(); it++)
    {
        if (*it == pObj)
        {
            auto temp_ptr = *it;
            vecStaticObj.erase(it);
            delete temp_ptr;
            break;
        }
    }
}
 DropBombCommand::DropBombCommand() 
 {
     BombCounter_ = 0;
     currPlane_ = nullptr;
 }

 DropBombCommand::~DropBombCommand()
 {
    
 }
 void DropBombCommand::Execute()
 {
     if (BombCounter_ > 0)
     {
         //LoggerSingleton::getLoggerSingleton().WriteToLog(std::string(__FUNCTION__) + " was invoked");
         
         //logger_->WriteToLog(std::string(__FUNCTION__) + " was invoked");

         //Plane* pPlane = FindPlane();
         double x = currPlane_->GetX() + 4;
         double y = currPlane_->GetY() + 2;

         Bomb* pBomb = new Bomb;
         pBomb->SetDirection(0.3, 1);
         pBomb->SetSpeed(2);
         pBomb->SetPos(x, y);
         pBomb->SetWidth(SMALL_CRATER_SIZE);

         vecDynamicObj_.push_back(pBomb);
         BombCounter_--;
         //score -= Bomb::BombCost;
     }
    
 }
 void DropBombCommand::SetParams(const Plane* currPlane, std::vector<DynamicObject*>  &vecDynamicObj, const uint16_t& BombCounter)
 {
     currPlane_ = currPlane;
     vecDynamicObj_ = vecDynamicObj;
     BombCounter_ = BombCounter;

         
 }

SBomber::SBomber(std::shared_ptr<MyTools::LoggerInterface> logger)
    : exitFlag(false),
    startTime(0),
    finishTime(0),
    deltaTime(0), 
    passedTime(0),
    fps(0),
    bombsNumber(10),
    score(0),
    logger_{std::move(logger)}
{
    //ProxyLogger proxyLog(&(LoggerSingleton::getLoggerSingleton()));

    //LoggerSingleton::getLoggerSingleton().WriteToLog(std::string(__FUNCTION__) + " was invoked");
    if (!logger_)
    {
        throw std::runtime_error{ "logger is nullptr" };
    }
    logger_->WriteToLog(std::string(__FUNCTION__) + " was invoked");

    Plane* p = new Plane;
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
    vecDynamicObj.push_back(p);

    LevelGUI* pGUI = new LevelGUI;
    pGUI->SetParam(passedTime, fps, bombsNumber, score);
    const uint16_t maxX = ScreenSingleton::getInstance().GetMaxX();
    const uint16_t maxY = ScreenSingleton::getInstance().GetMaxY();
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    vecStaticObj.push_back(pGUI);

    Ground* pGr = new Ground;
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    vecStaticObj.push_back(pGr);

    Tank* pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(30, groundY - 1);
    vecStaticObj.push_back(pTank);

    pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(50, groundY - 1);
    vecStaticObj.push_back(pTank);

    House * pHouse = new House;
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    vecStaticObj.push_back(pHouse);

    /*
    Bomb* pBomb = new Bomb;
    pBomb->SetDirection(0.3, 1);
    pBomb->SetSpeed(2);
    pBomb->SetPos(51, 5);
    pBomb->SetSize(SMALL_CRATER_SIZE);
    vecDynamicObj.push_back(pBomb);
    */
}

SBomber::~SBomber()
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            delete vecDynamicObj[i];
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        if (vecStaticObj[i] != nullptr)
        {
            delete vecStaticObj[i];
        }
    }
}

void SBomber::MoveObjects()
{
    //LoggerSingleton::getLoggerSingleton().WriteToLog(std::string(__FUNCTION__) + " was invoked");
    logger_->WriteToLog(std::string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            vecDynamicObj[i]->Move(deltaTime);
        }
    }
};

void SBomber::CheckObjects()
{
    //LoggerSingleton::getLoggerSingleton().WriteToLog(std::string(__FUNCTION__) + " was invoked");
    logger_->WriteToLog(std::string(__FUNCTION__) + " was invoked");

    CheckPlaneAndLevelGUI();
    CheckBombsAndGround();
};

void SBomber::CheckPlaneAndLevelGUI()
{
    if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX())
    {
        exitFlag = true;
    }
}

void SBomber::CheckBombsAndGround() 
{
    vector<Bomb*> vecBombs = FindAllBombs();
    Ground* pGround = FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++)
    {
        
        if (vecBombs[i]->GetY() >= y) // ??????????? ????? ? ??????
        {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecBombs[i]);

            DeleteDynamicObjCommand* delDObl = new(DeleteDynamicObjCommand);
            delDObl->SetParams(vecBombs[i], vecDynamicObj);
            CommandExecuter(reinterpret_cast<AbstractCommand*>(delDObl));
            //DeleteDynamicObj(vecBombs[i]);
        }
    }

}

void SBomber::CheckDestoyableObjects(Bomb * pBomb)
{
    vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
    {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2))
        {
            score += vecDestoyableObjects[i]->GetScore();
            DeleteStaticObjCommand* delStObj = new DeleteStaticObjCommand;
            delStObj->SetParams(vecDestoyableObjects[i], vecStaticObj);
            CommandExecuter(delStObj);
            //DeleteStaticObj(vecDestoyableObjects[i]);
        }
    }
}

/*void SBomber::DeleteDynamicObj(DynamicObject* pObj)
{
    auto it = vecDynamicObj.begin();
    for (; it != vecDynamicObj.end(); it++)
    {
        if (*it == pObj)
        {
            auto temp_ptr = *it;
            vecDynamicObj.erase(it);
            delete temp_ptr;
            break;
        }
    }
}*/
void SBomber::CommandExecuter(AbstractCommand* pCommand)
{
    pCommand->Execute();
    delete pCommand;
}

/*void SBomber::DeleteStaticObj(GameObject* pObj)
{
    auto it = vecStaticObj.begin();
    for (; it != vecStaticObj.end(); it++)
    {
        if (*it == pObj)
        {
            vecStaticObj.erase(it);
            break;
        }
    }
}*/

vector<DestroyableGroundObject*> SBomber::FindDestoyableGroundObjects() const
{
    vector<DestroyableGroundObject*> vec;
    Tank* pTank;
    House* pHouse;
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
        if (pTank != nullptr)
        {
            vec.push_back(pTank);
            continue;
        }

        pHouse = dynamic_cast<House*>(vecStaticObj[i]);
        if (pHouse != nullptr)
        {
            vec.push_back(pHouse);
            continue;
        }
    }

    return vec;
}

Ground* SBomber::FindGround() const
{
    Ground* pGround;

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pGround = dynamic_cast<Ground *>(vecStaticObj[i]);
        if (pGround != nullptr)
        {
            return pGround;
        }
    }

    return nullptr;
}

vector<Bomb*> SBomber::FindAllBombs() const
{
    vector<Bomb*> vecBombs;

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Bomb* pBomb = dynamic_cast<Bomb*>(vecDynamicObj[i]);
        if (pBomb != nullptr)
        {
            vecBombs.push_back(pBomb);
        }
    }

    return vecBombs;
}

Plane* SBomber::FindPlane() const
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

LevelGUI* SBomber::FindLevelGUI() const
{
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

void SBomber::ProcessKBHit()
{
    int c = _getch();

    if (c == 224)
    {
        c = _getch();
    }

    //LoggerSingleton::getLoggerSingleton().WriteToLog(std::string(__FUNCTION__) + " was invoked. key = ", c);

    logger_->WriteToLog(std::string(__FUNCTION__) + " was invoked. key = ", c);

    switch (c) {

    case 27: // esc
        exitFlag = true;
        break;

    case 72: // up
        FindPlane()->ChangePlaneY(-0.25);
        break;

    case 80: // down
        FindPlane()->ChangePlaneY(0.25);
        break;

    case 'b':
    {
        DropBomb();
        break;
    }
    case 'B':
    {
         DropBomb();
         break;

    }
    default:
        break;
    }
}

void SBomber::DrawFrame()
{
    //LoggerSingleton::getLoggerSingleton().WriteToLog(std::string(__FUNCTION__) + " was invoked");
    logger_->WriteToLog(std::string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            /*if (typeid(vecDynamicObj[i]) == typeid(Bomb))
            {
                auto image = std::make_shared<Bomb>(vecDynamicObj[i]);
                BombDecorator decorator{ std::static_pointer_cast<DynamicObject>(image) };
                decorator.Draw();
            }
            else
            {*/
                vecDynamicObj[i]->Draw();
            /*}   */      
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        if (vecStaticObj[i] != nullptr)
        {
            vecStaticObj[i]->Draw();
        }
    }

    ScreenSingleton::getInstance().GotoXY(0, 0);
    fps++;

    FindLevelGUI()->SetParam(passedTime, fps, bombsNumber, score);
}

void SBomber::TimeStart()
{
    LoggerSingleton::getLoggerSingleton().WriteToLog(std::string(__FUNCTION__) + " was invoked");
    startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
    finishTime = GetTickCount64();
    deltaTime = uint16_t(finishTime - startTime);
    passedTime += deltaTime;

    //LoggerSingleton::getLoggerSingleton().WriteToLog(std::string(__FUNCTION__) + " deltaTime = ", (int)deltaTime);
    logger_->WriteToLog(std::string(__FUNCTION__) + " deltaTime = ", (int)deltaTime);
}

void SBomber::DropBomb()
{
    if (bombsNumber > 0)
    {
        //LoggerSingleton::getLoggerSingleton().WriteToLog(std::string(__FUNCTION__) + " was invoked");
        logger_->WriteToLog(std::string(__FUNCTION__) + " was invoked");

        const Plane* pPlane = FindPlane();
        //Plane* pPlane = FindPlane();
        DropBombCommand* dbCom = new DropBombCommand;
        dbCom->SetParams(pPlane, vecDynamicObj, bombsNumber);
        CommandExecuter(dynamic_cast <AbstractCommand*>(dbCom));

        //double x = pPlane->GetX() + 4;
        //double y = pPlane->GetY() + 2;

        /*Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(2);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(SMALL_CRATER_SIZE);

        vecDynamicObj.push_back(pBomb);
        bombsNumber--;*/
        score -= Bomb::BombCost;
    }
}
