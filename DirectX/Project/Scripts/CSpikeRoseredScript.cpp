#include "pch.h"
#include "CSpikeRoseredScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include <Engine/CAnim.h>
#include "CSpikeballGreenScript.h"


CSpikeRoseredScript::CSpikeRoseredScript()
	: CScript(SPIKEROSEREDSCRIPT)
{
}

CSpikeRoseredScript::~CSpikeRoseredScript()
{
}

void CSpikeRoseredScript::begin()
{
	//if (StateMachine())
	//{
	//	StateMachine()->AddBlackboardData(L"DetectRange", BB_DATA::FLOAT, &m_DetectRange);
	//	StateMachine()->AddBlackboardData(L"Speed", BB_DATA::FLOAT, &m_Speed);

	//	// �÷��̾ ã�Ƽ� Object Ÿ������ �����忡 ����Ѵ�.
	//	CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	//	if (pPlayer)
	//	{
	//		StateMachine()->AddBlackboardData(L"TargetObject", BB_DATA::OBJECT, pPlayer);
	//	}

	//	if (nullptr != StateMachine()->GetFSM())
	//	{
	//		StateMachine()->GetFSM()->SetState(L"IdleState");
	//	}
	//}


	Vec2 colScale = {};
	colScale.x = 100;
	colScale.y = 150;
	Collider2D()->SetOffsetScale(colScale);

	//�ִϸ��̼� ���
	//idle
	Ptr<CTexture> Atlas_SpikeroseredIdleLeft = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Spikerosered_IdleLeft.png", L"texture\\Spikerosered_IdleLeft.png");
	Animator2D()->Create(L"Spikerosered_IdleLeft", Atlas_SpikeroseredIdleLeft, Vec2(0.f, 0.f), Vec2(256.f, 256.f), Vec2(0.f, 0.f), Vec2(128.f, 128.f), 5, 5);

	// Appear
	Ptr<CTexture> Atlas_SpikeRoseredAppear = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\SpikeRosered_Appear.png", L"texture\\SpikeRosered_Appear.png");
	Animator2D()->Create(L"SpikeRosered_Appear", Atlas_SpikeRoseredAppear, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(0.f, 0.f), Vec2(128.f, 128.f), 91, 30);
	//Animator2D()->Play(L"SpikeRosered_Appear");


	//Pattern SpikeballGreen
	Ptr<CTexture> Atlas_SpikeballGreenLeft = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Boss_SpikeballLeft.png", L"texture\\Boss_SpikeballLeft.png");
	Animator2D()->Create(L"Boss_SpikeballLeft", Atlas_SpikeballGreenLeft, Vec2(0.f, 0.f), Vec2(256.f, 256.f), Vec2(5.f, 5.f), Vec2(128.f, 128.f), 22, 35);
	Animator2D()->Play(L"Boss_SpikeballLeft");

	//Ptr<CTexture> Atlas_ZeroMoveLeft = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Zero_MoveLeft.png", L"texture\\Zero_MoveLeft.png");
	//Animator2D()->Create(L"Zero_MoveLeft", Atlas_ZeroMoveLeft, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(0.f, 0.f), Vec2(50.f, 50.f), 14, 24);



	//���¸ӽ� �����忡 �� ������Ʈ ������ ���
	CGameObject* pSpikerosered = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"SpikeRosered");
	if (pSpikerosered)
	{
		StateMachine()->AddBlackboardData(L"SpikeRosered", BB_DATA::OBJECT, pSpikerosered);
	}

	
	//����׿� Ȯ��
	Ptr<CFSM> MonsterFSM = StateMachine()->GetFSM();
	bool originFSM = MonsterFSM->GetOrigin();
	CStateMachine* MonsterSM = MonsterFSM->GetStateMachine();
	//
}

