// 2020.12.22 Add CDiskDlg �� ��������

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
	// ��Ա����
	enum { IDD = IDD_DISK_DIALOG };
	CStatic	       m_Text2;
	CStatic	       m_Text1;
	CStatic	       m_Text;
	CButton	       m_CheckAll;
	CListCtrl	   m_Grid;
	
	//------------------------------------------------
	// ��Ա����
	CDiskDlg(CWnd* pParent = NULL);

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	/*
	* ɾ���ļ���
	*/
	void DelFolder(CString path);
	/*
	* ���ݴ���ġ�����ֵ�������Ӧλ�õ�����
	*/ 
	void ClearDisk(int num);

	/*
	* ��ѡ��ѡ�е���Ӧ����
	*/
	afx_msg void OnCheckll();
	
	/*
	* ���������ť��Ӧ����
	*/
	afx_msg void OnButclear();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

};

#endif