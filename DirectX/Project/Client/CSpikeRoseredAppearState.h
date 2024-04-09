#pragma once
#include <Engine/CState.h>

class CSpikeRoseredAppearState :
    public CState
{
private:
    bool FirstAnimPlay;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CSpikeRoseredAppearState();
    ~CSpikeRoseredAppearState();

    void SetFirstAnimPlay(bool _Play) { FirstAnimPlay = _Play; }
    bool GetFirstAnimPlay() { return FirstAnimPlay; }

    int ReturnDebugInt(int _value) { return _value; }
};

#pragma once
