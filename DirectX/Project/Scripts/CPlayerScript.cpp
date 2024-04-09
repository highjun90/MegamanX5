#include "pch.h"
#include "CPlayerScript.h"
#include <Engine/CAssetMgr.h>

#include <Engine/CGameObject.h>
#include "CMissileScript.h"

#include <Engine/CEngine.h>

#include <Engine/CMaterial.h>
#include <Engine/CRenderComponent.h>
#include <Engine/CAnim.h>
#include <Engine/CFontMgr.h>


CPlayerScript::CPlayerScript()
	: CScript(PLAYERSCRIPT)
	, m_Speed(500.f)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Player Speed", &m_Speed);
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::begin()
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

	// GetPixel함수는 반환값이 int인데, RGB()함수로 if문을 쓰면 된다. RGB 함수는 RGB값 3개를 인자로 넣어주면 비트계산후 알아서 int값을 반환해준다.
	
	// 디버그코드 텍스처 컬러 확인 
	Vec3 CheckPos = Transform()->GetRelativePos();
	int Color = GetPixel(ImageDC, CheckPos.x, CheckPos.y-50);
	if (Color == RGB(0, 0, 0))
	{
		int a = 0;
	}

	//HANDLE ImageHandle = LoadImageA(nullptr, _Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);


	/*Ptr<CTexture> pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\link.png", L"texture\\link.png");
	Animator2D()->Create(L"IDLE_UP", pAltasTex, Vec2(0.f, 260.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(200.f, 200.f), 1, 10);
	Animator2D()->Create(L"IDLE_DOWN", pAltasTex, Vec2(0.f, 0.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(200.f, 200.f), 3, 10);
	Animator2D()->Create(L"IDLE_LEFT", pAltasTex, Vec2(0.f, 130.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(200.f, 200.f), 3, 10);
	Animator2D()->Create(L"IDLE_RIGHT", pAltasTex, Vec2(0.f, 390.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(200.f, 200.f), 3, 10);

	Animator2D()->Create(L"MOVE_UP", pAltasTex, Vec2(0.f, 780.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(200.f, 200.f), 10, 20);
	Animator2D()->Create(L"MOVE_DOWN", pAltasTex, Vec2(0.f, 520.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(200.f, 200.f), 10, 20);
	Animator2D()->Create(L"MOVE_LEFT", pAltasTex, Vec2(0.f, 650.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(200.f, 200.f), 10, 20);
	Animator2D()->Create(L"MOVE_RIGHT", pAltasTex, Vec2(0.f, 910.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(200.f, 200.f), 10, 20);*/


	//Zero

	//idle
	Ptr<CTexture> Atlas_ZeroIdleLeft = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Zero_IdleLeft.png", L"texture\\Zero_IdleLeft.png");
	Animator2D()->Create(L"Zero_IdleLeft", Atlas_ZeroIdleLeft, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(0.f, 0.f), Vec2(50.f, 50.f), 6, 4);
	Ptr<CTexture> Atlas_ZeroIdleRight = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Zero_IdleRight.png", L"texture\\Zero_IdleRight.png");
	Animator2D()->Create(L"Zero_IdleRight", Atlas_ZeroIdleRight, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(0.f, 0.f), Vec2(50.f, 50.f), 6, 4);

	//Move
	Ptr<CTexture> Atlas_ZeroMoveLeft = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Zero_MoveLeft.png", L"texture\\Zero_MoveLeft.png");
	Animator2D()->Create(L"Zero_MoveLeft", Atlas_ZeroMoveLeft, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(0.f, 0.f), Vec2(50.f, 50.f), 14, 24);
	Ptr<CTexture> Atlas_ZeroMoveRight = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Zero_MoveRight.png", L"texture\\Zero_MoveRight.png");
	Animator2D()->Create(L"Zero_MoveRight", Atlas_ZeroMoveRight, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(0.f, 0.f), Vec2(50.f, 50.f), 14, 24);


	//HitStrong
	Ptr<CTexture> Atlas_ZeroHitStrong = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Zero_HitStrong.png", L"texture\\Zero_HitStrong.png");
	Animator2D()->Create(L"Zero_HitStrong", Atlas_ZeroHitStrong, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(0.f, 0.f), Vec2(50.f, 50.f), 39, 40);

	GetRenderComponent()->GetDynamicMaterial();

	//m_Missile = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"MissilePrefab");
	//m_Missile = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\missile.pref", L"prefab\\missile.pref");
}

