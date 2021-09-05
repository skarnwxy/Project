
// Ex0003  股票仿真系统 Wangxiaoyao Add  股票仿真系统界面 2021.2.20

#include "pch.h"
#include "framework.h"
#include "CMrkjSystemApp.h"

// 股票仿真系统的面板
#include "CMrkjSystemDlg.h"

// 股票仿真系统的面板 —— 工具页签
#include "CDialogScreenShot.h" // 截屏工具
#include "CScreenTools.h" // 截屏工具服务类

#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

////////////////////////////////////////////////
// CMrkjSystemDlg 对话框
CMrkjSystemDlg::CMrkjSystemDlg(CWnd* pParent /*=nullptr*/) : CDialogEx(IDD_MRKJSYSTEM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMrkjSystemDlg::~CMrkjSystemDlg()
{
	//SAFE_DELETE(m_pDlgCalc);
	//SAFE_DELETE(m_pDlgSetting);
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示
HCURSOR CMrkjSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CMrkjSystemDlg::PreTranslateMessage(MSG *pMsg)
{
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMrkjSystemDlg::OnOK()
{
	if (IDOK == AfxMessageBox(_T("退出股票仿真系统"), MB_OKCANCEL)) {
		CDialogEx::OnOK();
	}
}

void CMrkjSystemDlg::OnCancel()
{
	if (IDOK == AfxMessageBox(_T("退出股票仿真系统"), MB_OKCANCEL)) {
		CDialogEx::OnCancel();
	}
}

HBRUSH CMrkjSystemDlg::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd == this) {
		// 生成背景画刷
		return (HBRUSH)m_bkBrush.GetSafeHandle();
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

//-----------------------------工具----------------------------------
// 计算器
void CMrkjSystemDlg::OnMenuCalc()
{
	ShowChange(m_pDlgCalc);
}

void CMrkjSystemDlg::OnMenuScreenShot()
{
	//隐藏自己
	ShowWindow(SW_HIDE);
	// 显示模态对话框
	CDialogScreenShot dlg;
	HBITMAP hBmp = NULL;
	if (IDOK == dlg.DoModal()) {
		// 获取鼠标选中的区域
		CRect rc = dlg.GetSelectRect();
		// 先获得选中区域的图片(以防止被其它弹出窗口遮挡)
		hBmp = CScreenTools::CopyScreenToBitmap(&rc);
		// 弹出一个对话框, 获取保存图片的位置
		static CString strFilename = (CToolServices::GetDir() + _T("\\截图.bmp")).c_str();
		{
			static TCHAR szFilter[] = _T("bmp(*.bmp)|*.bmp|所有文件(*.*)|*.*||");
			CFileDialog dlg(FALSE, // 创建文件打开对话框:FALSE保存对话框　
				_T(".txt"),
				strFilename.GetString(),
				OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
				szFilter
			);
			if (IDOK != dlg.DoModal()) {
				goto __End;
			}
			// 显示选择的文件内容
			strFilename = dlg.GetPathName();
		}
		if (!strFilename.IsEmpty()) {
			//把指定区域保存成图片
			CScreenTools::SaveBitmapToFile(hBmp, strFilename);
		}
	}
__End:
	// 删除位图句柄
	if (hBmp) {
		DeleteObject(hBmp);
	}
	ShowWindow(SW_SHOW);
}

// 系统设置
void CMrkjSystemDlg::OnMenuSetting()
{
	ShowChange(m_pDlgSetting);
}

//-----------------------------帮助----------------------------------
void CMrkjSystemDlg::OnMenuHelp()
{
	std::wstring strDir = CToolServices::GetDir();
	CString path(strDir.c_str());
	PathAppend(path.GetBuffer(1024), _T("help.html"));
	path.ReleaseBuffer();
	ShellExecute(NULL, _T("open"), path.GetString(), NULL, NULL, SW_SHOW);
}

void CMrkjSystemDlg::OnMenuAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}


//////////////////////////////////////////////////////////////////////////
void CMrkjSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMrkjSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	// 系统页签

	// 查询页签

	// 即时数据页签

	// 工具页签
	ON_COMMAND(ID_MENU_CALC, &CMrkjSystemDlg::OnMenuCalc)
	ON_COMMAND(ID_MENU_SCREEN_SHOT, &CMrkjSystemDlg::OnMenuScreenShot)
	ON_COMMAND(ID_MENU_SETTING, &CMrkjSystemDlg::OnMenuSetting)

	// 帮助页签
	ON_COMMAND(ID_MENU_HELP, &CMrkjSystemDlg::OnMenuHelp)
	ON_COMMAND(ID_MENU_ABOUT, &CMrkjSystemDlg::OnMenuAbout)
END_MESSAGE_MAP()


// CMrkjSystemDlg 消息处理程序
BOOL CMrkjSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// (1): 背景画刷
	{
		CBitmap bmp;
		if (bmp.LoadBitmap(IDB_BITMAP_MAINDLG_BACKGROUND)) {
			m_bkBrush.CreatePatternBrush(&bmp);
		}
	}

	// (2): 标题
	{
		CString str;
		str.LoadStringW(IDS_STRING_MAINDLG_TITLE);
		this->SetWindowTextW(str);
	}

	// (3): 菜单
	{
		m_menu.LoadMenu(IDR_MENU_MAIN);
		SetMenu(&m_menu);
#if CHECK_LOGIN
		const CMrkjDatabase::DBEntryUser &user = g_loginUser;
		// 设置主菜单 可用状态
		m_menu.EnableMenuItem(0, (user.p001 == L"1" ? MF_ENABLED : MF_GRAYED) | MF_BYPOSITION);
		m_menu.EnableMenuItem(1, (user.p005 == L"1" ? MF_ENABLED : MF_GRAYED) | MF_BYPOSITION);
		m_menu.EnableMenuItem(2, (user.p006 == L"1" ? MF_ENABLED : MF_GRAYED) | MF_BYPOSITION);
		m_menu.EnableMenuItem(3, (user.p007 == L"1" ? MF_ENABLED : MF_GRAYED) | MF_BYPOSITION);

		// 设置子菜单 可用状态
		m_menu.EnableMenuItem(ID_MENU_DATA_MAINTENANCE, user.p002 == L"1" ? MF_ENABLED : MF_GRAYED);
		m_menu.EnableMenuItem(ID_MENU_DATA_IMPEXP, user.p003 == L"1" ? MF_ENABLED : MF_GRAYED);
		m_menu.EnableMenuItem(ID_MENU_DATA_KIND, user.p004 == L"1" ? MF_ENABLED : MF_GRAYED);

		m_menu.EnableMenuItem(ID_MENU_KIND_SELECT, user.p005 == L"1" ? MF_ENABLED : MF_GRAYED);
		m_menu.EnableMenuItem(ID_MENU_HOSTORY_DATA, user.p005 == L"1" ? MF_ENABLED : MF_GRAYED);
		m_menu.EnableMenuItem(ID_MENU_REALTIME_DATA, user.p006 == L"1" ? MF_ENABLED : MF_GRAYED);

		m_menu.EnableMenuItem(ID_MENU_CALC, user.p008 == L"1" ? MF_ENABLED : MF_GRAYED);
		m_menu.EnableMenuItem(ID_MENU_SCREEN_SHOT, user.p009 == L"1" ? MF_ENABLED : MF_GRAYED);
		m_menu.EnableMenuItem(ID_MENU_SETTING, user.p010 == L"1" ? MF_ENABLED : MF_GRAYED);
#endif
	}

	// (4):  状态栏
	{
		// 加载的字符串资源的ID
		UINT array[] = { IDS_STRING_STATUS_PANETEXT_LOGINUSER
						 , IDS_STRING_STATUS_PANETEXT_LOGINTIME
						 , IDS_STRING_STATUS_PANETEXT_COPYRIGHT
		};
		m_statusBar.Create(this);
		m_statusBar.SetIndicators(array, _countof(array));
		CRect rcCli;
		GetClientRect(rcCli);
		int index = 0;
		// 设置 登陆用户名
		{
			m_statusBar.SetPaneInfo(index, array[index], 0, rcCli.Width() * 1 / _countof(array));
			CString str = m_statusBar.GetPaneText(index) + g_loginUser.username.c_str();
			m_statusBar.SetPaneText(index, str);
			++index;
		}
		// 设置 登陆时间
		{
			CTime t = CTime::GetCurrentTime();
			CString str = m_statusBar.GetPaneText(index);
			str += t.Format(_T("%Y-%m-%d %H:%d:%S"));
			m_statusBar.SetPaneInfo(index, array[index], 0, rcCli.Width() * 1 / _countof(array));
			m_statusBar.SetPaneText(index, str);
			++index;
		}
		// 设置 版权信息
		{
			CString str;
			str.LoadString(IDS_STRING_STATUS_PANETEXT_COPYRIGHT);
			m_statusBar.SetPaneInfo(index, array[index], 0, rcCli.Width() * 1 / _countof(array));
			++index;
		}
		// 设置背景色
		m_statusBar.GetStatusBarCtrl().SetBkColor(RGB(178, 212, 255));
		// 移动到指定的位置
		RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, IDS_STRING_STATUS_PANETEXT_COPYRIGHT);
	}

	// (5)：子对话框
	{
		// 存入数组,便于使用
		m_vDlgPtr.push_back(m_pDlgCalc);
		//m_vDlgPtr.push_back(m_pDlgSetting);

		// 获取对话框位置
		CRect rc;
		{
			GetClientRect(rc);
			CRect rcs;
			m_statusBar.GetWindowRect(rcs);
			rc.bottom -= 1 + rcs.Height();
		}

		// 创建面板
		m_pDlgCalc->Create(IDD_DIALOG_CALC, this);
		//m_pDlgSetting->Create(IDD_DIALOG_SETTING, this);
		//初始时全部不显示
		for each(auto pdlg in m_vDlgPtr) {
			pdlg->MoveWindow(rc);
			pdlg->ShowWindow(SW_HIDE);
		}
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMrkjSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMrkjSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//只显示自己的窗口,其余的隐藏
void CMrkjSystemDlg::ShowChange(CDialogEx *pDlg)
	{
	// 查找当前己经显示的窗口
	for (auto p : m_vDlgPtr) {
		if (p->IsWindowVisible()) {
			m_pDlgLastShow = p;
			break;
		}
	}
	// 更新窗口数据
	{
		//if (pDlg == m_pDlgDataMaintenance) {
		//	m_pDlgDataMaintenance->UpdateKindList();
		//}
		//if (pDlg == m_pDlgHostoryData) {
		//	m_pDlgHostoryData->UpdateStockInfoComboBox();
		//}
		//if (pDlg == m_pDlgRealtimeData) {
		//	m_pDlgRealtimeData->UpdateStockInfoComboBox();
		//}
	}
	// 显示新窗口
	if (pDlg && pDlg->GetSafeHwnd()) {
		pDlg->ShowWindow(SW_SHOW);
	}
	//隐藏其它窗口
	for (auto p : m_vDlgPtr) {
		if (p != pDlg) {
			p->ShowWindow(SW_HIDE);
		}
	}
	m_statusBar.ShowWindow(SW_SHOW);
}