/** 
  * Copyright (C) 2021 skarn
  * @file     CDialogSetting.h                                                       
  * @brief    股票分析系统系统设置功能的头文件                                                  
  * @author   debugSarn                                                     
  * @date     2021-09-21  
  * @note     
  * @see      
 */
		
#pragma once
#include <afxdialogex.h>

/**
  * @File  CDialogSetting
  * @brief 股票分析系统系统设置功能
 */
class CDialogSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSetting)
public:
	CDialogSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogSetting();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	// 用户列表
	CListCtrl m_lst;
	enum {
		EListIndexID = 0,
		EListIndexUsername,
		EListIndexPassword,
		EListIndexP001,
		EListIndexP002,
		EListIndexP003,
		EListIndexP004,
		EListIndexP005,
		EListIndexP006,
		EListIndexP007,
		EListIndexP008,
		EListIndexP009,
		EListIndexP010,
		EListIndexMaxLimit,
	};

	// 更新m_lst中的数据
	void UpdateListData();
	void UpdateListData(const CMrkjDatabase::VDBEntryUser& v);
	// 获得某行数据
	void GetListData(CMrkjDatabase::DBEntryUser& data, int index);
	// 清理m_lst数据
	void ClearList();
	// 获取选中行
	int GetSelectLineIndex();

	// 编号
	CString m_strID;
	// 用户名
	CString m_strUsername;
	// 密码
	CString m_strPassword;
	// 系统
	CButton m_btn001;
	BOOL m_b001;
	// 基础数据维护
	CButton m_btn002;
	BOOL m_b002;
	// 品种维护
	CButton m_btn003;
	BOOL m_b003;
	// 导入导出数据
	CButton m_btn004;
	BOOL m_b004;
	// 查询
	CButton m_btn005;
	BOOL m_b005;
	// 即时数据
	CButton m_btn006;
	BOOL m_b006;
	// 工具
	CButton m_btn007;
	BOOL m_b007;
	// 金融计算器
	CButton m_btn008;
	BOOL m_b008;
	// 屏幕截图
	CButton m_btn009;
	BOOL m_b009;
	// 系统设置
	CButton m_btn010;
	BOOL m_b010;

public:
	afx_msg void OnLvnItemchangedListData(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckSystem();
	afx_msg void OnBnClickedCheckTools();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnDestroy();

};

