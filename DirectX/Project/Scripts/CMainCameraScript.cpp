#include "pch.h"
#include "CMainCameraScript.h"


CMainCameraScript::CMainCameraScript()
	: CScript(MAINCAMERASCRIPT)
	, followPlayer(true)
{
}

CMainCameraScript::~CMainCameraScript()
{
}

void CMainCameraScript::tick()
{
	Vec3 vPos = {};
	//Vec3 vRot = {};
	
	//플레이어의 위치값을 받아서 메인카메라가 플레이어를 따라가게 한다.
	vPos = MainPlayer->Transform()->GetRelativePos(); 
	vPos.z = 0;   //이거 설정안하면 너무 가까이서 봐서 안보임, 아마 플레이어 z값이 더 가까운듯?
	if (true == GetFollowPlayer())
	{
		Transform()->SetRelativePos(vPos);
	}
	if (vPos.x > 19100)
	{
		vPos.x = 19100;
		vPos.y = 150;
		Transform()->SetRelativePos(vPos);
		SetFollowPlayer(false);
	}

	return;

	/*return;

	Vec3 vPos = Transform()->GetRelativePos();

	Transform()->SetRelativePos(vPos);*/
}

void CMainCameraScript::SaveToFile(FILE* _File)
{
}

void CMainCameraScript::LoadFromFile(FILE* _File)
{
}
