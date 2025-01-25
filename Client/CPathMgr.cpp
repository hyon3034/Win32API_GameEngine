#include "pch.h"

#include "CPathMgr.h"

CPathMgr::CPathMgr()
    : m_szContentPath{}
{
}

CPathMgr::~CPathMgr()
{

}

void CPathMgr::init()
{
    GetCurrentDirectory(255, m_szContentPath); // m_szContentPath에 현재 경로가 채워짐

    int iLen = wcslen(m_szContentPath);

    // 상위 폴더로 이동 + bin\\content\\
    // 아이디어
    // \\를 뒤에서 부터 찾은뒤 문자열의 끝의 의미인 \0으로 변경

    for (int i = iLen - 1; i >= 0; --i)
    {
        if (m_szContentPath[i] == '\\')
        {
            m_szContentPath[i] = '\0';
            break;
        }
    }

    // + bin\\content\\ 붙이기

    wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");


}

wstring CPathMgr::GetRelativePath(const wchar_t* _filepath)
{ 
    wstring strFilePath = _filepath;

    // 절대 경로 길이 
    size_t iAbsLen = wcslen(m_szContentPath);
    
    // 전체 길이
    size_t iFullLen = strFilePath.length();

    wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen - iAbsLen);

    return strRelativePath;
}
