#pragma once
#include "singleton.h"

#include "CConstBuffer.h"


#include <string>
#include <filesystem>

class CBackgroundMgr :
    public CSingleton<CBackgroundMgr>
{
    SINGLE(CBackgroundMgr);

private:
    // BackgroundMagenta 상수버퍼. 픽셀쉐이더에 discard할지 안할지 데이터를 전달
    CConstBuffer* BGMgtConstBuffer;

    
    wstring BGMgtTexturePath;       //배경마젠타 텍스처가 있는 경로
    CGameObject* Player;           //플레이어 오브젝트
    Vec3 PlayerPos;                //플레이어 현재 좌표값


    wchar_t PlayerPosText[256];    //플레이어 좌표값 text
    wchar_t BGMgtColorText[256];   //배경 픽셀색깔 text
    wchar_t BGMgtPath[256];        //배경마젠타 텍스처 경로

    


    //배경마젠타 이미지 경로
    std::filesystem::path Path;

    HBITMAP BitMap;
    HBITMAP OldBitMap;
    HDC ImageDC;

    HDC BGMgtDC; 
    /* 원본 배경이미지에 배율을 적용시켜 이미지를 가리키려는 DC. 이걸만든이유는,
       지금 게임플레이에 보여지는 배경마젠타 이미지는 3배율을 적용해서 보여지는데 ImageDC에서는 원본 이미지 고대로여서
       GetPixel(ImageDC)하면 ImageDC 기준으로 픽셀 색상을 가져와서 내가 원하는 3배로 커진 배경이미지의 픽셀 색깔을 안가져 오고있음.
       따라서 이 BGMgtDC에는 ImageDC에 3배율을 적용시킨 배경이미지를 복사저장 시켜서 
       GetPixel(BGMgtDC)하면 게임플레이상에서 보이는 배경픽셀을 가져오게 싱크를 맞출거다.
     */

    BITMAP Info;

    //윈도우 HDC
    HDC windowHDC;

public:

    void init();
    void render();
    void GetPlayer(CGameObject* _Player)
    {
        Player = _Player;
    }
};