#include "pch.h"
#include "CObject.h"

#include "CCollider.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
    , m_pCollider(nullptr)
    , m_bAlive(true)
{
}

CObject::~CObject()
{
    if (nullptr != m_pCollider)
    {
        delete m_pCollider;
    }
}

void CObject::finalupdate()
{
    if (m_pCollider)
        m_pCollider->finalupdate();
}

void CObject::render(HDC _dc)
{
    Rectangle(_dc, (int)(m_vPos.x - m_vScale.x / 2.f), (int)(m_vPos.y - m_vScale.y / 2.f)
        , (int)(m_vPos.x + m_vScale.x / 2.f), (int)(m_vPos.y + m_vScale.y / 2.f));

    component_render(_dc);
}

void CObject::component_render(HDC _dc)
{
    if (nullptr != m_pCollider) // 콜라이더 렌더링
    {
        m_pCollider->render(_dc);
    }
}

void CObject::CreateCollider()
{
    m_pCollider = new CCollider;
    m_pCollider->m_pOwner = this;
}