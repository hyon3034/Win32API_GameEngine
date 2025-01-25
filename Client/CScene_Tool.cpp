#include "pch.h"
#include "CScene_Tool.h"

#include "CKeyMgr.h"
#include "CTile.h"

#include "CCore.h"
#include "CResMgr.h"

#include "CSceneMgr.h"

#include "Resource.h"
#include "CUI.h"

#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CUIMgr.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{
    // 타일 생성
    CreateTile(5, 5);

    // UI 하나 만들어 보기
    Vec2 vResolution = CCore::GetInst()->GetResolution();

    CUI* pPanelUI = new CPanelUI;
    pPanelUI->SetName(L"ParentUI");
    pPanelUI->SetScale(Vec2(500.f, 300.f));
    pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

    CBtnUI* pBtnUI = new CBtnUI;
    pBtnUI->SetName(L"ChildUI");
    pBtnUI->SetScale(Vec2(100.f, 40.f));
    pBtnUI->SetPos(Vec2(0.f, 0.f)); // 부모로부터 상대위치

    pPanelUI->AddChild(pBtnUI);

    AddObject(pPanelUI, GROUP_TYPE::UI);

    CUI* pClonePanel = pPanelUI->Clone();
    pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));
    ((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(ChangeScene, 0, 0);

    AddObject(pClonePanel, GROUP_TYPE::UI);

    m_pUI = pClonePanel;

    // Camera Look 지정
    CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}
    

void CScene_Tool::Exit()
{   
    DeleteAll();
}

void CScene_Tool::update()
{
    CScene::update(); // 부모의 기능 호출

    SetTileIdx();

    if (KEY_TAP(KEY::LSHIFT))
    {
        CUIMgr::GetInst()->SetFocusedUI(m_pUI);
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

