// MainFrm.cpp: CMainFrame 类的实现
#include "pch.h"
#include "framework.h"
#include "Tank.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// !!!
#define GAME_WIN_W (800)
#define GAME_WIN_H (600)

// CMainFrame
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

// 建立消息映射
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER() // !!!使窗口响应定时器消息
	ON_WM_MOUSEMOVE() // !!!鼠标移动事件
	ON_WM_LBUTTONUP() // !!!鼠标抬起事件
END_MESSAGE_MAP()

// CMainFrame 构造/析构
CMainFrame::CMainFrame() noexcept
{
	// !!!
#define MY_STYLE (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | FWS_ADDTOTITLE)

	// !!!创建窗口
	Create(NULL, _T("坦克动荡大战"), MY_STYLE, CRect(0, 0,GAME_WIN_W, GAME_WIN_H));

	// !!!设置客户区大小
	{
		CRect rcCli;
		GetClientRect(rcCli);

		RECT rcFrame = {
			0, 0,
			m_iWidth + m_iWidth - rcCli.right,
			m_iHeight + m_iHeight - rcCli.bottom
		};
		MoveWindow(&rcFrame, TRUE);	// 调用WindowsAPI设置窗口大小
	}
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1) {
		return -1;
	}

	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("未能创建工具栏\n");
	//	return -1;      // 未能创建
	//}

	//// TODO: 如果不需要可停靠工具栏，则删除这三行
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

	// !!!
	SetTimer(ETimerIdGameLoop, 0, NULL);
	m_game.SetHandle(GetSafeHwnd());

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MAXIMIZEBOX | WS_SYSMENU;

	return TRUE;
}

// CMainFrame 诊断
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

// CMainFrame 消息处理程序
void CMainFrame::OnTimer(UINT_PTR nIDEvent) {
	switch (nIDEvent) {
		case ETimerIdGameLoop: {
			static DWORD dwLastUpdate = GetTickCount(); // 记录本次时刻
			if (GetTickCount() - dwLastUpdate >= 20) {
				m_game.EnterFrame(GetTickCount()); // !!!进入游戏帧处理
				dwLastUpdate = GetTickCount(); // 记录时间间隔
			}
			break;
		}
		default:
			break;
	}

	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point) {
	m_game.OnMouseMove(nFlags, point);
	
	CFrameWnd::OnMouseMove(nFlags, point);
}
void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point) {
	m_game.OnLButtonUp(nFlags, point);
	
	CFrameWnd::OnLButtonUp(nFlags, point);
}
