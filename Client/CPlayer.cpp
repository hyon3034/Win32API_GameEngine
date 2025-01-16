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


CPlayer::CPlayer()
    :m_pTex(nullptr)
{
    // Texture 로딩하기
    m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

    CreateCollider();
    GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
    GetCollider()->SetScale(Vec2(30.f, 25.f));
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
}

void CPlayer::render(HDC _dc)
{
    int iWidth = (int)m_pTex->Width();
    int iHeight = (int)m_pTex->Height();

    Vec2 vPos = GetPos();

    //BitBlt(_dc
    //    , int(vPos.x - (float)(iWidth / 2))
    //    , int(vPos.y - (float)(iHeight / 2))
    //    , iWidth, iHeight
    //    , m_pTex->GetDC()
    //    , 0, 0, SRCCOPY);

    TransparentBlt(_dc
        , int(vPos.x - (float)(iWidth / 2))
        , int(vPos.y - (float)(iHeight / 2))
        , iWidth, iHeight
        , m_pTex->GetDC()
        , 0, 0, iWidth, iHeight
        , RGB(255,0,255));

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
