
// Raid_Test.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRaid_TestApp:
// �йش����ʵ�֣������ Raid_Test.cpp
//

class CRaid_TestApp : public CWinApp
{
public:
	CRaid_TestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRaid_TestApp theApp;