void CSpikeRoseredScript::tick()
{
	//����׿� Ȯ��
	Ptr<CFSM> MyFSM = StateMachine()->GetFSM();
	bool originFSM = MyFSM->GetOrigin();
	CStateMachine* MySM = MyFSM->GetStateMachine();
	//

	//���� ��ũ��Ʈ������ state �ҷ��ͺ��� �� ���纻 FSM����Ű�µ� �� ���� §�� ���� FSM�� ����Ű��. �׷��� FSM���� ���¸ӽ� �ҷ������� �ص� null�̿��� ����������.
	//Spikerosered->AddState(L"SpikeRoseredIdleState", new CSpikeRoseredIdleState);
	//Spikerosered->AddState(L"SpikeRoseredAppearState", new CSpikeRoseredAppearState);
	CState* MyState = MyFSM->FindState(L"SpikeRoseredIdleState");
	MyFSM = MyState->GetFSMDebug();
	originFSM = MyFSM->GetOrigin();

	//StateMachine()->GetFSM()->ChangeState(L"SpikeRoseredIdleState");

	int Debug = 0;


	//Ptr<CFSM> SpikeRoseredFSM = StateMachine()->GetFSM();
	//SpikeRoseredFSM->SetState(L"SpikeRoseredIdleState");

	//StateMachine()->GetFSM()->SetState(L"SpikeRoseredIdleState");
	//StateMachine()->GetFSM()->SetState(L"SpikeRosereAppearState");
	//�����

	//if (Animator2D()->FindAnim(L"SpikeRosered_Appear") == Animator2D()->GetCurAnim())
	//{
	//	Vec3 vPos = Transform()->GetRelativePos();
	//	CAnim* curAnim = Animator2D()->GetCurAnim();
	//	int curFrmIdx = curAnim->GetCurFrmIdx();

	//	if (curFrmIdx < 15)
	//	{
	//		if (curFrmIdx % 2 == 1)
	//			;
	//		vPos.y += DT * 300;
	//	}
	//	else if (curFrmIdx < 35)
	//		vPos.y += DT * 200;
	//	else if (curFrmIdx < 50)
	//		vPos.y -= DT * 200;
	//	else if (50 <= curFrmIdx < 50)
	//	{
	//		vPos.y -= DT * 300;

	//		if (vPos.y < -50.f)
	//			vPos.y = -50.f;
	//	}

	//	if (curFrmIdx == 90)
	//	{
	//		vPos.y = -50.f;
	//	}
	//	Transform()->SetRelativePos(vPos);
	//}

	//�ִϸ��̼� ��ȯ
	//if (KEY_TAP(KEY::B))
	//{ 
	//	Animator2D()->Play(L"Boss_SpikeballLeft");
	//}
	//
	//CAnim* curAnime = Animator2D()->GetCurAnim();
	//if (Animator2D()->FindAnim(L"Boss_SpikeballLeft") == curAnime)
	//{
	//	if (curAnime->GetCurFrmIdx() == 20)
	//	{
	//		SetMakeGreenball(true);
	//	}
	//}
	//



	//if (KEY_TAP(KEY::N))
	//{
	//	Animator2D()->Play(L"SpikeRosered_Appear");
	//}
	////��ġ x ��¦�̵�
	//if (KEY_TAP(KEY::M))
	//{
	//	Vec3 vPos = Transform()->GetRelativePos();
	//	vPos.x -= 50.f;
	//	Transform()->SetRelativePos(vPos);
	//}
	//
	////�������� ������ �����ӿ��� ���߱�
	//CAnim* CurAnim = Animator2D()->GetCurAnim();
	//if (Animator2D()->FindAnim(L"Boss_SpikeballLeft") == CurAnim)
	//{
	//	if (CurAnim->GetCurFrmIdx() == 21)
	//		CurAnim->SetAccTime(0);

	//}

	/*if (StateMachine())
	{

		if (nullptr != StateMachine()->GetFSM())
		{
			StateMachine()->GetFSM()->SetState(L"SpikeRoseredIdleState");
		}
	}*/


	/*StateMachine���� GetOwner�� ������ ������ ������Ʈ�� �ҷ����°ǵǴµ�,
	  �� StateMachine�� FSM�� �ҷ��ͼ�, �ҷ��� FSM�� StateMachine�� ȣ���ϰ�, ȣ���� ���¸ӽſ��� GetOwner�� �ϸ� ������Ʈ�� null�̶�� ��.. 
	  ����Ȯ�� �м��� �ؾ߰�����, FSM���κ��� ������ ������ ������Ʈ�� ȣ���� ����� ���� �Ͱ���. ��ü ���̷����� �𸣰ڴ� �������� ���ذ� �ȵȴ�.. 
	  FSM�� ������Ʈ�� �����Ϸ��� �����忡 �̸� ����� ������Ʈ �����θ� ������ �����Ѱ� ����.
	  �Ʒ��� ���Ǻ� ������� FSM�� SpikeRosered ������Ʈ �ҷ����� �Ϸ��� ����� �����̴�.*/
	if (KEY_TAP(KEY::I))
	{
		StateMachine()->GetFSM()->ChangeState(L"SpikeRoseredIdleState");
	}

	if (KEY_TAP(KEY::U))
	{
		StateMachine()->GetFSM()->ChangeState(L"SpikeRoseredAppearState");
	}

	if (KEY_TAP(KEY::Y))
	{
		StateMachine()->GetFSM()->ChangeState(L"SpikeRoseredWhipState");
	}


	

	//�ʷϰ� ���Ͻ� �������
	
	if (KEY_TAP(KEY::P))
	{
		// Greenball Object ����
		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"SpikeballGreen");
		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CCollider2D);
		pObj->AddComponent(new CAnimator2D);
		pObj->AddComponent(new CSpikeballGreenScript);
		//pObj->AddComponent(new CStateMachine);

		//������ pos �����ͼ� �� ��ġ �տ��� ����� �ϴ� ���ʸ�..
		Vec3 BossPos = Transform()->GetRelativePos();
		pObj->Transform()->SetRelativePos(Vec3(BossPos.x - 100, BossPos.y, 32.f - 4.f));
		//pObj->Transform()->SetRelativePos(Vec3(19400.f, -50.f, 32.f - 4.f));
		pObj->Transform()->SetRelativeScale(Vec3(700.f, 700.f, 1.f));

		pObj->Collider2D()->SetAbsolute(true);
		pObj->Collider2D()->SetOffsetScale(Vec2(300.f, 300.f));
		pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
		//pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Zero_IdleRight_oneFrame.png", L"texture\\Zero_IdleRight_oneFrame.png"));

        //CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(pObj, L"Monster", false);
		GamePlayStatic::SpawnGameObject(pObj,4);
	}



	

	//CGameObject* pObj = new CGameObject;
//pObj = new CGameObject;
//pObj->SetName(L"SpikeballGreen");
//pObj->AddComponent(new CTransform);
//pObj->AddComponent(new CMeshRender);
//pObj->AddComponent(new CCollider2D);
//pObj->AddComponent(new CAnimator2D);
//pObj->AddComponent(new CSpikeballGreenScript);
////pObj->AddComponent(new CStateMachine);

//pObj->Transform()->SetRelativePos(Vec3(19400.f, -50.f, 32.f - 4.f));
//pObj->Transform()->SetRelativeScale(Vec3(700.f, 700.f, 1.f));

//pObj->Collider2D()->SetAbsolute(true);
//pObj->Collider2D()->SetOffsetScale(Vec2(20.f, 20.f));
//pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

//pTempLevel->AddObject(pObj, L"Monster", false);
}

void CSpikeRoseredScript::SaveToFile(FILE* _File)
{
}

void CSpikeRoseredScript::LoadFromFile(FILE* _File)
{
}

