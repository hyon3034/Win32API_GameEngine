#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CCamera.h"

CAnimation::CAnimation()
    : m_pAnimator(nullptr)
    , m_pTex(nullptr)
    , m_iCurFrm(0)
    , m_fAccTime(0.f)
    , m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::update()
{
    if (m_bFinish)
        return;

    m_fAccTime += fDT;

    if(m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
    {
        ++m_iCurFrm;

        if (m_vecFrm.size() <= m_iCurFrm)
        {
            m_iCurFrm = -1;
            m_bFinish = true;
            m_fAccTime = 0.f;
            return;
        }

        m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
    }
}

void CAnimation::render(HDC _dc)
{
    if (m_bFinish)
        return;

    CObject* pObj = m_pAnimator->GetObj();
    Vec2 vPos = pObj->GetPos();

    vPos += m_vecFrm[m_iCurFrm].vOffset; // Object Offset 만큼 추가 이동

    vPos = CCamera::GetInst()->GetRenderPos(vPos);

    TransparentBlt(_dc
        , (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
        , (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
        , (int)(m_vecFrm[m_iCurFrm].vSlice.x               )
        , (int)(m_vecFrm[m_iCurFrm].vSlice.y               )
        , m_pTex -> GetDC()
        , (int)(m_vecFrm[m_iCurFrm].vLT.x                  )
        , (int)(m_vecFrm[m_iCurFrm].vLT.y                  )
        , (int)(m_vecFrm[m_iCurFrm].vSlice.x               )
        , (int)(m_vecFrm[m_iCurFrm].vSlice.y               )
        , RGB(255, 0, 255)
        );
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration,  UINT _iFrameCount)
{
    m_pTex = _pTex;

    tAnimFrm frm = {};

    for (UINT i = 0; i < _iFrameCount; ++i)
    {
        frm.fDuration = _fDuration;
        frm.vSlice = _vSliceSize;
        frm.vLT = _vLT + _vStep * (float)i;

        m_vecFrm.push_back(frm);
    }
} 