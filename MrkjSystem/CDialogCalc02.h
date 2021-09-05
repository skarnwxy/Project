#pragma once

// Ex0003  股票仿真系统 Wangxiaoyao Add  工具页签 - 计算器功能 - 涨跌停计算器 2021.8.24

// CDialogCalc02 对话框
class CDialogCalc02 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCalc02)

public:
	CDialogCalc02(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogCalc02();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
