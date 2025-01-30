#include "pch.h"
#include "CScene_Tool.h"

#include "CKeyMgr.h"
#include "CTile.h"

#include "CCore.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"

#include "Resource.h"
#include "CUI.h"

#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CUIMgr.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
    : m_pUI(nullptr)
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{
    // 툴 Scene 에서 사용할 메뉴를 붙인다
    CCore::GetInst()->DockMenu();

    // 타일 생성
    CreateTile(5, 5);

    // UI 하나 만들어 보기
    Vec2 vResolution = CCore::GetInst()->GetResolution();

    CUI* pPanelUI = new CPanelUI;
    pPanelUI->SetName(L"ParentUI");
    pPanelUI->SetScale(Vec2(300.f, 150.f));
    pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

    CBtnUI* pBtnUI = new CBtnUI;
    pBtnUI->SetName(L"ChildUI");
    pBtnUI->SetScale(Vec2(100.f, 40.f));
    pBtnUI->SetPos(Vec2(0.f, 0.f)); // 부모로부터 상대위치
    ((CBtnUI*)pBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::SaveTileData);
    pPanelUI->AddChild(pBtnUI);
    AddObject(pPanelUI, GROUP_TYPE::UI);

    
    // 복사본 UI
    //CUI* pClonePanel = pPanelUI->Clone();
    //pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));
    //((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(ChangeScene, 0, 0);

    //AddObject(pClonePanel, GROUP_TYPE::UI);

    //m_pUI = pClonePanel;

    // Camera Look 지정
    CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}
    

void CScene_Tool::Exit()
{   
    CCore::GetInst()->DivideMenu();

    DeleteAll();
}

void CScene_Tool::update()
{
    CScene::update(); // 부모의 기능 호출

    SetTileIdx();

    //if (KEY_TAP(KEY::LSHIFT))
    //{
    //    //CUIMgr::GetIns\t()->SetFocusedUI(m_pUI);
    //    SaveTileData();
    //}

    if (KEY_TAP(KEY::CTRL))
    {
        //CUIMgr::GetIns\t()->SetFocusedUI(m_pUI);
        LoadTileData();
    }
}

void CScene_Tool::SetTileIdx()
{
    if (KEY_TAP(KEY::LBTN))
    {
        Vec2 vMousePos = MOUSE_POS;
        vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

        int iTileX = (int)GetTileX();
        int iTileY = (int)GetTileY();

        int iCol = (int)vMousePos.x / TILE_SIZE;
        int iRow = (int)vMousePos.y / TILE_SIZE;

        if (vMousePos.x < 0.f || iTileX <= iCol
            || vMousePos.y < 0.f || iTileX <= iRow)
        {
            return;
        }

        UINT iIdx = iRow * iTileX + iCol;

        const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
        ((CTile*)vecTile[iIdx])->AddImgIdx();
    }
}

void CScene_Tool::SaveTileData()
{
    wchar_t szName[256] = {};

    OPENFILENAME ofn = {};

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
    // 완성된 경로가 채워질 곳
    ofn.lpstrFile = szName;
    ofn.nMaxFile = sizeof(szName);
    // 아무 이름이나 아무 확장자 여도 됨 ( 이 필터들만 적용되서 골라짐 )
    ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
    ofn.nFilterIndex = 0;
    ofn.lpstrFileTitle = nullptr;
    ofn.nMaxFileTitle = 0;

    wstring strTileFolder = CPathMgr::GetInst()->GetContentPath(); // 절대경로
    strTileFolder += L"tile";

    ofn.lpstrInitialDir = strTileFolder.c_str();
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // 창 열어주는 함수, Modal 방식
    if (GetSaveFileName(&ofn)) // 저장하기를 눌렀을때, true값 반환
    {
        SaveTile(szName);
    }
}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
    // 커널 오브젝트
    FILE* pFile = nullptr;
    
    // 이중포인터 wb ( 바이너리로 쓰기, b를 안쓰면 문자로 저장함 )
    _wfopen_s(&pFile, _strFilePath.c_str(), L"wb");

    assert(pFile);

    // 데이터 저장
    UINT xCount = GetTileX();
    UINT yCount = GetTileY();

    fwrite(&xCount, sizeof(UINT), 1, pFile);
    fwrite(&yCount, sizeof(UINT), 1, pFile);

    // 모든 타일들을 개별적으로 저장할 데이터를 저장하게 함
    const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
    
    for (size_t i = 0; i < vecTile.size(); ++i)
    {
        ((CTile*)vecTile[i])->Save(pFile);
    }
    
    fclose(pFile);
}

void CScene_Tool::LoadTileData()
{
    wchar_t szName[256] = {};

    OPENFILENAME ofn = {};

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
    // 완성된 경로가 채워질 곳
    ofn.lpstrFile = szName;
    ofn.nMaxFile = sizeof(szName);
    // 아무 이름이나 아무 확장자 여도 됨 ( 이 필터들만 적용되서 골라짐 )
    ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
    ofn.nFilterIndex = 0;
    ofn.lpstrFileTitle = nullptr;
    ofn.nMaxFileTitle = 0;

    wstring strTileFolder = CPathMgr::GetInst()->GetContentPath(); // 절대경로
    strTileFolder += L"tile";

    ofn.lpstrInitialDir = strTileFolder.c_str();
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // 창 열어주는 함수, Modal 방식
    if (GetOpenFileName(&ofn)) // 저장하기를 눌렀을때, true값 반환
    {
        wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
        LoadTile(strRelativePath);
    }
}

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
    // 버튼 눌렀을시 CScene_Start로 이동
    ChangeScene(SCENE_TYPE::START);
}



// ===========================
// Tile Count Window Proc
// ===========================

INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
            UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

            CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
            
            // 무조건 Tool Scene에서만 동작하는지 확인
            CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
            assert(pToolScene);

            pToolScene->DeleteGroup(GROUP_TYPE::TILE);
            pToolScene->CreateTile(iXCount, iYCount);


            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if(LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

