#include "pch.h"
#include "CBackgroundMgr.h"

#include "CGameObject.h"
#include "CTransform.h"
#include "CFontMgr.h"

CBackgroundMgr::CBackgroundMgr()
	:Player(nullptr)
	,PlayerPos()
	,PlayerPosText()
{

}

CBackgroundMgr::~CBackgroundMgr()
{

}

void CBackgroundMgr::init()
{
	//��üũ �̹��� ��������

	// 1.���� �������� ��� �ҷ�����
	Path = std::filesystem::current_path();

	// 2.content ������ �ִ� ���������� ��η� �̵�
	while (true)
	{
		std::filesystem::path CheckPath = Path;

		CheckPath.append("content");

		if (false == std::filesystem::exists(CheckPath))
		{
			Path = Path.parent_path();
		}
		else
		{
			break;
		}

		if (Path == Path.root_path())
		{
			//MsgBoxAssert("��Ʈ ��α��� ������ ��������" + _ChildPath + "�����̳� ������ ������ ������ �ִ� ��θ� ã�� ���߽��ϴ�");
		}
	}

	// 3. texture ������ �浹�̹����� �ִ� ���������� ��η� �̵�
	std::filesystem::path CheckPath = Path;
	CheckPath.append("content\\texture\\BackGround_Magenta.bmp");
	if (false == std::filesystem::exists(CheckPath))
	{
		//MsgBoxAssert("�������� �ʴ� ��η� �̵��Ϸ��� �߽��ϴ�." + CheckPath.string());
	}
	Path = CheckPath;
	string mapPath = Path.string();

	//�ؽ�ó ����ε� ��η� �ҷ��Դ��� Ȯ���Ϸ��� ��� �����س���. string�� wstring�� �����ϴ� �ڵ�.
	BGMgtTexturePath.assign(mapPath.begin(), mapPath.end());


	// 4. ��ηκ��� �̹��� �ڵ� ��������
	HANDLE ImageHandle = LoadImageA(nullptr, mapPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// 5. �̹����ڵ��� �Ἥ ��Ʈ�� �̹����� ����
	BitMap = static_cast<HBITMAP>(ImageHandle);  //�̹��� �ڵ� �� ��Ʈ�� �ڵ�� ����

	ImageDC = CreateCompatibleDC(nullptr);   // �����쿡�� ���;��� �̹��� �������� DC

	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));  //HDC�� ��Ʈ�� ����. ���� HDC�� ��Ʈ�ʿ� �����Ҽ�����

	// 6. info �� ��Ʈ�� �̹��� �������� ����
	GetObject(BitMap, sizeof(BITMAP), &Info);
	BITMAP OldInfo;
	GetObject(OldBitMap, sizeof(BITMAP), &OldInfo);


	BGMgtDC = CreateCompatibleDC(ImageDC);   // �����쿡�� ���;��� �̹��� �������� DC
	//OldBitMap = static_cast<HBITMAP>(SelectObject(BGMgtDC, BitMap));  //HDC�� ��Ʈ�� ����. ���� HDC�� ��Ʈ�ʿ� �����Ҽ�����
	// 7. ���� ����̹����� ���� �����ؼ� �ٸ� DC�� ���������ϱ�
	//BitBlt(BGMgtDC,0,0, Info.bmWidth, Info.bmHeight, ImageDC,0,0,SRCCOPY); //�̰� �ȵ�. ���� �̹��� �÷��� �����Ϸ��� �ٸ� �Լ������.
	//BitBlt(ImageDC, 0, 0, Info.bmWidth, Info.bmHeight, BGMgtDC, 0, 0, SRCCOPY); //�̰� �ȵ�. ���� �̹��� �÷��� �����Ϸ��� �ٸ� �Լ������.
	StretchBlt(BGMgtDC,0,0, 6764, 935, ImageDC,0,0, 6764, 935, SRCCOPY);



	// GetPixel�Լ��� ��ȯ���� int�ε�, RGB()�Լ��� if���� ���� �ȴ�. RGB �Լ��� RGB�� 3���� ���ڷ� �־��ָ� ��Ʈ����� �˾Ƽ� int���� ��ȯ���ش�.


	// ������ڵ� �ؽ�ó �÷� Ȯ�� 
	/*Vec3 CheckPos = Transform()->GetRelativePos();
	int Color = GetPixel(ImageDC, CheckPos.x, CheckPos.y - 50);
	if (Color == RGB(0, 0, 0))
	{
		int a = 0;
	}*/

	
}


void CBackgroundMgr::render()
{
	if (nullptr == Player)
	{
		assert(L"���Ŵ����� �÷��̾���ٰ��մϴ�.");
	}

	PlayerPos = Player->Transform()->GetRelativePos();
	swprintf_s(PlayerPosText, 256, L"PlayerPos x : %f, y : %f", PlayerPos.x, PlayerPos.y);
	CFontMgr::GetInst()->DrawFont(PlayerPosText, 10.f, 50.f, 16, FONT_RGBA(255, 30, 30, 255));




	// �÷��̾� ��ǥ���� ����ؽ�ó �÷� Ȯ�� 
	int Color = GetPixel(BGMgtDC, PlayerPos.x, PlayerPos.y);
	//int Color = GetPixel(ImageDC, PlayerPos.x, PlayerPos.y);
	swprintf_s(BGMgtColorText, 256, L"PixelColor: %x", Color);
	CFontMgr::GetInst()->DrawFont(BGMgtColorText, 10.f, 70.f, 16, FONT_RGBA(255, 30, 30, 255));
	if (Color == RGB(0, 0, 0))
	{
		int a = 0;
	}

	//��渶��Ÿ ���
	CFontMgr::GetInst()->DrawFont(BGMgtTexturePath.c_str(), 10.f, 90.f, 16, FONT_RGBA(255, 30, 30, 255));


	//���� ��Ʈ�� info
	wchar_t BitmapInfo[256];
	swprintf_s(BitmapInfo, 256, L"BitMap Info x : %d, y : %d", Info.bmWidth, Info.bmHeight);
	CFontMgr::GetInst()->DrawFont(BitmapInfo, 10.f, 110.f, 16, FONT_RGBA(255, 30, 30, 255));





}


