#pragma once
#include "CScene.h"

class CScene_Tool : public CScene
{
private:

public:
    virtual void Enter();
    virtual void Exit();
    virtual void update();

public:
    CScene_Tool();
    ~CScene_Tool();
};

