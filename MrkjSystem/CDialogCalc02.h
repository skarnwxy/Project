#pragma once

// Ex0003  ��Ʊ����ϵͳ Wangxiaoyao Add  ����ҳǩ - ���������� - �ǵ�ͣ������ 2021.8.24

// CDialogCalc02 �Ի���
class CDialogCalc02 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCalc02)

public:
	CDialogCalc02(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogCalc02();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCode;
	CString m_strName;
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
