#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"

void CPlayer::update()
{
    Vec2 vPos = GetPos();

    if(KEY_HOLD(KEY::W))
    {
        vPos.y -= 200.f * fDT;
    }

    if(KEY_HOLD(KEY::S))
    {
        vPos.y += 200.f * fDT;
    }

    if(KEY_HOLD(KEY::A))
    {
        vPos.x -= 200.f * fDT;
    }

    if(KEY_HOLD(KEY::D))
    {
        vPos.x += 200.f * fDT;
    }

    if(KEY_TAP(KEY::SPACE))
    {
        CreateMissile();
    }

    SetPos(vPos);
}

void CPlayer::CreateMissile()
{
    Vec2 vMissilePos = GetPos();
    vMissilePos.y -= GetScale().y / 2.f;

    // Missile Object
    CMissile* pMissile = new CMissile;
    pMissile->SetPos(vMissilePos);
    pMissile->SetScale(Vec2(25.f, 25.f));
    pMissile->SetDir(true);

    CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
    pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}
