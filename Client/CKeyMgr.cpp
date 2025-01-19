#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"

int g_arrVK[(int)KEY::LAST] =
{
    VK_LEFT, // LEFT,
    VK_RIGHT, //RIGHT,
    VK_UP, //UP,
    VK_DOWN, //DOWN,

    'Q',
    'W',
    'E',
    'R',
    'T',
    'Y',
    'U',
    'I',
    'O',
    'P',
    'A',
    'S',
    'D',
    'F',
    'G',
    'Z',
    'X',
    'C',
    'V',
    'B',

    VK_MENU,
    VK_CONTROL,
    VK_LSHIFT,
    VK_SPACE,
    VK_RETURN,
    VK_ESCAPE,

    VK_LBUTTON,
    VK_RBUTTON,

    // LAST,
};


CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
    for (int i = 0; i < (int)KEY::LAST; ++i)
    {
        m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
    }

    m_vecKey[(int)KEY::LEFT].eState;
    m_vecKey[(int)KEY::LEFT].bPrevPush;
}

void CKeyMgr::update()
{
    // 윈도우 포커싱 알아내기
    // HWND hMainWnd = CCore::GetInst()->GetMainHwnd();

    HWND hWnd = GetFocus();

    // 윈도우 포커싱 중일때 키 동작
    if(nullptr != hWnd)
    {
        for (int i = 0; i < (int)KEY::LAST; ++i)
        {
            // 키가 눌려 있다.
            if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
            {
                if (m_vecKey[i].bPrevPush)
                {
                    // 이전에도 눌려있다 -> HOLD
                    m_vecKey[i].eState = KEY_STATE::HOLD;
                }
                else
                {
                    // 이전에 눌려있지 않았다 -> TAP
                    m_vecKey[i].eState = KEY_STATE::TAP;
                }

                m_vecKey[i].bPrevPush = true;
            }
            else
            {
                if (m_vecKey[i].bPrevPush)
                {
                    // 이전에 눌려있었다 -> 막떼짐 -> AWAY
                    m_vecKey[i].eState = KEY_STATE::AWAY;
                }
                else
                {
                    m_vecKey[i].eState = KEY_STATE::NONE;
                }

                m_vecKey[i].bPrevPush = false;
            }
        }

        // 마우스 위치 계산
        POINT ptPos = {};
        GetCursorPos(&ptPos);
        ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);

        m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);

    }
    else
    {
        for (int i = 0; i < (int)KEY::LAST; ++i)
        {
            m_vecKey[i].bPrevPush = false;
            
            if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
            {
                m_vecKey[i].eState = KEY_STATE::AWAY;
            }
            else if (KEY_STATE::AWAY == m_vecKey[i].eState)
            {
                m_vecKey[i].eState = KEY_STATE::NONE;
            }
        }
    }

}

