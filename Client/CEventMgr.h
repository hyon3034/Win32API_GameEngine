#pragma once

// 이벤트 정보
struct tEvent
{
    EVENT_TYPE eEven;
    DWORD_PTR lParam;
    DWORD_PTR wParam;
};

class CEventMgr
{
    SINGLE(CEventMgr)
private:
    // event를 취합해서 모아둘 m_vecEvent
    vector<tEvent> m_vecEvent;

    vector<CObject*> m_vecDead;

public:
    // 이벤트 실행 함수
    void update();

private:
    // 이벤트 처리 함수
    void Excute(const tEvent& _eve);

public:
    // 이벤트 받기
    void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }
};

