
// Ex0003  股票仿真系统 Wangxiaoyao Add  股票仿真系统界面 2021.2.20

#pragma once

#include "CDialogCalc.h"
#include "CDialogSetting.h"

class CMrkjSystemDlg : public CDialogEx
{
public:
	CMrkjSystemDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CMrkjSystemDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMRKJSYSTEM_DIALOG };
#endif

	virtual BOOL PreTranslateMessage(MSG *pMsg);
	virtual void OnOK();
	virtual void OnCancel();

	// 画背景 : 更改背景画刷
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);

	//-----------------------------系统----------------------------------


	//-----------------------------查询----------------------------------


	//-----------------------------即时数据------------------------------


	//-----------------------------工具----------------------------------
	// 金融记算器
	afx_msg void OnMenuCalc();
	// 屏幕截图
	afx_msg void OnMenuScreenShot();
	// 系统设置
	afx_msg void OnMenuSetting();

	//-----------------------------帮助----------------------------------
	// 帮助
	afx_msg void OnMenuHelp();
	// 关于本系统
	afx_msg void OnMenuAbout();

protected:
	//////////////////////////////////成员变量//////////////////////////////////////
	HICON m_hIcon;
	// 菜单栏
	CMenu m_menu;
	//状态栏
	CStatusBar m_statusBar;
	// 背景画刷
	CBrush m_bkBrush;

	//////////////////////////////////成员函数//////////////////////////////////////
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

private:

	// 子对话框 : 计算器
	CDialogCalc *m_pDlgCalc{ new CDialogCalc() };
	// 子对话框 : 屏幕截图
	// 没有对话框
	// 子对话框 : 系统设置
	CDialogSetting *m_pDlgSetting{ new CDialogSetting() };

	// 子对话框 : 帮助
	// 没有对话框, 弹出网页
	// 子对话框 : 关于
	// 模态对话框, 不必定义成成员变量

	// 存储所有对话框的指针
	std::vector<CDialogEx *> m_vDlgPtr;
	// 记录当前正在显示的对话框
	CDialogEx *m_pDlgLastShow{ nullptr };

	//////////////////////////////////成员函数//////////////////////////////////////
	//只显示自己的窗口,其余的隐藏,并返回上次显示的窗口
	void ShowChange(CDialogEx *pDlg);
};
