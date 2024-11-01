#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CObject.h"

// CCore* CCore::g_pInst = nullptr;

CObject g_obj;

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
{

}


CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
}


int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	RECT rt = {0,0, m_ptResolution.x, m_ptResolution.y}; // 좌상단, 우하단

	// 해상도에 맞게 윈도우 크기 조정
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100,100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();

	g_obj.SetPos(Vec2((float)(m_ptResolution.x/2), (float)(m_ptResolution.y/2)));
	g_obj.SetScale(Vec2(100,100));

	return S_OK;
}

void CCore::progress() // 프로그램이 도는 곳
{
	// Manager Update
	CTimeMgr::GetInst()->update();

	update();

	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	// 키입력 받음, 비동기 키입력
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // 왼쪽 키 눌림
	{
		vPos.x -= 200.f * CTimeMgr::GetInst()->GetfDT();
	}
	
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) // 왼쪽 키 눌림
	{
		vPos.x += 200.f * CTimeMgr::GetInst()->GetfDT();
	}

	g_obj.SetPos(vPos);

}

void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	// 그리기
	Rectangle(m_hDC , int(vPos.x - vScale.x / 2.f)
					, int(vPos.y - vScale.y / 2.f)
					, int(vPos.x + vScale.x / 2.f)
					, int(vPos.y + vScale.y / 2.f));
}
