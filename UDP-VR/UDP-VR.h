
// UDP-VR.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUDPVRApp:
// �йش����ʵ�֣������ UDP-VR.cpp
//

class CUDPVRApp : public CWinApp
{
public:
	CUDPVRApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUDPVRApp theApp;