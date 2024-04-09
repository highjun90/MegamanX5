#pragma once

#include <Engine/CScript.h>

class CMainCameraScript :
    public CScript
{
private:
    //float   m_fSpeed;

    CGameObject* MainPlayer;
    CGameObject* BackGround;
   

    bool followPlayer;



public:
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CMainCameraScript);

    void SetMainPlayer(CGameObject* _MainPlayer) { MainPlayer = _MainPlayer; }
    void SetBackGround(CGameObject* _MainPlayer) { BackGround = _MainPlayer; }

    void SetFollowPlayer(bool _follow) { followPlayer = _follow; }
    bool GetFollowPlayer() { return followPlayer; }

public:
    CMainCameraScript();
    ~CMainCameraScript();
};

