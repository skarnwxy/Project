
// Ex0003  股票仿真系统 Wangxiaoyao Add  股票仿真系统应用窗口头文件 2021.2.8

#pragma once
#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"

class CMrkjSystemApp : public CWinApp
{
public:
	CMrkjSystemApp();

	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
private:
	// 初始化GDI+需要的变量
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_gdiplusToken;
};

extern CMrkjSystemApp theApp;
