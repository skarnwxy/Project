
// Ex0003  ��Ʊ����ϵͳ Wangxiaoyao Add  ��¼����ͷ�ļ� 2021.2.8

#pragma once
#include <afxdialogex.h>
#include "resource.h"
#include "CConfig.h" // �����ļ�

class CDialogLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogLogin)

public:
	CDialogLogin(CWnd* pParent = NULL);
	virtual ~CDialogLogin();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedCheckRecord();

	// ��¼��Ϣ �������ļ���
	void RecordInfo();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// �û���
	CString m_strUsername;
	// ����
	CString m_strPassword;
	// �Ƿ��ס ����
	BOOL m_bRecordPass;

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

	CConfig m_Config;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

};

