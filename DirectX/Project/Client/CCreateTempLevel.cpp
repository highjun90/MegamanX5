#include "pch.h"
#include "CCreateTempLevel.h"


#include <Engine/CCollisionMgr.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include <Scripts/CPlayerScript.h>
#include <Scripts/CBackgroundScript.h>
#include <Scripts/CMainCameraScript.h>
#include <Scripts/CPurpleRoseScript.h>
#include <Scripts/CSpikeRoseredScript.h>
#include <Scripts/CSpikeballGreenScript.h>

#include <Scripts/CDebugScript.h>

#include <Engine/CMesh.h>
#include <Engine/CGraphicsShader.h>
#include <Engine/CTexture.h>
#include <Engine/CSetColorShader.h>

#include "CLevelSaveLoad.h"
#include <Scripts/CMissileScript.h>
#include <Scripts/CMonsterScript.h>

#include <Engine/CAssetMgr.h>
#include <Engine/CPrefab.h>
#include <Engine/CFSM.h>

//배경 마젠타
#include <Engine/CBackgroundMgr.h>

// State
#include "CIdleState.h"
#include "CTraceState.h"

// 보스 state
#include "CSpikeRoseredIdleState.h"
#include "CSpikeRoseredAppearState.h"
#include "CSpikeRoseredWhipState.h"

void CCreateTempLevel::Init()
{
	// Missile Prefab 생성
	/*CGameObject* pObj = nullptr;

	pObj = new CGameObject;
	pObj->SetName(L"Missile");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CMissileScript);

	pObj->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	Ptr<CPrefab> pMissilePrefab = new CPrefab(pObj);
	CAssetMgr::GetInst()->AddAsset<CPrefab>(L"MissilePrefab", pMissilePrefab.Get());
	

	//pMissilePrefab->Save(L"prefab\\missile.pref");
	*/

	// 임시 FSM 객체 에셋 하나 생성하기
	Ptr<CFSM>	pFSM = new CFSM(true);

	pFSM->AddState(L"IdleState", new CIdleState);
	pFSM->AddState(L"TraceState", new CTraceState);

	CAssetMgr::GetInst()->AddAsset<CFSM>(L"NormalMonsterFSM", pFSM.Get());


	//보스 상태머신
	Ptr<CFSM>	Spikerosered = new CFSM(true);
	Spikerosered->AddState(L"SpikeRoseredIdleState", new CSpikeRoseredIdleState);
	Spikerosered->AddState(L"SpikeRoseredAppearState", new CSpikeRoseredAppearState);
	Spikerosered->AddState(L"SpikeRoseredWhipState", new CSpikeroseredWhipState);

	CAssetMgr::GetInst()->AddAsset<CFSM>(L"SpikeRoseredFSM", Spikerosered.Get());

	int a = 0;
}

