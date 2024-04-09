#pragma once

#include <Engine/CScript.h>

class CSpikeRoseredScript :
    public CScript
{
private:

    bool make_Greenball;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CSpikeRoseredScript);

    void SetMakeGreenball(bool _GB) { make_Greenball = _GB; }
    bool GetMakeGreenball() { return make_Greenball; }
public:
    CSpikeRoseredScript();
    ~CSpikeRoseredScript();
};

