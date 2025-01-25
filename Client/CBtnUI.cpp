#include "pch.h"
#include "CBtnUI.h"



CBtnUI::CBtnUI()
    : CUI(false)
{
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::MouseOn()
{
}

void CBtnUI::MouseLbtnDown()
{
}

void CBtnUI::MouseLbtnUp()
{
}

void CBtnUI::MouseLbtnClicked()
{
    if (nullptr != m_pFunc)
    {
        // 호출할 함수 등록 && 함수 callback
        m_pFunc(m_param1, m_param2);
    }
}
