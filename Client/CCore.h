#pragma once

//// �̱��� ����
//// ��ü�� ������ 1���� ����
//// ���� ��𼭵� ���� ���� ����
//class CCore
//{
//	static CCore* g_pInst;
//
//public:
//
//	// ���� ����Լ�
//	static CCore* GetInstance()
//	{
//
//		// ���� ȣ�� �� ���
//		if (nullptr == g_pInst)
//		{
//			g_pInst = new CCore;
//		}
//
//		return g_pInst;
//	}
//
//	static void Release() // �̱��� ���� �Լ�
//	{
//		if (nullptr != g_pInst)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//	}
//private:
//	CCore();
//	~CCore();
//};


// Delete �Ҽ��� ����. ���α׷��� ����ɶ����� ���� ������ 
// �߰��� ���������� �����ϱ� �׳� ���� ������ ������ �÷����� ��

class CCore
{
	SINGLE(CCore)

private :
	HWND  m_hWnd; // ���� ������ �ڵ�
	POINT m_ptResolution; // �ػ�
	HDC m_hDC; // ���� �����쿡 Draw �� DC

public :
	int init(HWND _hWnd, POINT _ptResolution); // �������� ũ�� ����
	void progress(); // �޼����� �߻����� �ʴ� ��κ��� �ð��� �۾��� �����ϴ� �Լ�

private :
	void update();
	void render();

public:
	HWND GetMainHwnd() { return m_hWnd; }
};