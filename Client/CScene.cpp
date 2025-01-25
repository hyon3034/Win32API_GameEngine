#include "pch.h"
#include "CScene.h"

#include "CObject.h"
#include "CTile.h"
#include "CResMgr.h"
#include "CPathMgr.h"

CScene::CScene()
    : m_iTileX(0)
    , m_iTileY(0)
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
            if (!m_arrObj[i][j]->IsDead())
            {
                m_arrObj[i][j]->update();
            }
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
        vector<CObject*>::iterator iter = m_arrObj[i].begin();


        for (; iter != m_arrObj[i].end();)
        {
            if (!(*iter)->IsDead())
            {
                (*iter)->render(_dc);
                ++iter;
            }
            else
            {
                iter = m_arrObj[i].erase(iter);
            }
        }
    }
}
void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
    Safe_Delete_Vec(m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
    for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
    {
        DeleteGroup((GROUP_TYPE)i);
    }
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
    DeleteGroup(GROUP_TYPE::TILE);

    m_iTileX = _iXCount;
    m_iTileY = _iYCount;

    CTexture * pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\TILE.bmp");

    for (UINT i = 0; i < _iYCount; ++i)
    {
        for (UINT j = 0; j < _iXCount; ++j)
        {
            CTile* pTile = new CTile();
            pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
            pTile->SetTexture(pTileTex);

            AddObject(pTile, GROUP_TYPE::TILE);
        }
    }
}

void CScene::LoadTile(const wstring& _strRelativePath)
{
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    // 커널 오브젝트
    FILE* pFile = nullptr;

    // 파일 읽기
    _wfopen_s(&pFile, strFilePath.c_str(), L"rb");
    assert(pFile);

    // 데이터 저장
    // 타일 가로 세로 갯수 불러오기
    UINT xCount = 0;
    UINT yCount = 0;

    fread(&xCount, sizeof(UINT), 1, pFile);
    fread(&yCount, sizeof(UINT), 1, pFile);

    // 불러온 개수에 맞게 EmptyTile 들 만들어 두기
    CreateTile(xCount, yCount);
    
    // 만들어진 타일 개별로 필요한 정보를 불러오게 함
    const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

    for (size_t i = 0; i < vecTile.size(); ++i)
    {
        ((CTile*)vecTile[i])->Load(pFile);
    }

    fclose(pFile);
}

