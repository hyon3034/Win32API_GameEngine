#pragma once

class CObject;

class CRigidBody
{
private:
    CObject* m_pOwner;

    Vec2 m_vForce; // 크기, 방향
    Vec2 m_vAccel; // 가속도
    Vec2 m_vAccelA; // 가속도 추가값
    Vec2 m_vVelocity; // 속도

    Vec2 m_vMaxVelocity; // 최대 속도

    // F = M * A;
    // V += A * DT -> 현재 속도

    float m_fMass; // 질량

    float m_fFricCoeff; // 마찰 계수

public:
    void finalupdate();

public:
    void AddForce(Vec2 _vF)
    {
        // 힘 누적
        m_vForce += _vF;
    }

    void SetMass(float _fMass)
    {
        m_fMass = _fMass;
    }

    float GetMass()
    {
        return m_fMass;
    }

    float GetSpeed()
    {
        return m_vVelocity.Length();
    }

    void SetVelocity(Vec2 _v)
    {
        m_vVelocity = _v; 
    }

    void AddVelocity(Vec2 _v)
    {
        m_vVelocity += _v;
    }

    void SetMaxVelocity(Vec2 _v)
    {
        m_vMaxVelocity = _v;
    }

    void SetAccelAlpha(Vec2 _vAccel)
    {
        m_vAccelA = _vAccel;
    }

    Vec2 GetVelocity() { return m_vVelocity; }


private:
    void Move();
    
public:
    CRigidBody();
    ~CRigidBody();

    friend class CObject;
};

