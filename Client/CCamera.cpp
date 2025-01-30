#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CResMgr.h"
#include "CTexture.h"

CCamera::CCamera()
    : m_pTargetObj(nullptr)
    , m_fTime(1.f)
    , m_fSpeed(0.f)
    , m_fAccTime(0.5f)
    , m_pVeilTex(nullptr)
{
}

CCamera::~CCamera()
{

}

void CCamera::init()
{
    Vec2 vResolution = CCore::GetInst()->GetResolution();
    m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
}

void CCamera::update()
{
    if (m_pTargetObj)
    {
        if (m_pTargetObj->IsDead())
        {
            m_pTargetObj = nullptr;
        }
        else
        {
            m_vLookAt = m_pTargetObj->GetPos();
        }
    }

    if (KEY_HOLD(KEY::UP))
        m_vLookAt.y -= 500.f * fDT;
    if (KEY_HOLD(KEY::DOWN))
        m_vLookAt.y += 500.f * fDT;
    if (KEY_HOLD(KEY::LEFT))
        m_vLookAt.x -= 500.f * fDT;
    if (KEY_HOLD(KEY::RIGHT))
        m_vLookAt.x += 500.f * fDT;


    // 화면 중앙좌표와 카메라 LooAt 좌표간의 차이값 계산
    CalDiff();
}

void CCamera::render(HDC _dc)
{
    if (m_listCamEffect.empty())
        return;

    tCamEffect& effect = m_listCamEffect.front();
    effect.fCurTime += fDT;

    float fRatio = 0.f; // 이펙트 진행 비율
    fRatio = effect.fCurTime / effect.fDuration;

    if (fRatio < 0.f)
        fRatio = 0.f;
    if (fRatio > 1.f)
        fRatio = 1.f;

    int iAlpha = 0;

    if (CAM_EFFECT::FADE_OUT == effect.eEffect)
    {
        iAlpha = (int)(255.f * fRatio);
    }
    else if (CAM_EFFECT::FADE_IN == effect.eEffect)
    {
        iAlpha = (int)(255.f * (1.f - fRatio));
    }
     
    BLENDFUNCTION bf = {};

    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.AlphaFormat = 0;
    bf.SourceConstantAlpha = iAlpha;

    AlphaBlend(_dc, 0, 0
        , (int)m_pVeilTex->Width()
        , (int)m_pVeilTex->Height()
        , m_pVeilTex->GetDC()
        , 0, 0
        , (int)m_pVeilTex->Width()
        , (int)m_pVeilTex->Height(), bf);

    // 진행 시간이 이펙트 최대 지정 시간을 넘어선 경우
    if (effect.fDuration < effect.fCurTime)
    {
        // 효과 종료
        m_listCamEffect.pop_front();
        return;
    }
}

void CCamera::CalDiff()
{
    // 이전 LookAt 과 현재 Look 의 차이값을 보정해서 현재의 LookAt을 구한다
    
    m_fAccTime += fDT;

    if (m_fAccTime >= m_fTime)
    {
        m_vCurLookAt = m_vLookAt;
    }
    else
    {
        Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;
        
        if (!vLookDir.IsZero())
        {
            m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
        }
    }

    Vec2 vResolution = CCore::GetInst()->GetResolution();
    Vec2 vCenter = vResolution / 2;
    
    m_vDiff = m_vCurLookAt - vCenter;
    m_vPrevLookAt = m_vCurLookAt;
}
