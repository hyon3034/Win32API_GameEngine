#pragma once

//// 싱글톤 패턴
//// 객체의 생성을 1개로 제한
//// 언제 어디서든 쉽게 접근 가능
//class CCore
//{
//	static CCore* g_pInst;
//
//public:
//
//	// 정적 멤버함수
//	static CCore* GetInstance()
//	{
//
//		// 최초 호출 된 경우
//		if (nullptr == g_pInst)
//		{
//			g_pInst = new CCore;
//		}
//
//		return g_pInst;
//	}
//
//	static void Release() // 싱글톤 해제 함수
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


// Delete 할수가 없음. 프로그램이 종료될때까지 끌고 가야함 
// 중간에 지워질일이 없으니까 그냥 보통 데이터 영역에 올려놓고 씀

class CTexture;

class CCore
{
	SINGLE(CCore)

private :
	HWND  m_hWnd; // 메인 윈도우 핸들
	POINT m_ptResolution; // 해상도
	HDC m_hDC; // 메인 윈도우에 Draw 할 DC

    CTexture* m_pMemTex;    // 백버퍼 텍스쳐

    // 자주 사용하는 GDI Object
    HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
    HPEN m_arrPen[(UINT)PEN_TYPE::END];
    
    // 메뉴
    HMENU m_hMenu; // Tool Scene 에서만 사용


public :
	int init(HWND _hWnd, POINT _ptResolution); // 윈도우의 크기 조절
	void progress(); // 메세지가 발생하지 않는 대부분의 시간때 작업을 진행하는 함수

private:
    void Clear();
    void CreateBrushPen();
    
public:
    void DockMenu();
    void DivideMenu();
    void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);


public:
	HWND GetMainHwnd() { return m_hWnd; }
    HDC GetMainDC() { return m_hDC; }

    POINT GetResolution() { return m_ptResolution; }
    HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
    HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};