#include "pch.h"
#include "CSpikeRoseredIdleState.h"

#include <Engine/CGameObject.h>
#include <Engine/CStateMachine.h>
#include <Engine/CTransform.h>
#include <Engine/CAnimator2D.h>

CSpikeRoseredIdleState::CSpikeRoseredIdleState()
{
}

CSpikeRoseredIdleState::~CSpikeRoseredIdleState()
{
}

void CSpikeRoseredIdleState::finaltick()
{
	//디버그용 코드
	Ptr<CFSM> MyFSM = GetFSM();
	bool originFSM = MyFSM->GetOrigin();
	CStateMachine* MySM = MyFSM->GetStateMachine();
	//

	if (true == GetFirstAnimPlay() )
	{
		GetFSM()->GetStateMachine()->GetOwner()->Animator2D()->Play(L"Spikerosered_IdleLeft");
		SetFirstAnimPlay(false);
	}


}

void CSpikeRoseredIdleState::Enter()
{
	//디버그용 코드
	Ptr<CFSM> MyFSM = GetFSM();
	bool originFSM = MyFSM->GetOrigin();
	CStateMachine* MySM = MyFSM->GetStateMachine();
	//

	SetFirstAnimPlay(true);

}

void CSpikeRoseredIdleState::Exit()
{
	//OffAnimPlay();
}