#include "pch.h"
#include "CScriptMgr.h"

#include "CBackgroundScript.h"
#include "CDebugScript.h"
#include "CMainCameraScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CPlayerScript.h"
#include "CPurpleRoseScript.h"
#include "CSpikeballGreen.h"
#include "CSpikeballGreenScript.h"
#include "CSpikeRoseredScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBackgroundScript");
	_vec.push_back(L"CDebugScript");
	_vec.push_back(L"CMainCameraScript");
	_vec.push_back(L"CMathScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CPurpleRoseScript");
	_vec.push_back(L"CSpikeballGreen");
	_vec.push_back(L"CSpikeballGreenScript");
	_vec.push_back(L"CSpikeRoseredScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBackgroundScript" == _strScriptName)
		return new CBackgroundScript;
	if (L"CDebugScript" == _strScriptName)
		return new CDebugScript;
	if (L"CMainCameraScript" == _strScriptName)
		return new CMainCameraScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CPurpleRoseScript" == _strScriptName)
		return new CPurpleRoseScript;
	if (L"CSpikeballGreenScript" == _strScriptName)
		return new CSpikeballGreenScript;
	if (L"CSpikeRoseredScript" == _strScriptName)
		return new CSpikeRoseredScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return new CBackgroundScript;
		break;
	case (UINT)SCRIPT_TYPE::DEBUGSCRIPT:
		return new CDebugScript;
		break;
	case (UINT)SCRIPT_TYPE::MAINCAMERASCRIPT:
		return new CMainCameraScript;
		break;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::PURPLEROSESCRIPT:
		return new CPurpleRoseScript;
		break;
		break;
	case (UINT)SCRIPT_TYPE::SPIKEBALLGREENSCRIPT:
		return new CSpikeballGreenScript;
		break;
	case (UINT)SCRIPT_TYPE::SPIKEROSEREDSCRIPT:
		return new CSpikeRoseredScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return L"CBackgroundScript";
		break;

	case SCRIPT_TYPE::DEBUGSCRIPT:
		return L"CDebugScript";
		break;

	case SCRIPT_TYPE::MAINCAMERASCRIPT:
		return L"CMainCameraScript";
		break;

	case SCRIPT_TYPE::MATHSCRIPT:
		return L"CMathScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::PURPLEROSESCRIPT:
		return L"CPurpleRoseScript";
		break;

	case SCRIPT_TYPE::SPIKEBALLGREEN:
		return L"CSpikeballGreen";
		break;

	case SCRIPT_TYPE::SPIKEBALLGREENSCRIPT:
		return L"CSpikeballGreenScript";
		break;

	case SCRIPT_TYPE::SPIKEROSEREDSCRIPT:
		return L"CSpikeRoseredScript";
		break;

	}
	return nullptr;
}