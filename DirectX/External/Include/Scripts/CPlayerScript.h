#pragma once

#include <Engine/CScript.h>

#include <string>
#include <filesystem>





class CPlayerScript :
    public CScript
{

private:
    Ptr<CPrefab>    m_Missile;
    float           m_Speed;

    std::filesystem::path Path;

    HBITMAP BitMap;
    HBITMAP OldBitMap;
    HDC ImageDC;

    BITMAP Info;

    //À©µµ¿ì HDC
    HDC windowHDC;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    void render();

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CPlayerScript);
public:
    CPlayerScript();
    ~CPlayerScript();
};





