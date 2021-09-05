// Tank.h: Tank 应用程序的主头文件
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // 主符号
class CTankApp : public CWinApp
{
public:
	CTankApp() noexcept;

	virtual BOOL InitInstance();
	virtual int ExitInstance();

	afx_msg void OnAppAbout();

	DECLARE_MESSAGE_MAP()

private:
	// 引入GDIPlus所需要的变量
	ULONG_PTR m_tokenGdiplus;
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartupOutput output;
};

extern CTankApp theApp;
