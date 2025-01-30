#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CCollider.h"

#include "AI.h"

CMonster::CMonster()
    : m_tInfo{}

{
    CreateCollider(); // 부모 렌더러에서 Render 해줌
    GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
    if (nullptr != m_pAI)
        delete m_pAI;
}


void CMonster::SetAI(AI* _AI)
{
    m_pAI = _AI; 
    m_pAI->m_pOwner = this;
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
    CObject* pOtherObj = _pOther->GetObj();

    if (pOtherObj->GetName() == L"Missile_Player")
    {
    }
}

void CMonster::update()
{
    if(nullptr != m_pAI)
        m_pAI->update();
}

