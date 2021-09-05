// 2020.12.27 Add CLitterDlg �� ��������

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
	* �ļ�ɾ��
	*/
	void FileDelete(CString FilePath);
	/*
	* ɾ�������ļ�
	*/
	void DeleteLitterFile();

	//------------------------------------------------
	enum { IDD = IDD_LITTER_DIALOG };
	HANDLE		m_hThread;                // �߳̾��
	CListBox	m_List;
	CComboBox	m_Combo;

protected:
	//------------------------------------------------
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	/*
	* ѡ�������ļ����͵���Ӧ����
	*/
	afx_msg void OnButselect();
	/*
	��ʼ�������������ļ�����Ӧ����
	*/
	afx_msg void OnButbegin();
	/*
	ֹͣ���������ļ�����Ӧ����
	*/
	afx_msg void OnButstop();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif