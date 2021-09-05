// 2020.12.8 Add CSystemsOptimizeApp 实现类

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主符号


// CSystemsApp:
class CSystemsOptimizeApp : public CWinApp
{
public:
	CSystemsOptimizeApp();

	/*
	* 重写
	*/
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CSystemsOptimizeApp theApp;
