#include "pch.h"
#include "CPurpleRoseScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CPurpleRoseScript::CPurpleRoseScript()
	: CScript(PURPLEROSESCRIPT)
{
}

CPurpleRoseScript::~CPurpleRoseScript()
{
}

void CPurpleRoseScript::begin()
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

	// collision 

	Vec2 colScale = {};
	colScale.x = 100;
	colScale.y = 100;
	Collider2D()->SetOffsetScale(colScale);


	// AttackSpike
	
	Ptr<CTexture> Atlas_PurpleRose_ASLeft = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\PurpleRose_AttackSpikeLeft.png", L"texture\\PurpleRose_AttackSpikeLeft.png");
	Animator2D()->Create(L"PurpleRose_AttackSpikeLeft", Atlas_PurpleRose_ASLeft, Vec2(0.f, 0.f), Vec2(256.f, 256.f), Vec2(0.f, 0.f), Vec2(256.f, 256.f), 23, 20);
	Animator2D()->Play(L"PurpleRose_AttackSpikeLeft");

	Ptr<CTexture> Atlas_ZeroMoveLeft = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Zero_MoveLeft.png", L"texture\\Zero_MoveLeft.png");
	Animator2D()->Create(L"Zero_MoveLeft", Atlas_ZeroMoveLeft, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(0.f, 0.f), Vec2(50.f, 50.f), 14, 24);

}

void CPurpleRoseScript::tick()
{

	
	//if (KEY_TAP(KEY::LEFT))
		

}

void CPurpleRoseScript::SaveToFile(FILE* _File)
{
}

void CPurpleRoseScript::LoadFromFile(FILE* _File)
{
}

