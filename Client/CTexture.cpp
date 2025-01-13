#include "pch.h"

#include "CTexture.h"
#include "CCore.h"

CTexture::CTexture()
    : m_hBit(0)
    , m_dc(0)
    , m_bitInfo{}
{
}

CTexture::~CTexture()
{
    DeleteDC(m_dc);
    DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
    // 경로가 문제가 없다면 Image를 Load
    m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

    // 비트맵과 연결할 DC
    m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

    // 비트맵과 DC 연결
    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
    DeleteObject(hPrevBit);

    // 가로 세로 길이
    // 비트맵의 정보들을 저장하는 구조체 타입 BITMAP, 비트맵 정보
    GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

    assert(m_hBit);
}
