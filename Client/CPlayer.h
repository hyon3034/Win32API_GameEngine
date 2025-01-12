#pragma once
#include "CObject.h"

class CPlayer :
    public CObject
{
public :
    virtual void update();

private:
    void CreateMissile();
};

