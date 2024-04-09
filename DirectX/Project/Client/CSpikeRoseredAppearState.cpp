#include "pch.h"
#include "CSpikeRoseredAppearState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CGameObject.h>
#include <Engine/CStateMachine.h>
#include <Engine/CTransform.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CAnim.h>

CSpikeRoseredAppearState::CSpikeRoseredAppearState()
{
}

CSpikeRoseredAppearState::~CSpikeRoseredAppearState()
{
}

void CSpikeRoseredAppearState::finaltick()
{
	//Owner 받아두기 (spikerosered 오브젝트)
	CGameObject* Owner = GetFSM()->GetStateMachine()->GetOwner();

	if (true == GetFirstAnimPlay())
	{
		Owner->Animator2D()->Play(L"SpikeRosered_Appear");
		SetFirstAnimPlay(false);
	}

	//등장씬

	/*	Vec3 vPos = Owner->Transform()->GetRelativePos();
		CAnim* curAnim = Owner->Animator2D()->GetCurAnim();
		int curFrmIdx = curAnim->GetCurFrmIdx();
		if (curFrmIdx < 15)
		{
			if (curFrmIdx % 2 == 1)
				;
			vPos.y += DT * 300;
		}
		else if (curFrmIdx < 35)
			vPos.y += DT * 200;
		else if (curFrmIdx < 50)
			vPos.y -= DT * 200;
		else if (50 <= curFrmIdx < 50)
		{
			vPos.y -= DT * 300;

			if (vPos.y < -50.f)
				vPos.y = -50.f;
		}

		if (curFrmIdx == 90)
		{
			vPos.y = -50.f;
		}
		Owner->Transform()->SetRelativePos(vPos);*/
	
}

void CSpikeRoseredAppearState::Enter()
{
	//디버그용 코드..
	//CFSM* curFSM = GetFSM();
	//CStateMachine* curStateMachine = curFSM->GetStateMachine();
	//CGameObject* pSelf = curStateMachine->GetOwner();

	SetFirstAnimPlay(true);

}

void CSpikeRoseredAppearState::Exit()
{

}