#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CObject.h"

// CCore* CCore::g_pInst = nullptr;

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{

}


CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
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


	// 이중 버퍼링 용도의 비트맵과 DC 를 만든다
	
	// m_hDC(메인 윈도우 DC)와 호환되는 비트맵 생성 ( 비트맵 ID 반환 )
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);

	// 그림을 그릴려면 DC가 필요. 뒤에서 그릴 캔버스를 타겟으로 하는 DC 생성
	m_memDC = CreateCompatibleDC(m_hDC);

	// 비트맵과 DC를 연결, 가지고 있던 BITMAP 반환
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);


	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
    CSceneMgr::GetInst()->init();

	return S_OK;
}

void CCore::progress() // 프로그램이 도는 곳
{
	// Manager Update
	CTimeMgr::GetInst()->update();
    CKeyMgr::GetInst()->update();

    CSceneMgr::GetInst()->update();

    // =============
    // Rendering
    // =============

    // 화면 청소
    // -1인 이유 (테투리선이 보이니까)
    Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

    CSceneMgr::GetInst()->render(m_memDC);

    // 비트맵을 복사
    BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
}