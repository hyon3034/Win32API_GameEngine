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

	RECT rt = {0,0, m_ptResolution.x, m_ptResolution.y}; // �»��, ���ϴ�

	// �ػ󵵿� �°� ������ ũ�� ����
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100,100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// Manager �ʱ�ȭ
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();

	g_obj.SetPos(Vec2((float)(m_ptResolution.x/2), (float)(m_ptResolution.y/2)));
	g_obj.SetScale(Vec2(100,100));

	return S_OK;
}

void CCore::progress() // ���α׷��� ���� ��
{
	// Manager Update
	CTimeMgr::GetInst()->update();

	update();

	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	// Ű�Է� ����, �񵿱� Ű�Է�
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // ���� Ű ����
	{
		vPos.x -= 200.f * CTimeMgr::GetInst()->GetfDT();
	}
	
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) // ���� Ű ����
	{
		vPos.x += 200.f * CTimeMgr::GetInst()->GetfDT();
	}

	g_obj.SetPos(vPos);

}

void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	// �׸���
	Rectangle(m_hDC , int(vPos.x - vScale.x / 2.f)
					, int(vPos.y - vScale.y / 2.f)
					, int(vPos.x + vScale.x / 2.f)
					, int(vPos.y + vScale.y / 2.f));
}
