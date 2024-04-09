#include "pch.h"
#include "CDebugScript.h"

#include <Engine/CKeyMgr.h>
#include <Engine/CFontMgr.h>

CDebugScript::CDebugScript()
	: CScript(SCRIPT_TYPE::DEBUGSCRIPT)
{
}

CDebugScript::~CDebugScript()
{
}

void CDebugScript::SaveToFile(FILE* _File)
{
}

void CDebugScript::LoadFromFile(FILE* _File)
{
}



void CDebugScript::tick()
{
	text_playerPos[50] = {};
	swprintf_s(text_playerPos, 50, L"DeltaTime : %f, FPS : %f", 33.f, 44.f);

	CFontMgr::GetInst()->DrawFont(text_playerPos, 10.f, 30.f, 16, FONT_RGBA(30, 255, 255, 255));
}
