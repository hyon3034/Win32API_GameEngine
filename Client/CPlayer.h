#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
    public CObject
{
private:
    CTexture* m_pTex; // 캐릭터의 texture

public :
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();

public:
    CPlayer();
    ~CPlayer();
};

