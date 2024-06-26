#pragma once

#include <Engine/CScript.h>

class CPurpleRoseScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CPurpleRoseScript);
public:
    CPurpleRoseScript();
    ~CPurpleRoseScript();
};

