#include "pch.h"
#include "CScene_Tool.h"

#include "CKeyMgr.h"

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{
}

void CScene_Tool::Exit()
{
}

void CScene_Tool::update()
{
    CScene::update(); // 부모의 기능 호출

    if (KEY_TAP(KEY::ENTER)) // tool scene 전환
    {
        ChangeScene(SCENE_TYPE::START); // 이벤트 등록
    }
}

