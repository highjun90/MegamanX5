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

		// �÷��̾ ã�Ƽ� Object Ÿ������ �����忡 ����Ѵ�.
		CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
		if (pPlayer)
		{
			StateMachine()->AddBlackboardData(L"TargetObject", BB_DATA::OBJECT, pPlayer);
		}
		//����׿� Ȯ��
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
	//����׿� Ȯ��
	Ptr<CFSM> MyFSM = StateMachine()->GetFSM();
	bool originFSM = MyFSM->GetOrigin();
	CStateMachine* MySM = MyFSM->GetStateMachine();

	//���͵� state�� ���� FSM ����Ű�°� Ȯ��
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

