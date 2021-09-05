// 2020.12.22 Add CDiskDlg — 磁盘清理

#if !defined(AFX_DISKDLG_H__87987066_DBFD_4910_9966_0724F2A745FA__INCLUDED_)
#define AFX_DISKDLG_H__87987066_DBFD_4910_9966_0724F2A745FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma once
#include <afxwin.h>
#include "resource.h"

class CDiskDlg :public CDialog
{
public:
	//------------------------------------------------
	// 成员变量
	enum { IDD = IDD_DISK_DIALOG };
	CStatic	       m_Text2;
	CStatic	       m_Text1;
	CStatic	       m_Text;
	CButton	       m_CheckAll;
	CListCtrl	   m_Grid;
	
	//------------------------------------------------
	// 成员函数
	CDiskDlg(CWnd* pParent = NULL);

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	/*
	* 删除文件夹
	*/
	void DelFolder(CString path);
	/*
	* 根据传入的“索引值”清楚对应位置的内容
	*/ 
	void ClearDisk(int num);

	/*
	* 复选框被选中的响应函数
	*/
	afx_msg void OnCheckll();
	
	/*
	* “清除”按钮响应函数
	*/
	afx_msg void OnButclear();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

};

#endif