// HDCardDevDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// CHDCardDevDemoApp:
// �йش����ʵ�֣������ HDCardDevDemo.cpp
//

class CHDCardDevDemoApp : public CWinApp
{
public:
	CHDCardDevDemoApp();
	
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHDCardDevDemoApp theApp;
