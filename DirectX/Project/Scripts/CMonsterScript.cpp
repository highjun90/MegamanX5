#include "pch.h"
#include "CMonsterScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CMonsterScript::CMonsterScript()
	: CScript(MONSTERSCRIPT)
	, m_DetectRange(400.f)
	, m_Speed(200.f)
{
}

CMonsterScript::~CMonsterScript()
{
}

void CMonsterScript::begin()
{
	if (StateMachine())
	{
		StateMachine()->AddBlackboardData(L"DetectRange", BB_DATA::FLOAT, &m_DetectRange);
		StateMachine()->AddBlackboardData(L"Speed", BB_DATA::FLOAT, &m_Speed);

		// 플레이어를 찾아서 Object 타입으로 블랙보드에 기록한다.
		CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
		if (pPlayer)
		{
			StateMachine()->AddBlackboardData(L"TargetObject", BB_DATA::OBJECT, pPlayer);
		}
		//디버그용 확인
		Ptr<CFSM> MonsterFSM = StateMachine()->GetFSM();
		bool originFSM = MonsterFSM->GetOrigin();
		CStateMachine* MonsterSM = MonsterFSM->GetStateMachine();

		if (nullptr != StateMachine()->GetFSM())
		{		
			StateMachine()->GetFSM()->SetState(L"IdleState");
		}
	}
}

void CMonsterScript::tick()
{
	//디버그용 확인
	Ptr<CFSM> MyFSM = StateMachine()->GetFSM();
	bool originFSM = MyFSM->GetOrigin();
	CStateMachine* MySM = MyFSM->GetStateMachine();

	//몬스터도 state은 원본 FSM 가리키는걸 확인
	//pFSM->AddState(L"IdleState", new CIdleState);
	//pFSM->AddState(L"TraceState", new CTraceState);
	CState* MyState = MyFSM->FindState(L"IdleState");
	MyFSM = MyState->GetFSMDebug();
	originFSM = MyFSM->GetOrigin();

	StateMachine()->GetFSM()->ChangeState(L"TraceState");
}

void CMonsterScript::SaveToFile(FILE* _File)
{
}

void CMonsterScript::LoadFromFile(FILE* _File)
{
}

