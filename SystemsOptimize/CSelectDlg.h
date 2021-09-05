// 2020.12.27 Add CSelectDlg — 垃圾文件选择类型

#if !defined(AFX_SELECTDLG_H__4816E93A_D4F5_45C6_9811_73D9310E2066__INCLUDED_)
#define AFX_SELECTDLG_H__4816E93A_D4F5_45C6_9811_73D9310E2066__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#pragma once
#include <afxwin.h>
#include "resource.h"

class CSelectDlg : public CDialog
{
public:
	//------------------------------------------------
	CSelectDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_SELECT_DIALOG };

protected:
	//------------------------------------------------
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	
	//------------------------------------------------
	/*
	* 选择垃圾文件类型确定函数
	*/
	afx_msg void OnButok();
	/*
	* 选择垃圾文件类型取消函数
	*/
	afx_msg void OnButcancel();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif

