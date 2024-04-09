#pragma once
#include <Engine/CScript.h>

class CDebugScript :
    public CScript
{
private:


    Vec3            playerPos;
    wchar_t			text_playerPos[256];
    
public:
    virtual void tick() override;


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CDebugScript);
public:
    CDebugScript();
    ~CDebugScript();
};

