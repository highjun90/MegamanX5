#include "pch.h"
#include "CSpikeballGreenScript.h"

#include "CSpikeRoseRedScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include <Engine/CAnim.h>
#include <Engine/CLayer.h>

CSpikeballGreenScript::CSpikeballGreenScript()
	: CScript(SPIKEBALLGREENSCRIPT)
	, Destroyself(false)
{
}

CSpikeballGreenScript::~CSpikeballGreenScript()
{
}

void CSpikeballGreenScript::begin()
{
	Ptr<CTexture> Atlas_SpikeballGreen_Destroy = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\SpikeballGreen_Destroy.png", L"texture\\SpikeballGreen_Destroy.png");
	Animator2D()->Create(L"SpikeballGreen_Destroy", Atlas_SpikeballGreen_Destroy, Vec2(0.f, 0.f), Vec2(256.f, 256.f), Vec2(0.f, 0.f), Vec2(256.f, 256.f), 6, 25);
	Animator2D()->Play(L"SpikeballGreen_Destroy");


	Ptr<CTexture> Atlas_SpikeballGreenRunLeft = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\PSpikeballGreen_RunLeft.png", L"texture\\SpikeballGreen_RunLeft.png");
	Animator2D()->Create(L"SpikeballGreen_RunLeft", Atlas_SpikeballGreenRunLeft, Vec2(0.f, 0.f), Vec2(256.f, 256.f), Vec2(0.f, 0.f), Vec2(256.f, 256.f), 8, 20);
	//Ptr<CTexture> Atlas_ZeroIdleLeft = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Zero_IdleLeft.png", L"texture\\Zero_IdleLeft.png");
	//Animator2D()->Create(L"Zero_IdleLeft", Atlas_ZeroIdleLeft, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(0.f, 0.f), Vec2(50.f, 50.f), 6, 4);
	//Animator2D()->Play(L"Zero_IdleLeft");
}

void CSpikeballGreenScript::tick()
{
	
	// 보스 스크립트 알아내서 그린볼 만드는 bool값 확인
	Vec3 vPos = Transform()->GetRelativePos();
	//CGameObject* MyOwner = GetOwner();
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CGameObject* BossObj = CurLevel->FindObjectByName(L"SpikeRosered");
	CSpikeRoseredScript* BossScript = BossObj->GetScript<CSpikeRoseredScript>();

	if (true == BossScript->GetMakeGreenball())
	{
		Vec3 ballPos = BossObj->Transform()->GetRelativePos();
		ballPos.x = ballPos.x - 80.f;
		Transform()->SetRelativePos(ballPos);
		Animator2D()->Play(L"SpikeballGreen_RunLeft");
		BossScript->SetMakeGreenball(false);
	}



	if (vPos.x > 18750)
	{
		vPos.x -= DT * 700.f;
		Transform()->SetRelativePos(vPos);
		
	}
	/*else if(vPos.x <= 18750 && false == GetDestroyself())
	{
		SetDestroyself(true);
		Animator2D()->Play(L"SpikeballGreen_Destroy");
	}*/
	else
	{
		SetDestroyself(true);
	}

	if (true == GetDestroyself())
	{
		Animator2D()->Play(L"SpikeballGreen_Destroy");
		//SetDestroyself(false);
	}


	/*CAnim* curAnime = Animator2D()->GetCurAnim();
	if (curAnime == Animator2D()->FindAnim(L"SpikeballGreen_Destroy"))
	{
		if (5 == curAnime->GetCurFrmIdx())
		{
			CLayer* DLay = CurLevel->GetLayer(0);
			CGameObject* Owner = GetOwner();
			DLay->AddObject(Owner,false);
		}
	}*/



	int a = 0;

	//CSpikeRoseredScript* BossScript = MyOwner->GetScript<CSpikeRoseredScript>();
	//if (true == BossScript->GetMakeGreenball())
	//{
		//vPos.x += DT * 50.f;
		//Transform()->SetRelativePos(vPos);
	//}



	//if (KEY_TAP(KEY::LEFT))


}

void CSpikeballGreenScript::SaveToFile(FILE* _File)
{
}

void CSpikeballGreenScript::LoadFromFile(FILE* _File)
{
}

