
// LunaStudio.h : LunaStudio Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CLunaStudioApp:
// �йش����ʵ�֣������ LunaStudio.cpp
//

class CLunaStudioApp : public CWinApp
{
public:
	CLunaStudioApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLunaStudioApp theApp;
