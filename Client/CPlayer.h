#pragma once
#include "CObject.h"

enum class PLAYER_STATE
{
    IDLE,
    WALK,
    ATTACK,
    JUMP,
    DEAD,
};

enum class PLAYER_ATTACK_STATE
{
    NORMAL_ATT_1,
    NORMAL_ATT_2,
    NORMAL_ATT_3,

    SKILL_ATT_1,
    // ....
};


class CTexture;

class CPlayer :
    public CObject
{
private:
    vector<CObject*> m_vecColObj;

    PLAYER_STATE m_eCurState;
    PLAYER_STATE m_ePrevState;
    int m_iDir;
    int m_iPrevDir;

public :
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();
    void update_state();
    void update_move();
    void update_animation();
    void update_gravity();

    virtual void OnCollisionEnter(CCollider* _pOther);

    CLONE(CPlayer);

public:
    CPlayer();
    ~CPlayer();
};

