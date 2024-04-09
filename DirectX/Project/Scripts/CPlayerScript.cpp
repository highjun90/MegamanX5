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

	// GetPixel�Լ��� ��ȯ���� int�ε�, RGB()�Լ��� if���� ���� �ȴ�. RGB �Լ��� RGB�� 3���� ���ڷ� �־��ָ� ��Ʈ����� �˾Ƽ� int���� ��ȯ���ش�.
	
	// ������ڵ� �ؽ�ó �÷� Ȯ�� 
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


	//xyz�� ȸ��
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

	//����׿� ��ġ �̵� ����Ű
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



	//���� �ִϸ��̼� ������ ������ ���� idle�� �ʱ�ȭ
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
	//ȭ�鿡 �۾�
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
