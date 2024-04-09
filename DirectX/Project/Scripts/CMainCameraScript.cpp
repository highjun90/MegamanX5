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
	
	//�÷��̾��� ��ġ���� �޾Ƽ� ����ī�޶� �÷��̾ ���󰡰� �Ѵ�.
	vPos = MainPlayer->Transform()->GetRelativePos(); 
	vPos.z = 0;   //�̰� �������ϸ� �ʹ� �����̼� ���� �Ⱥ���, �Ƹ� �÷��̾� z���� �� ������?
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
