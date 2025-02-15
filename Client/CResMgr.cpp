#include "pch.h"

#include "CResMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
    Safe_Delete_Map(m_mapTex);
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    // 같은 키가 이미 있는지 확인
    CTexture* pTex = FindTexture(_strKey);
    if (pTex != nullptr)
    {
        return pTex;
    }

    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    pTex = new CTexture;
    pTex->Load(strFilePath);

    pTex->SetKey(_strKey);
    pTex->SetRelativePath(_strRelativePath);

    m_mapTex.insert(make_pair(_strKey, pTex));

    return pTex;
}

CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
    // 같은 키가 이미 있는지 확인
    CTexture* pTex = FindTexture(_strKey);
    
    if (pTex != nullptr)
    {
        return pTex;
    }

    // 파일로부터 로딩 X 바로 Create

    pTex = new CTexture;
    pTex->Create(_iWidth, _iHeight);
    pTex->SetKey(_strKey);

    m_mapTex.insert(make_pair(_strKey, pTex));

    return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
    map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);
    
    if (iter == m_mapTex.end()) // 찾지못함
    {
        return nullptr;
    }

    return (CTexture*)iter->second;
}

CSound* CResMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
    return nullptr;
}

CSound* CResMgr::FindSound(const wstring& _strKey)
{
    return nullptr;
}
