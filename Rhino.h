
// Rhino.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRhinoApp: 
// �йش����ʵ�֣������ Rhino.cpp
//

class CRhinoApp : public CWinApp
{
public:
	CRhinoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRhinoApp theApp;