void CPlayerScript::tick()
{


	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();

	if (KEY_PRESSED(KEY::UP))
		vPos.y += DT * m_Speed;
	//if (KEY_TAP(KEY::UP))
	//	Animator2D()->Play(L"MOVE_UP");
	//if (KEY_RELEASED(UP))
	//	Animator2D()->Play(L"IDLE_UP");

	if (KEY_PRESSED(KEY::DOWN))
		vPos.y -= DT * m_Speed;
	/*if (KEY_TAP(KEY::DOWN))
		Animator2D()->Play(L"MOVE_DOWN");
	if (KEY_RELEASED(DOWN))
		Animator2D()->Play(L"IDLE_DOWN");*/

	if (KEY_PRESSED(KEY::LEFT))
		vPos.x -= DT * m_Speed;
	if (KEY_TAP(KEY::LEFT))
		//Animator2D()->Play(L"MOVE_LEFT");
		Animator2D()->Play(L"Zero_MoveLeft");
	if (KEY_RELEASED(LEFT))
		//Animator2D()->Play(L"IDLE_LEFT");
		Animator2D()->Play(L"Zero_IdleLeft");

	if (KEY_PRESSED(KEY::RIGHT))
		vPos.x += DT * m_Speed;
	if (KEY_TAP(KEY::RIGHT))
		//Animator2D()->Play(L"MOVE_RIGHT");
		Animator2D()->Play(L"Zero_MoveRight");
	if (KEY_RELEASED(RIGHT))
		//Animator2D()->Play(L"IDLE_RIGHT");
		Animator2D()->Play(L"Zero_IdleRight");


	//xyz축 회전
	//if (KEY_PRESSED(KEY::X))
	//{
	//	//vRot.x += DT * XM_PI;
	//}

	//if (KEY_PRESSED(KEY::Y))
	//{
	//	vRot.y += DT * XM_PI;
	//}

	//if (KEY_PRESSED(KEY::Z))
	//{
	//	//vRot.z += DT * XM_PI;
	//}

	//디버그용 위치 이동 단축키
	if (KEY_PRESSED(KEY::_1))
	{
		vPos.x = 0;
		vPos.y = 0;
	}

	if (KEY_PRESSED(KEY::_2))
	{
		vPos.x = 6000.f;
		vPos.y = 2100.f;
	}

	if (KEY_PRESSED(KEY::_3))
	{
		vPos.x = 19050;
		vPos.y = 150;
	}


	Transform()->SetRelativePos(vPos);
	Transform()->SetRelativeRotation(vRot);

	if (KEY_TAP(KEY::SPACE))
	{
		Instantiate(m_Missile, Transform()->GetWorldPos(), 0);
		//GamePlayStatic::Play2DSound(L"sound\\DM.wav", 1, 0.5f, false);
		GamePlayStatic::Play2DBGM(L"sound\\DM.wav", 0.5f);
	}

	if (KEY_PRESSED(KEY::SPACE))
	{
		Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 1);
		}
	}
	else if (KEY_RELEASED(KEY::SPACE))
	{
		Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 0);
		}
	}



	//맞은 애니메이션 프레임 끝까지 가면 idle로 초기화
	CAnim* CurAnim = Animator2D()->GetCurAnim();
	if (Animator2D()->FindAnim(L"Zero_HitStrong") == CurAnim)
	{
		if(CurAnim->GetCurFrmIdx() == 38)
		Animator2D()->Play(L"Zero_IdleRight");
	}



	//static float f = 0.f;
	//f += DT * 0.3f;
	//GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_1, f);

	//GamePlayStatic::DrawDebugRect(Vec3(0.f, 0.f, 0.f), Vec3(200.f, 200.f, 1.f), Vec3(0.f, 0.f, 0.f), Vec3(1.f, 1.f, 1.f), true, 20);
	//GamePlayStatic::DrawDebugCircle(Vec3(0.f, 0.f, 0.f), 200.f, Vec3(0.f, 1.f, 1.f), true);
}

void CPlayerScript::BeginOverlap(CCollider2D* _Collider
	, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	Ptr<CMaterial> pMtrl = GetRenderComponent()->GetDynamicMaterial();


	Vec3 vPos = Transform()->GetRelativePos();
	//vPos.x -= DT * 8000;
	Transform()->SetRelativePos(vPos);
	if (Animator2D()->GetCurAnim() != Animator2D()->FindAnim(L"Zero_HitStrong"))
		Animator2D()->Play(L"Zero_HitStrong");

	//Animator2D()->Play(L"Zero_HitStrong");
}

void CPlayerScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	Vec3 vPos = Transform()->GetRelativePos();
	//vPos.x -= DT * 500;
	Transform()->SetRelativePos(vPos);

}

void CPlayerScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	
}

void CPlayerScript::render()
{
	//화면에 글씨
	wchar_t	TestText[256];
	swprintf_s(TestText, 256, L"PlayerScriptText");
	CFontMgr::GetInst()->DrawFont(TestText, 10.f, 50.f, 16, FONT_RGBA(255, 30, 30, 255));
}

void CPlayerScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, sizeof(float), 1, _File);
}

void CPlayerScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, sizeof(float), 1, _File);
}
