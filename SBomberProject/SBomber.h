#pragma once

#include <vector>
#include <memory>
#include "MyTools.h"
#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"

class AbstractCommand
{
public:
    virtual ~AbstractCommand() = default;
    virtual void __fastcall Execute()=0;
    
};

class DeleteDynamicObjCommand : public AbstractCommand
{
private:
    DynamicObject* pObj;
    std::vector<DynamicObject*> vecDynamicObj;
public:
    DeleteDynamicObjCommand();
    //DeleteDynamicObjCommand(DynamicObject* pObj, std::vector<DynamicObject*>& vecDynamicObj) = delete;
    
    ~DeleteDynamicObjCommand() override;

    void Execute() override;
    void SetParams(DynamicObject* pObj, std::vector<DynamicObject*>& vecDynamicObj);
};

class DeleteStaticObjCommand : public AbstractCommand
{
private:
    GameObject* pObj;
    std::vector<GameObject*> vecStaticObj;
public:
    DeleteStaticObjCommand();

    ~DeleteStaticObjCommand() override;

    void Execute() override;
    void SetParams(GameObject* pObj, std::vector<GameObject*>& vecDynamicObj);

};

class DropBombCommand:public AbstractCommand
{
private:
    uint16_t& BombCounter_;
    const Plane* currPlane_;
    std::vector<DynamicObject*>& vecDynamicObj_;

public:
    DropBombCommand(const Plane* currPlane, std::vector<DynamicObject*>& vecDynamicObj, uint16_t& BombCounter) :
        BombCounter_(BombCounter), currPlane_(currPlane), vecDynamicObj_(vecDynamicObj) {};
    ~DropBombCommand() override;

    void Execute() override;
    void SetParams(const Plane* currPlane, std::vector<DynamicObject*>& vecDynamicObj, const uint16_t& BombCounter_);
};

class SBomber
{
public:

    SBomber(std::shared_ptr<MyTools::LoggerInterface> logger);
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();
    void CommandExecuter(AbstractCommand* pCommand);
private:

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void __fastcall CheckDestoyableObjects(Bomb* pBomb);

    //void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
    //void __fastcall DeleteStaticObj(GameObject* pObj);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;

    void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
    std::shared_ptr<MyTools::LoggerInterface> logger_;
};