void CCreateTempLevel::CreateTempLevel()
{		
	/*Ptr<CMaterial> pBackgroudMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMtrl");
	Ptr<CMaterial> pStd2DMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl");

	pBackgroudMtrl->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Background.jpg", L"texture\\Background.jpg"));
	pStd2DMtrl->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Fighter.bmp", L"texture\\Fighter.bmp"));*/

	/*CLevel* pLevel = CLevelSaveLoad::LoadLevel(L"level\\temp.lv");
	CLevelMgr::GetInst()->ChangeLevel(pLevel, LEVEL_STATE::STOP);
	return;*/


	CLevel* pTempLevel = new CLevel;

	pTempLevel->GetLayer(0)->SetName(L"Default");
	pTempLevel->GetLayer(1)->SetName(L"Background");
	pTempLevel->GetLayer(2)->SetName(L"BackgroundMagenta");
	pTempLevel->GetLayer(3)->SetName(L"Tile");
	pTempLevel->GetLayer(4)->SetName(L"Player");
	pTempLevel->GetLayer(5)->SetName(L"Monster");
	pTempLevel->GetLayer(6)->SetName(L"Light");
	pTempLevel->GetLayer(7)->SetName(L"Tile");
	pTempLevel->GetLayer(31)->SetName(L"UI");

	// ComputeShader 테스트
	// 사용할 텍스쳐 생성
	Ptr<CTexture> pTestTex = CAssetMgr::GetInst()->CreateTexture(L"TestTex"
		, 1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM
		, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);

	Ptr<CSetColorShader> pCS = (CSetColorShader*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"SetColorShader").Get();
	pCS->SetColor(Vec3(1.f, 0.f, 0.f));
	pCS->SetTargetTexture(pTestTex);
	pCS->Execute();

	tPixel* pPixel = pTestTex->GetPixels();
	tPixel pixel = pPixel[pTestTex->GetWidth() * 1 + 5];

	// Main Camera Object 생성
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CMainCameraScript);

	pCamObj->Transform()->SetRelativePos(Vec3(0.0f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pCamObj->Camera()->SetCameraPriority(0);
	pCamObj->Camera()->LayerCheckAll();
	pCamObj->Camera()->LayerCheck(31, false);

	pTempLevel->AddObject(pCamObj, 0);

	//메인카메라 포인터 임시저장 why -> 메인플레이어와 백그라운드 포인터를 메인카메라스크립트에 저장시켜두려고. 두 정보가 있어야 원하는 카메라 통제가 가능.
	CGameObject* MainCamera = pCamObj;

	// UI 카메라 생성
	pCamObj = new CGameObject;
	pCamObj->SetName(L"UICamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);

	pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 32.f-31.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	pCamObj->Camera()->SetCameraPriority(1);
	pCamObj->Camera()->LayerCheck(31, true);

	pTempLevel->AddObject(pCamObj, 0);

	// 전역 광원 추가
	CGameObject* pLight = new CGameObject;
	pLight->SetName(L"Directional Light");
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetAmbient(Vec3(0.8f, 0.8f, 0.8f));
	pTempLevel->AddObject(pLight, L"Light");


	CGameObject* pObj = nullptr;

	// Backgruond Object 생성
	pObj = new CGameObject;
	pObj->SetName(L"BackGround");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CBackgroundScript);

	pObj->Transform()->SetRelativePos(Vec3(9400.f, 1015.f, 32.f-1.f));
	pObj->Transform()->SetRelativeScale(Vec3(6764.f * 3.f , 935.f *3.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMtrl"));

	Ptr<CTexture> pTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BackGroundImage.png", L"texture\\BackGroundImage.png");
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

	pTempLevel->AddObject(pObj, L"Background", false);

	//메인카메라에 백그라운드 정보(포인터)를 넘겨줌
	CMainCameraScript* MainCameraScript = MainCamera->GetScript<CMainCameraScript>();
	MainCameraScript->SetBackGround(pObj);


	// BackgruondMagenta Object 생성
	pObj = new CGameObject;
	pObj->SetName(L"BackGroundMagenta");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CBackgroundScript);

	pObj->Transform()->SetRelativePos(Vec3(9400.f, 1015.f, 32.f - 2.f));
	pObj->Transform()->SetRelativeScale(Vec3(6764.f * 3.f, 935.f * 3.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMagentaMtrl"));

	pTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BackGround_Magenta.bmp", L"texture\\BackGround_Magenta.bmp");
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

	pTempLevel->AddObject(pObj, L"BackgroundMagenta", false);

	//메인카메라에 백그라운드마젠타 정보(포인터)를 넘겨줌
	MainCameraScript->SetBackGroundMagenta(pObj);


	// Player Object 생성
	pObj = new CGameObject;
	pObj->SetName(L"Player");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerScript);
	pObj->AddComponent(new CMissileScript);

	pObj->Transform()->SetRelativePos(Vec3(6000.f, 2100.f, 32.f-3.f));
	pObj->Transform()->SetRelativeScale(Vec3(160.f, 160.f, 1.f));

	pObj->Collider2D()->SetAbsolute(true);
	pObj->Collider2D()->SetOffsetScale(Vec2(100.f, 100.f));
	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Zero_IdleRight_oneFrame.png", L"texture\\Zero_IdleRight_oneFrame.png"));

	pTempLevel->AddObject(pObj, L"Player", false);

	//메인카메라에 플레이어 정보(포인터)를 넘겨줌
	MainCameraScript->SetMainPlayer(pObj);

	pObj->Animator2D()->Play(L"Zero_IdleRight");

	//배경매니저에 플레이어 포인터 넘겨줌
	CBackgroundMgr::GetInst()->GetPlayer(pObj);


	//Monster Object 생성
	pObj = new CGameObject;
	pObj->SetName(L"Monster");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CStateMachine);
	pObj->AddComponent(new CMonsterScript);

	pObj->Transform()->SetRelativePos(Vec3(500.f, 0.f, 32.f - 4.f));
	pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	pObj->Collider2D()->SetAbsolute(true);
	pObj->Collider2D()->SetOffsetScale(Vec2(120.f, 120.f));
	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Fighter.bmp", L"texture\\Fighter.bmp"));

	pObj->StateMachine()->SetFSM(CAssetMgr::GetInst()->FindAsset<CFSM>(L"NormalMonsterFSM"));



	pTempLevel->AddObject(pObj, L"Monster", false);

	// PurpleRose Object 생성
	pObj = new CGameObject;
	pObj->SetName(L"PurpleRose_0");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CStateMachine);
	pObj->AddComponent(new CPurpleRoseScript);

	//testpos : Vec3(5800.f, 2080.f, 32.f - 4.f)
	pObj->Transform()->SetRelativePos(Vec3(5800.f, 2080.f, 32.f - 4.f));
	pObj->Transform()->SetRelativeScale(Vec3(700.f, 700.f, 1.f));

	pObj->Collider2D()->SetAbsolute(true);
	pObj->Collider2D()->SetOffsetScale(Vec2(300.f, 300.f));
	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	//pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Fighter.bmp", L"texture\\Fighter.bmp"));

	//pObj->StateMachine()->SetFSM(CAssetMgr::GetInst()->FindAsset<CFSM>(L"NormalMonsterFSM"));

	pTempLevel->AddObject(pObj, L"Monster", false);


	// SpikeRosered Object 생성
	pObj = new CGameObject;
	pObj->SetName(L"SpikeRosered");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CStateMachine);
	pObj->AddComponent(new CSpikeRoseredScript);

	//testpos 19400,-50
	pObj->Transform()->SetRelativePos(Vec3(19400.f, -50.f, 32.f - 4.f));
	pObj->Transform()->SetRelativeScale(Vec3(370.f, 370.f, 1.f));

	pObj->Collider2D()->SetAbsolute(true);
	pObj->Collider2D()->SetOffsetScale(Vec2(300.f, 300.f));
	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	pObj->StateMachine()->SetFSM(CAssetMgr::GetInst()->FindAsset<CFSM>(L"SpikeRoseredFSM"));

	//디버그 제발 FSM좀 찾아줘
	/*Ptr<CFSM> FindFromAssetMgrFSM = CAssetMgr::GetInst()->FindAsset<CFSM>(L"SpikeRoseredFSM");
	Ptr<CFSM> FindFrompObjFSM = pObj->StateMachine()->GetFSM();
	int findFSM = 0;*/
	//Ptr<CFSM> TestBossFSM = pObj->StateMachine()->GetFSM();
	int a = 0;


	pTempLevel->AddObject(pObj, L"Monster", false);

    // Greenball Object 생성
	//CGameObject* pObj = new CGameObject;
	pObj = new CGameObject;
	pObj->SetName(L"SpikeballGreen");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CSpikeballGreenScript);
	//pObj->AddComponent(new CStateMachine);

	pObj->Transform()->SetRelativePos(Vec3(19200.f, -50.f, 32.f - 4.f));
	pObj->Transform()->SetRelativeScale(Vec3(700.f, 700.f, 1.f));

	pObj->Collider2D()->SetAbsolute(true);
	pObj->Collider2D()->SetOffsetScale(Vec2(90.f, 90.f));
	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	pTempLevel->AddObject(pObj, L"Monster", false);

	
		

	// 디버그용 Object 생성
	pObj = new CGameObject;
	pObj->SetName(L"DebugObject");
	pObj->AddComponent(new CDebugScript);

	pTempLevel->AddObject(pObj, L"Default", false);

	// 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(4, 5);

	wstring pLayer1(L"Player");

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	//CLayer* pLeftLayer = pCurLevel->GetLayer(L"Player");

	//CCollisionMgr::GetInst()->LayerCheck(L"player", L"Monster");
	//CCollisionMgr::GetInst()->LayerCheck(4, 4);

	CLevelMgr::GetInst()->ChangeLevel(pTempLevel, LEVEL_STATE::STOP);

	CLevelSaveLoad::SaveLevel(pTempLevel, L"level\\temp.lv");	



	//LayerCheck(pLeftLayer->GetLayerIdx(), pRightLayer->GetLayerIdx());
}