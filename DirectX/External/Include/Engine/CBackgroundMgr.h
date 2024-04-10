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
    // BackgroundMagenta �������. �ȼ����̴��� discard���� ������ �����͸� ����
    CConstBuffer* BGMgtConstBuffer;

    
    wstring BGMgtTexturePath;       //��渶��Ÿ �ؽ�ó�� �ִ� ���
    CGameObject* Player;           //�÷��̾� ������Ʈ
    Vec3 PlayerPos;                //�÷��̾� ���� ��ǥ��


    wchar_t PlayerPosText[256];    //�÷��̾� ��ǥ�� text
    wchar_t BGMgtColorText[256];   //��� �ȼ����� text
    wchar_t BGMgtPath[256];        //��渶��Ÿ �ؽ�ó ���

    


    //��渶��Ÿ �̹��� ���
    std::filesystem::path Path;

    HBITMAP BitMap;
    HBITMAP OldBitMap;
    HDC ImageDC;

    HDC BGMgtDC; 
    /* ���� ����̹����� ������ ������� �̹����� ����Ű���� DC. �̰ɸ���������,
       ���� �����÷��̿� �������� ��渶��Ÿ �̹����� 3������ �����ؼ� �������µ� ImageDC������ ���� �̹��� ���ο���
       GetPixel(ImageDC)�ϸ� ImageDC �������� �ȼ� ������ �����ͼ� ���� ���ϴ� 3��� Ŀ�� ����̹����� �ȼ� ������ �Ȱ��� ��������.
       ���� �� BGMgtDC���� ImageDC�� 3������ �����Ų ����̹����� �������� ���Ѽ� 
       GetPixel(BGMgtDC)�ϸ� �����÷��̻󿡼� ���̴� ����ȼ��� �������� ��ũ�� ����Ŵ�.
     */

    BITMAP Info;

    //������ HDC
    HDC windowHDC;

public:

    void init();
    void render();
    void GetPlayer(CGameObject* _Player)
    {
        Player = _Player;
    }
};