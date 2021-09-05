// MainFrm.h: CMainFrame 类的接口
#pragma once
#include "Game.h"

class CMainFrame : public CFrameWnd
{
public: // 仅从序列化创建
	CMainFrame() noexcept;
	virtual ~CMainFrame();
protected:
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:
// 操作
public:
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
 
	// 控件条嵌入成员
	CToolBar m_wndToolBar;
	// 生成的消息映射函数
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	// !!!设置界面框架大小
	int m_iWidth{ 800 };
	int m_iHeight{ 600 };
	// !!!设置游戏核心功能
	enum ETimer { ETimerIdGameLoop = 1 }; // 定时器ID
	// 游戏类
	CGame m_game;

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};