#pragma once

class CEngine 
	: public CSingleton<CEngine>
{
	SINGLE(CEngine);
private:
	HWND		m_hMainWnd;		// ���� ������ �ڵ�
	Vec2		m_vResolution;	// �ػ� ����

	HDC        hdc;

public:
	HWND GetMainWind() { return m_hMainWnd; }

	void CreateHDC() { hdc = ::GetDC(GetMainWind()); }

private:
	void DebugFunctionCheck();

public:
	int init(HWND _hWnd, Vec2 _vResolution);
	void progress();
};

