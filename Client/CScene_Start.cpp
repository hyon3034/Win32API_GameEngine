#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
    CScene::update(); // 부모의 기능 호출

    if (KEY_TAP(KEY::ENTER)) // tool scene 전환
    {
        ChangeScene(SCENE_TYPE::TOOL); // 이벤트 등록
    }

}

void CScene_Start::Enter()
{

    // Player 추가
    CObject* pObj = new CPlayer;
    
    pObj->SetPos(Vec2(640.f, 384.f));
    pObj->SetScale(Vec2(100.f, 100.f));                                                     

    AddObject(pObj, GROUP_TYPE::PLAYER);

    CObject* pOtherPlayer = pObj->Clone();
    pOtherPlayer->SetPos(Vec2(740.f, 384.f));
    AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

    // Monster 추가
    int iMonCount = 2;
    float fMoveDist = 25.f;
    float fObjScale = 50.f;

    Vec2 vResolution = CCore::GetInst()->GetResolution();
    CMonster* pMonsterObj = nullptr;

    float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 1);

    for (int i = 0; i < iMonCount; ++i)
    {
        pMonsterObj = new CMonster;
        pMonsterObj->SetName(L"Monster");
        pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTerm, 50.f));
        pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
        pMonsterObj->SetMoveDistance(fMoveDist);
        pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
        AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
    }

    // 충돌 지정
    // Player 그룹과 Monster 그룹 간의 충돌 체크
    CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

}

void CScene_Start::Exit()
{
    DeleteAll();

    // 충돌 그룹을 해제
    CCollisionMgr::GetInst()->Reset();
}
