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

	//	// 플레이어를 찾아서 Object 타입으로 블랙보드에 기록한다.
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

	//애니메이션 등록
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



	//상태머신 블랙보드에 내 오브젝트 포인터 기록
	CGameObject* pSpikerosered = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"SpikeRosered");
	if (pSpikerosered)
	{
		StateMachine()->AddBlackboardData(L"SpikeRosered", BB_DATA::OBJECT, pSpikerosered);
	}

	
	//디버그용 확인
	Ptr<CFSM> MonsterFSM = StateMachine()->GetFSM();
	bool originFSM = MonsterFSM->GetOrigin();
	CStateMachine* MonsterSM = MonsterFSM->GetStateMachine();
	//
}

void CSpikeRoseredScript::tick()
{
	//디버그용 확인
	Ptr<CFSM> MyFSM = StateMachine()->GetFSM();
	bool originFSM = MyFSM->GetOrigin();
	CStateMachine* MySM = MyFSM->GetStateMachine();
	//

	//몬스터 스크립트에서는 state 불러와보면 다 복사본 FSM가리키는데 왜 내가 짠건 원본 FSM을 가리키냐. 그래서 FSM보고 상태머신 불러오려고 해도 null이여서 오류가난다.
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
	//등장씬

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

	//애니메이션 전환
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
	////위치 x 살짝이동
	//if (KEY_TAP(KEY::M))
	//{
	//	Vec3 vPos = Transform()->GetRelativePos();
	//	vPos.x -= 50.f;
	//	Transform()->SetRelativePos(vPos);
	//}
	//
	////공던지기 마지막 프레임에서 멈추기
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


	/*StateMachine에서 GetOwner로 본인을 소유한 오브젝트를 불러오는건되는데,
	  그 StateMachine의 FSM을 불러와서, 불러온 FSM의 StateMachine을 호출하고, 호출한 상태머신에서 GetOwner를 하면 오브젝트가 null이라고 뜸.. 
	  더정확한 분석을 해야겠지만, FSM으로부터 본인을 소유한 오브젝트를 호출할 방법은 없는 것같다. 대체 왜이러는지 모르겠다 논리적으로 이해가 안된다.. 
	  FSM이 오브젝트에 접근하려면 블랙보드에 미리 저장된 오브젝트 정보로만 접근이 가능한거 같다.
	  아래는 별의별 방법으로 FSM이 SpikeRosered 오브젝트 불러오게 하려고 노력한 흔적이다.*/
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


	

	//초록공 패턴시 공만들기
	
	if (KEY_TAP(KEY::P))
	{
		// Greenball Object 생성
		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"SpikeballGreen");
		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CCollider2D);
		pObj->AddComponent(new CAnimator2D);
		pObj->AddComponent(new CSpikeballGreenScript);
		//pObj->AddComponent(new CStateMachine);

		//보스의 pos 가져와서 그 위치 앞에서 만들기 일단 왼쪽만..
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

