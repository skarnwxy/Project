// 2020.12.8 Add CSystemsOptimizeDlg 实现类

#pragma once
#include <afxwin.h>
#include "resource.h" // 主符号
#include "CContralDlg.h"
#include "CDiskDlg.h"
#include "CLitterDlg.h"
#include "CTaskDlg.h"

#if !defined(AFX_SYSOPTIMIZEDLG_H__368DD37B_D0F5_4840_935F_3A3889E04035__INCLUDED_)
#define AFX_SYSOPTIMIZEDLG_H__368DD37B_D0F5_4840_935F_3A3889E04035__INCLUDED_

// 宏定义
#define fTitle          1  // 标题
#define fMinButton      2  // 最小化按钮
#define fCloseButton    4  // 关闭按钮
#define fAll            7  // 所有标识

//#define IDR_MAINFRAME 128
//#define IDC_STATICSELECT 1040
//#define IDC_FRAME 1000

// 按钮状态
enum CButtonState { bsNone, bsMin, bsClose };

// CSystemsOptimizeDlg 对话框
class CSystemsOptimizeDlg : public CDialog
{
public:
	//------------------------------------------------
	// 成员函数
	/*
	* 构造函数
	*/
	CSystemsOptimizeDlg(CWnd* pParent = nullptr);

	/*
	* 初始化面板
	* 备注1：对对话框进行初始化
	*/
	virtual BOOL OnInitDialog();
	/*
	* 消息处理程序
	* 备注1：对话框的系统菜单命令（例，最大化等），实际上就是对话框发送WM_SYSCOMMAND消息
	*/
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	/*
	* 如果向对话框添加最小化按钮，则需要下面的代码来绘制该图标
	* 备注1：WM_PAINT是窗口每次重绘都会产生的一个消息，OnPaint是对这个消息的响应函数
	* 备注2：OnPaint()是CWnd的类成员，负责响应WM_PAINT消息。OnDraw()是CVIEW的成员函数
	*/
	afx_msg void OnPaint();
	
	/*
	* 当用户拖动最小化窗口时系统调用此函数取得光标显示
	*/
	afx_msg HCURSOR OnQueryDragIcon();

	/*
	* 关闭窗口
	*/
	afx_msg void OnClose();

	/*
	* 数据动态绑定
	* 备注1：框架通过调用此函数改些与确认对话框数据
	* 备注2：数据动态绑定技术 — 对按钮添加变量时，添加型的变量就需要用到DoDataExchange函数
	* 备注3：在构造函数中初始化变量时，再用DoDataExchange函数，将它板顶到动态按钮中
	*/
	virtual void DoDataExchange(CDataExchange* pDX);

	//----------------------------------------------
	/*
	* 控制面板
	*/
	afx_msg void OnStaContral();
	/*
	* 磁盘空间整理
	*/
	afx_msg void OnStaDisk();
	/*
	* 垃圾清理
	*/
	afx_msg void OnStaLitter();
	/*
	* 系统任务
	*/
	afx_msg void OnStaTask();

	//----------------------------------------------
	/*
	* 析构面板
	*/
	void DestroyWindowBox(int num);
	/*
	* 点击不同的菜单项(例，控制面板等)，创建子面板
	*/
	void CreateDialogBox(int num);
	/*
	* 绘制窗体标题
	*/
	void DrawCaption();
	/*
	* 绘制标题栏和按钮
	*/
	void DrawDialog(UINT Flags);
	/*
	* 控件窗口函数，其画刷句柄效果由提示信息函数构成
	*/
	HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);

	//----------------------------------------------
	/*
	* 当光标在非工作区中移动时，调用该函数 
	* 备注1：带边框的对话框，边框就是非工作区，其余部分则为工作区
	* 备注2：通过GetClientRect方法则得到工作区的大小
	*/
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	/*
	* 鼠标在非工作区右键的单击响应函数
	* 备注1：OnLButtonDown是鼠标右键的响应函数
	*/
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);

	/*
	* 非工作区激活的消息
	*/
	afx_msg BOOL OnNcActivate(BOOL bActive);

	/*
	* 鼠标在当前对象上移动时的响应函数
	* 备注1：当鼠标移过当前对象时的响应函数
	*/
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
	/*
	* 非工作区绘制响应函数
	*/
	afx_msg void OnNcPaint();
	/*
	* 在移动窗口的时候用
	*/
	afx_msg void OnMove(int x, int y);
	
	DECLARE_MESSAGE_MAP() // 声明消息函数
	//-----------------------------------------------	
	// 成员变量

	// 对话框数据
//#ifdef AFX_DESIGN_TIME
//	enum { IDD = IDD_SYSTEMSOPTIMIZE_DIALOG };
//#endif
	enum { IDD = IDD_SYSTEMSOPTIMIZE_DIALOG };
	
	int                   m_Num;
	
	HICON                 m_hIcon;
	CStatic               m_Select;
	CStatic               m_Frame;

	CString               m_Caption;              // 窗体标题
	CButtonState          m_ButtonState;          // 按钮状态
	int                   m_CaptionHeight;        // 标题栏的高度
	int                   m_TitleDrawHeight;      // 标题栏实际的绘制高度
	int                   m_ButtonWidth;          // 按钮位图宽度
	int                   m_ButtonHeight;         // 按钮高度
	int                   m_BorderWidth;          // 边框宽度
	int                   m_BorderHeight;         // 边框高度
	COLORREF              m_CapitonColor;         // 标题字体颜色
	CFont                 m_CaptionFont;          // 标题字体
	BOOL                  m_IsDrawForm;           // 是否重绘按钮
	CRect                 m_TitleRc;              // 标题栏区域
	CRect                 m_MinRect;              // 最小化按钮区域
	CRect                 m_CloseRect;            // 关闭按钮区域

	CBitmap               m_BKGround;

	CContralDlg          *m_pContralDlg;          // 控制面板操作模块
	CDiskDlg             *m_pDiskDlg;             // 磁盘空间整理模块
	CLitterDlg           *m_pLitterDlg;           // 垃圾文件清理模块
	CTaskDlg             *m_pTaskDlg;             // 系统任务管理模块
};

#endif
