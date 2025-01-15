#include "pch.h"
#include "CScene.h"

#include "CObject.h"

CScene::CScene()
{
}

CScene::~CScene()
{
    for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
    {
        for (size_t j = 0; j < m_arrObj[i].size(); ++j) // 벡터니까
        {
            // m_arrObj[i] 그룹벡터의 j 물체 삭제
            delete m_arrObj[i][j];
        }
    }
}

void CScene::update()
{
    for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
    {
        for (size_t j = 0; j < m_arrObj[i].size(); ++j)
        {
            m_arrObj[i][j]->update();
        }
    }
}

void CScene::finalupdate()
{
    for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
    {
        for (size_t j = 0; j < m_arrObj[i].size(); ++j)
        {
            m_arrObj[i][j]->finalupdate();
        }
    }
}

void CScene::render(HDC _dc)
{
    for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
    {
        for (size_t j = 0; j < m_arrObj[i].size(); ++j)
        {
            m_arrObj[i][j]->render(_dc);
        }
    }
}

