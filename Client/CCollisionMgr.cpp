#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
    : m_arrCheck{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::init()
{
}

void CCollisionMgr::update()
{
    // 충돌을 할수 있게 검사
    for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
    {
        for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
        {
            if (m_arrCheck[iRow] & (1 << iCol))
            {
                CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
            }
        }
    }
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
    CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

    // 참조로 반환하니 참조로 받아야함, 참조를 안붙이면 지역변수로 받는것이기 때문에 원본이 바뀌지 않음
    const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
    const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

    map<ULONGLONG, bool>::iterator iter;

    // 충돌 진행 시키기
    for (size_t i = 0; i < vecLeft.size(); ++i)
    {
        // 충돌체를 보유하지 않는 경우
        if (nullptr == vecLeft[i]->GetCollider())
            continue;

        for (size_t j = 0; j < vecRight.size(); ++j)
        {
            // 충돌체가 없거나, 자기 자신과의 충돌인 경우
            if (nullptr == vecRight[j]->GetCollider() || vecLeft[i] == vecRight[j])
                continue;

            CCollider* pLeftCol = vecLeft[i]->GetCollider();
            CCollider* pRightCol = vecRight[j]->GetCollider();

            // 두 충돌체 조합 아이디 생성
            COLLIDER_ID ID;
            ID.Left_id = pLeftCol->GetID();
            ID.Right_id = pRightCol->GetID();

            // 이전 충돌 
            iter = m_mapColInfo.find(ID.ID); // 4바이트 + 4바이트 -> 8바이트 두 충돌체로만 나오는 ID -> map의 key 값으로 사용

            // 등록조차 안되어있으면 충돌여부를 완전 처음 조사 -> 충돌 X -> false로 설정
            // false면 충돌 X

            // 충돌 정보가 미등록 상태인 경우 충돌하지 않았다로 등록 
            if (m_mapColInfo.end() == iter)
            {
                m_mapColInfo.insert(make_pair(ID.ID, false));
                iter = m_mapColInfo.find(ID.ID);
            }

            // 충돌 검사
            if(IsCollision(pLeftCol, pRightCol))
            {
                // 이전 프레임을 알아야 충돌중인지 벗어났는지를 알아야함

                // 현재 충돌 중이다.
                if (iter->second)
                {
                    // 이전에도 충돌 하고 있었다. ( 인자로 누구랑 충돌했는지를 넣어줌 )
                 
                    if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
                    {
                        // 근데 둘 중 하나가 삭제 예정이라면, 충돌 해제 시켜준다
                        pLeftCol->OnCollisionExit(pRightCol);
                        pRightCol->OnCollisionExit(pLeftCol);
                        iter->second = false;
                    }
                    else
                    {
                        pLeftCol->OnCollision(pRightCol);
                        pRightCol->OnCollision(pLeftCol);
                    }
                }
                else
                {
                    // 이전에는 충돌하지 않았다.
                    // 근데 둘중 하나가 삭제 예정이라면, 충돌하지 않은것으로 취급
                    if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
                    {
                        pLeftCol->OnCollisionEnter(pRightCol);
                        pRightCol->OnCollisionEnter(pLeftCol);
                        iter->second = true;
                    }
                }
            }
            else
            {
                // 현재 충돌하고 있지 않다
                if (iter->second)
                {
                    // 이전에는 충돌하고 있었다.
                    pLeftCol->OnCollisionExit(pRightCol);
                    pRightCol->OnCollisionExit(pLeftCol);
                    iter->second = false;
                }
            }
        }
    }
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{   
    Vec2 vLeftPos = _pLeftCol->GetFinalPos();
    Vec2 vLeftScale = _pLeftCol->GetScale();

    Vec2 vRightPos = _pRightCol->GetFinalPos();
    Vec2 vRightScale = _pRightCol->GetScale();

    if (abs(vRightPos.x - vLeftPos.x) <= (vLeftScale.x + vRightScale.x) / 2.f
        && abs(vRightPos.y - vLeftPos.y) <= (vLeftScale.y + vRightScale.y) / 2.f)
    {
        return true;
    }

    return false;
}


void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
    // 더 작은 값의 그룹 타입을 행으로,
    // 큰 값을 열(비트) 로 사용

    UINT iRow = (UINT)_eLeft;
    UINT iCol = (UINT)_eRight;

    if (iCol < iRow)
    {
        iRow = (UINT)_eRight;
        iCol = (UINT)_eLeft;
    }

    if (m_arrCheck[iRow] & (1 << iCol))
    {
        m_arrCheck[iRow] &= ~(1 << iCol);
    }
    else
    {
        m_arrCheck[iRow] |= (1 << iCol);
    }
}
