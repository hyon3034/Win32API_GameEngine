#pragma once

class CCollider;

union COLLIDER_ID
{
    struct
    {
        UINT Left_id;
        UINT Right_id;
    };
    ULONGLONG ID;
}; // 8바이트 자료형

class CCollisionMgr
{
    SINGLE(CCollisionMgr)

private:
    // 그룹간의 충돌 체크 매트릭스
    UINT m_arrCheck[(UINT)GROUP_TYPE::END];

    // 충돌체 간의 프레임 충돌 정보
    map<ULONGLONG, bool> m_mapColInfo;


public:
    void init();
    void update();
    void CheckGroup(GROUP_TYPE eLeft, GROUP_TYPE eRight);
    void Reset() // 그룹간의 체크를 해제하는 함수
    {
        memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
    }

private:
    void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
    bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

