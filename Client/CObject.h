#pragma once

class CCollider;

class CObject
{
private :
    wstring m_strName;

	Vec2 m_vPos;
	Vec2 m_vScale;

    CCollider* m_pCollider;


public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

    CCollider* GetCollider() { return m_pCollider; }
    void CreateCollider();

    virtual void OnCollision(CCollider* _pOther) {}
    virtual void OnCollisionEnter(CCollider* _pOther) {};
    virtual void OnCollisionExit(CCollider* _pOther) {};

public:
    virtual void update() = 0;
    virtual void finalupdate() final;
    virtual void render(HDC _dc);

    void component_render(HDC _dc);

public:
	CObject();
	virtual ~CObject();
};

