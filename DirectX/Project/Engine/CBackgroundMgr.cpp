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
	//땅체크 이미지 가져오기

	// 1.현재 실행파일 경로 불러오기
	Path = std::filesystem::current_path();

	// 2.content 폴더가 있는 상위폴더로 경로로 이동
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
			//MsgBoxAssert("루트 경로까지 샅샅히 뒤졌지만" + _ChildPath + "파일이나 폴더를 하위로 가지고 있는 경로를 찾지 못했습니다");
		}
	}

	// 3. texture 폴더의 충돌이미지가 있는 하위폴더로 경로로 이동
	std::filesystem::path CheckPath = Path;
	CheckPath.append("content\\texture\\BackGround_Magenta.bmp");
	if (false == std::filesystem::exists(CheckPath))
	{
		//MsgBoxAssert("존재하지 않는 경로로 이동하려고 했습니다." + CheckPath.string());
	}
	Path = CheckPath;
	string mapPath = Path.string();

	//텍스처 제대로된 경로로 불러왔는지 확인하려고 경로 저장해놓음. string을 wstring에 저장하는 코드.
	BGMgtTexturePath.assign(mapPath.begin(), mapPath.end());


	// 4. 경로로부터 이미지 핸들 가져오기
	HANDLE ImageHandle = LoadImageA(nullptr, mapPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// 5. 이미지핸들을 써서 비트맵 이미지로 저장
	BitMap = static_cast<HBITMAP>(ImageHandle);  //이미지 핸들 중 비트맵 핸들로 변경

	ImageDC = CreateCompatibleDC(nullptr);   // 윈도우에서 얻어와야할 이미지 수정권한 DC

	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));  //HDC와 비트맵 연결. 이제 HDC로 비트맵에 접근할수있음

	// 6. info 에 비트맵 이미지 정보들을 저장
	GetObject(BitMap, sizeof(BITMAP), &Info);
	BITMAP OldInfo;
	GetObject(OldBitMap, sizeof(BITMAP), &OldInfo);


	BGMgtDC = CreateCompatibleDC(ImageDC);   // 윈도우에서 얻어와야할 이미지 수정권한 DC
	//OldBitMap = static_cast<HBITMAP>(SelectObject(BGMgtDC, BitMap));  //HDC와 비트맵 연결. 이제 HDC로 비트맵에 접근할수있음
	// 7. 원본 배경이미지에 배율 적용해서 다른 DC에 복사저장하기
	//BitBlt(BGMgtDC,0,0, Info.bmWidth, Info.bmHeight, ImageDC,0,0,SRCCOPY); //이거 안됨. 원본 이미지 늘려서 복사하려면 다른 함수써야함.
	//BitBlt(ImageDC, 0, 0, Info.bmWidth, Info.bmHeight, BGMgtDC, 0, 0, SRCCOPY); //이거 안됨. 원본 이미지 늘려서 복사하려면 다른 함수써야함.
	StretchBlt(BGMgtDC,0,0, 6764, 935, ImageDC,0,0, 6764, 935, SRCCOPY);



	// GetPixel함수는 반환값이 int인데, RGB()함수로 if문을 쓰면 된다. RGB 함수는 RGB값 3개를 인자로 넣어주면 비트계산후 알아서 int값을 반환해준다.


	// 디버그코드 텍스처 컬러 확인 
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
		assert(L"배경매니저가 플레이어없다고합니다.");
	}

	PlayerPos = Player->Transform()->GetRelativePos();
	swprintf_s(PlayerPosText, 256, L"PlayerPos x : %f, y : %f", PlayerPos.x, PlayerPos.y);
	CFontMgr::GetInst()->DrawFont(PlayerPosText, 10.f, 50.f, 16, FONT_RGBA(255, 30, 30, 255));




	// 플레이어 좌표값의 배경텍스처 컬러 확인 
	int Color = GetPixel(BGMgtDC, PlayerPos.x, PlayerPos.y);
	//int Color = GetPixel(ImageDC, PlayerPos.x, PlayerPos.y);
	swprintf_s(BGMgtColorText, 256, L"PixelColor: %x", Color);
	CFontMgr::GetInst()->DrawFont(BGMgtColorText, 10.f, 70.f, 16, FONT_RGBA(255, 30, 30, 255));
	if (Color == RGB(0, 0, 0))
	{
		int a = 0;
	}

	//배경마젠타 경로
	CFontMgr::GetInst()->DrawFont(BGMgtTexturePath.c_str(), 10.f, 90.f, 16, FONT_RGBA(255, 30, 30, 255));


	//원본 비트맵 info
	wchar_t BitmapInfo[256];
	swprintf_s(BitmapInfo, 256, L"BitMap Info x : %d, y : %d", Info.bmWidth, Info.bmHeight);
	CFontMgr::GetInst()->DrawFont(BitmapInfo, 10.f, 110.f, 16, FONT_RGBA(255, 30, 30, 255));





}


