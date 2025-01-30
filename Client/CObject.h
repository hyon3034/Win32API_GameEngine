#pragma once
#include "global.h"
#include "CCamera.h"

class CCollider;
class CAnimator;
class CRigidBody;
class CGravity;

class CObject
{
private :
    wstring m_strName;

	Vec2 m_vPos;
	Vec2 m_vScale;

    // component
    CCollider* m_pCollider;
    CAnimator* m_pAnimator;
    CRigidBody* m_pRigidBody;
    CGravity* m_pGravity;

    bool m_bAlive;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

    void SetName(const wstring& _strName) { m_strName = _strName; }
    const wstring& GetName() { return m_strName; }

    CCollider* GetCollider() { return m_pCollider; }
    CAnimator* GetAnimator() { return m_pAnimator; }
    CRigidBody* GetRigidBody() { return m_pRigidBody; }
    CGravity* GetGravity() { return m_pGravity; }

    bool IsDead() { return !m_bAlive; }

    void CreateCollider();
    void CreateAnimator();
    void CreateRigidBody();
    void CreateGravity();

    virtual void OnCollision(CCollider* _pOther) {}
    virtual void OnCollisionEnter(CCollider* _pOther) {};
    virtual void OnCollisionExit(CCollider* _pOther) {};

public:
    virtual void start() {}; // Scene이 시작되기 직전에 호출되는 함수
    virtual void update() = 0;
    virtual void finalupdate();
    virtual void render(HDC _dc);

    void component_render(HDC _dc);

    // 자기 자신의 복제 버전을 되돌려주는 역할
    virtual CObject* Clone() = 0;

private:
    // 함부로 죽이면 안됨 ( Event Manager만 사용 가능 ) -> freind 클래스 사용
    void SetDead() { m_bAlive = false; }

public:
	CObject();
    CObject(const CObject& _origin);

	virtual ~CObject();

    friend class CEventMgr;
};

