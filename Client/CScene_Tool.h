#pragma once
#include "CScene.h"

class CUI;

class CScene_Tool : public CScene
{
private:
    CUI* m_pUI;

public:
    virtual void Enter();
    virtual void Exit();
    virtual void update();
    
public:
    void SetTileIdx();

    void SaveTileData();
    void SaveTile(const wstring& _strRelativePath);

    void LoadTileData();

public:
    CScene_Tool();
    ~CScene_Tool();
};