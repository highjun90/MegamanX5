#pragma once

#include <Engine/CScript.h>

class CSpikeballGreenScript :
    public CScript
{
private:
    bool Destroyself;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CSpikeballGreenScript);

    void SetDestroyself(bool _DS) { Destroyself = _DS; }
    bool GetDestroyself() { return Destroyself; }
public:
    CSpikeballGreenScript();
    ~CSpikeballGreenScript();
};

