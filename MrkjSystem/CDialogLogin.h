
// Ex0003  股票仿真系统 Wangxiaoyao Add  登录界面头文件 2021.2.8

#pragma once
#include <afxdialogex.h>
#include "resource.h"
#include "CConfig.h" // 配置文件

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

	// 记录信息 到配置文件中
	void RecordInfo();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// 用户名
	CString m_strUsername;
	// 密码
	CString m_strPassword;
	// 是否记住 密码
	BOOL m_bRecordPass;

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

	CConfig m_Config;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

};

