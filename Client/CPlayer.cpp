#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"

#include "CResMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
    //// Texture 로딩하기
    //m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

    CreateCollider();
    GetCollider()->SetOffsetPos(Vec2(0.f, 12.f));
    GetCollider()->SetScale(Vec2(20.f, 40.f));

    // Texture 로딩하기
    CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link_0.bmp");

    CreateAnimator();
    GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);
    GetAnimator()->Play(L"WALK_DOWN", true);
    
    CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");

    for(UINT i = 0; i < pAnim->GetMaxFrame(); ++i)
        pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
}

CPlayer::~CPlayer()
{
}


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

    GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{

    // 컴포넌트 (충돌체, etc...) 가 있는 경우 렌더
    component_render(_dc);
}

void CPlayer::CreateMissile()
{
    Vec2 vMissilePos = GetPos();
    vMissilePos.y -= GetScale().y / 2.f;

    // Missile Object
    CMissile* pMissile = new CMissile;
    pMissile->SetName(L"Missile_Player");
    pMissile->SetPos(vMissilePos);
    pMissile->SetScale(Vec2(25.f, 25.f));
    pMissile->SetDir(Vec2(0.f, -1.f));

    // CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
    // pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);

    // 이벤트 정보 등록
    CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
 }
