#pragma once
class CPathMgr
{
    SINGLE(CPathMgr);

private:
    wchar_t m_szContentPath[255];

public:
    void init();
    const wchar_t* GetContentPath() { return m_szContentPath; }
};

