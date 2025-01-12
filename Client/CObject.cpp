#include "pch.h"
#include "CObject.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
{
}

CObject::~CObject()
{
}

void CObject::update()
{
    if (CKeyMgr::GetInst()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
    {
        m_vPos.y -= 200.f * fDT;
    }

    if (CKeyMgr::GetInst()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
    {
        m_vPos.y += 200.f * fDT;
    }

    if (CKeyMgr::GetInst()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
    {
        m_vPos.x -= 200.f * fDT;
    }

    if (CKeyMgr::GetInst()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
    {
        m_vPos.x += 200.f * fDT;
    }
}

void CObject::render(HDC _dc)
{
    Rectangle(_dc, (int)(m_vPos.x - m_vScale.x / 2.f), (int)(m_vPos.y - m_vScale.y / 2.f)
        , (int)(m_vPos.x + m_vScale.x / 2.f), (int)(m_vPos.y + m_vScale.y / 2.f));
}
