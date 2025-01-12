#pragma once

//전방선언 ( 실제 타입에 대한 구체적인 정보 X , 포인터 타입으로 밖에 사용 불가능 )
class CObject;

class CScene
{
private:
    vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 저장 및 관리할 벡터를 그룹 개수 만큼 선언
    wstring m_strName; // Scene 이름

public:
    void SetName(const wstring& _strName) { m_strName = _strName; }
    const wstring& GetName() { return m_strName; }
    
    void update();
    void render(HDC _dc);

    virtual void Enter() = 0; // 해당 Scene에 진입 시 호출
    virtual void Exit() = 0; // 해당 Scene을 탈출 시 호출

protected:
    void AddObject(CObject* _pObj, GROUP_TYPE _eType)
    {
        m_arrObj[(UINT)_eType].push_back(_pObj);
    }

public:
    CScene();
    virtual ~CScene();
};

