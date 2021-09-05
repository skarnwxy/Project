// 2020.12.27 Add CLitterDlg — 垃圾清理

#if !defined(AFX_LITTERDLG_H__5BE912A3_8112_471F_8D04_082D52D0EE80__INCLUDED_)
#define AFX_LITTERDLG_H__5BE912A3_8112_471F_8D04_082D52D0EE80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma once
#include <afxwin.h>
#include "resource.h"

class CLitterDlg : public CDialog
{
public:
	//------------------------------------------------
	CLitterDlg(CWnd* pParent = NULL);   // standard constructor

	/*
	* 文件删除
	*/
	void FileDelete(CString FilePath);
	/*
	* 删除垃圾文件
	*/
	void DeleteLitterFile();

	//------------------------------------------------
	enum { IDD = IDD_LITTER_DIALOG };
	HANDLE		m_hThread;                // 线程句柄
	CListBox	m_List;
	CComboBox	m_Combo;

protected:
	//------------------------------------------------
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	/*
	* 选择垃圾文件类型的响应函数
	*/
	afx_msg void OnButselect();
	/*
	开始清理清理垃圾文件的响应函数
	*/
	afx_msg void OnButbegin();
	/*
	停止清理垃圾文件的响应函数
	*/
	afx_msg void OnButstop();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif