#include "pch.h"
#include "CObject.h"

#include "CCollider.h"
#include "CAnimator.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
    , m_pCollider(nullptr)
    , m_pAnimator(nullptr)
    , m_bAlive(true)
{
}

CObject::CObject(const CObject& _origin)
    : m_strName(_origin.m_strName)
    , m_vPos(_origin.m_vPos)
    , m_vScale(_origin.m_vScale)
    , m_pAnimator(_origin.m_pAnimator)
    , m_pCollider(nullptr)
    , m_bAlive(true)
{
    if(_origin.m_pCollider)
    {
        m_pCollider = new CCollider(*_origin.m_pCollider);
        m_pCollider->m_pOwner = this;
    }

    if (_origin.m_pAnimator)
    {
        m_pAnimator = new CAnimator(*_origin.m_pAnimator);
        m_pAnimator->m_pOwner = this;
    }
    
}

CObject::~CObject()
{
    if (nullptr != m_pCollider)
    {
        delete m_pCollider;
    }

    if (nullptr != m_pAnimator)
    {
        delete m_pAnimator;
    }
}

void CObject::finalupdate()
{
    if (m_pCollider)
        m_pCollider->finalupdate();

    if (m_pAnimator)
        m_pAnimator->finalupdate();
}

void CObject::render(HDC _dc)
{
    Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

    Rectangle(_dc, (int)(vRenderPos.x - m_vScale.x / 2.f), (int)(vRenderPos.y - m_vScale.y / 2.f)
        , (int)(vRenderPos.x + m_vScale.x / 2.f), (int)(vRenderPos.y + m_vScale.y / 2.f));

    component_render(_dc);
}

void CObject::component_render(HDC _dc)
{
    if (nullptr != m_pCollider) // 콜라이더 렌더링
    {
        m_pCollider->render(_dc);
    }

    if (nullptr != m_pAnimator) // 애니메이션 렌더링
    {
        m_pAnimator->render(_dc);
    }
}

void CObject::CreateCollider()
{
    m_pCollider = new CCollider;
    m_pCollider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
    m_pAnimator = new CAnimator;
    m_pAnimator->m_pOwner = this;
}
