// 2020.12.10 Add CContralDlg实现类

#include "pch.h"
#include "CContralDlg.h"

#include <afxwin.h>
//#include "stdafx.h"
#include <Windows.h>
#include "gdiplusbitmap.h"
#include <winapifamily.h>

// CContralDlg 对话框
//IMPLEMENT_DYNAMIC(CContralDlg, CDialog)

CContralDlg::CContralDlg(CWnd* pParent /*=nullptr*/): CDialog(CContralDlg::IDD, pParent)
{
	//---------------------------------------------------------
	// 测试：bmp——>png
	//CString str = _T("F:\\Temp\\12.20.bmp");
	//HBITMAP hBitmap = (HBITMAP)::LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//BITMAP bm;
	//::GetObject(hBitmap, sizeof(bm), &bm);

	//CImage  Img;
	//Img.Attach(hBitmap/**pBitmap*/);

	//CString StringPath1 = _T("F:\\Temp\\12.21.png");
	//Img.Save(StringPath1, Gdiplus::ImageFormatPNG);

	//CString StringPath2 = _T("F:\\Temp\\12.21.jpeg");
	//Img.Save(StringPath2, Gdiplus::ImageFormatJPEG);

	//CString StringPath3 = _T("F:\\Temp\\12.21.bmp");
	//Img.Save(StringPath3, Gdiplus::ImageFormatBMP);
}

CContralDlg::~CContralDlg()
{

}

void CContralDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CContralDlg)
	DDX_Control(pDX, IDC_BUTCOMPUTER, m_Computer);
	DDX_Control(pDX, IDC_BUTTIMEDATE, m_Timedate);
	DDX_Control(pDX, IDC_BUTSYSDM, m_Sysdm);
	DDX_Control(pDX, IDC_BUTMOUSE, m_Mouse);
	DDX_Control(pDX, IDC_BUTMMSYS, m_Mmsys);
	DDX_Control(pDX, IDC_BUTKEYBOARD, m_Keyboard);
	DDX_Control(pDX, IDC_BUTINTL, m_Intl);
	DDX_Control(pDX, IDC_BUTHDWWIZ, m_Hdwwiz);
	DDX_Control(pDX, IDC_BUTDESK, m_Desk);
	DDX_Control(pDX, IDC_BUTAPPWIZ, m_Appwiz);
	DDX_Control(pDX, IDC_BUTACCESS, m_Access);
	DDX_Control(pDX, IDC_BUTINTERNET, m_Internet);
}

BEGIN_MESSAGE_MAP(CContralDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTINTERNET, OnButinternet)
	ON_BN_CLICKED(IDC_BUTMMSYS, OnButmmsys)
	ON_BN_CLICKED(IDC_BUTTIMEDATE, OnButtimedate)
	ON_BN_CLICKED(IDC_BUTDESK, OnButdesk)
	ON_BN_CLICKED(IDC_BUTACCESS, OnButaccess)
	ON_BN_CLICKED(IDC_BUTMOUSE, OnButmouse)
	ON_BN_CLICKED(IDC_BUTKEYBOARD, OnButkeyboard)
	ON_BN_CLICKED(IDC_BUTINTL, OnButintl)
	ON_BN_CLICKED(IDC_BUTAPPWIZ, OnButappwiz)
	ON_BN_CLICKED(IDC_BUTHDWWIZ, OnButhdwwiz)
	ON_BN_CLICKED(IDC_BUTSYSDM, OnButsysdm)
	ON_BN_CLICKED(IDC_BUTMODEM, OnButmodem)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CContralDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_Internet.SetImageIndex(0);            // Internet选项按钮显示图标
	m_Mmsys.SetImageIndex(1);               // 声音按钮显示图标
	m_Timedate.SetImageIndex(2);            // 时间和日期按钮显示图标
	m_Desk.SetImageIndex(3);                // 显示按钮显示图标
	m_Access.SetImageIndex(4);              // 辅助选项按钮显示图标
	m_Mouse.SetImageIndex(5);               // 鼠标按钮显示图标
	m_Keyboard.SetImageIndex(6);            // 键盘按钮显示图标
	m_Intl.SetImageIndex(7);                // 区域按钮显示图标
	m_Appwiz.SetImageIndex(8);              // 添加/删除程序按钮显示图标
	m_Hdwwiz.SetImageIndex(9);              // 添加硬件按钮显示图标
	m_Sysdm.SetImageIndex(10);              // 系统按钮显示图标
	m_Computer.SetImageIndex(11);           // 计算机管理按钮显示图标

	return TRUE;
}

// Internet选项按钮
void CContralDlg::OnButinternet()
{
	//::ShellExecute(NULL, "OPEN", "rundll32.exe",
	//	"shell32.dll Control_RunDLL inetcpl.cpl", NULL, SW_SHOW);

	//LPCWSTR open = _T("OPEN");
	//LPCWSTR rund = _TEXT("rundll32.exe");
	//LPCWSTR shell = _TEXT("shell32.dll Control_RunDLL inetcpl.cpl");

	::ShellExecute(NULL, _T("OPEN"), _T("rundll32.exe"), _T("shell32.dll Control_RunDLL inetcpl.cpl"), NULL, SW_SHOW);
}
// 声音按钮
void CContralDlg::OnButmmsys()
{
	::ShellExecute(NULL, "OPEN", "rundll32.exe",
		"shell32.dll Control_RunDLL mmsys.cpl @1", NULL, SW_SHOW);
}
// 时间和日期按钮
void CContralDlg::OnButtimedate()
{
	// 启动日期和时间设置
	::ShellExecute(NULL, "OPEN", "rundll32.exe",
		"shell32.dll Control_RunDLL timedate.cpl", NULL, SW_SHOW);
}
// 显示按钮
void CContralDlg::OnButdesk()
{
	::ShellExecute(NULL, "OPEN", "rundll32.exe",
		"shell32.dll Control_RunDLL desk.cpl", NULL, SW_SHOW);
}
// 辅助选项按钮
void CContralDlg::OnButaccess()
{
	::ShellExecute(NULL, "OPEN", "rundll32.exe",
		"shell32.dll Control_RunDLL access.cpl", NULL, SW_SHOW);
}
// 鼠标按钮
void CContralDlg::OnButmouse()
{
	::ShellExecute(NULL, "OPEN", "rundll32.exe",
		"shell32.dll Control_RunDLL main.cpl @0", NULL, SW_SHOW);
}
// 键盘按钮
void CContralDlg::OnButkeyboard()
{
	// 启动键盘设置
	::ShellExecute(NULL, "OPEN", "rundll32.exe",
		"shell32.dll Control_RunDLL main.cpl @1", NULL, SW_SHOW);
}
// 区域按钮
void CContralDlg::OnButintl()
{
	::ShellExecute(NULL, "OPEN", "rundll32.exe",
		"shell32.dll Control_RunDLL intl.cpl", NULL, SW_SHOW);
}
// 添加/删除程序按钮
void CContralDlg::OnButappwiz()
{
	::ShellExecute(NULL, "OPEN", "rundll32.exe",
		"shell32.dll Control_RunDLL appwiz.cpl", NULL, SW_SHOW);
}
// 添加硬件按钮
void CContralDlg::OnButhdwwiz()
{
	::ShellExecute(NULL, "OPEN", "rundll32.exe",
		"shell32.dll Control_RunDLL hdwwiz.cpl", NULL, SW_SHOW);
}
// 系统按钮
void CContralDlg::OnButsysdm()
{
	::ShellExecute(NULL, "OPEN", "rundll32.exe",
		"shell32.dll Control_RunDLL sysdm.cpl", NULL, SW_SHOW);
}
// 计算机管理按钮
void CContralDlg::OnButmodem()
{
	::ShellExecute(NULL, "OPEN", "compmgmt.msc",
		"shell32.dll Control_RunDLL compmgmt.cpl", NULL, SW_SHOW);
}

HBRUSH CContralDlg::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	CBitmap m_BKGround;
	m_BKGround.LoadBitmap(IDB_BITBLANK);
	if (nCtlColor == CTLCOLOR_DLG) {
		// 定义一个位图画刷
		CBrush m_Brush(&m_BKGround);
		CRect rect;
		GetClientRect(rect);
		// 选中画刷
		pDC->SelectObject(&m_Brush);
		// 填充客户区域
		pDC->FillRect(rect, &m_Brush);
		return m_Brush;
	}
	else {
		hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	return hbr;
}

void CContralDlg::OnBnClickedBtnSave()
{
	//CBitmap* pBitmap = CBitmap::FromHandle(CopyScreenToBitmap(&m_RectTracker.m_rect, TRUE));
	//Bitmap* pBitmap = new Bitmap(130, 110, PixelFormat24bppRGB);
	//HBITMAP hBitmap;
	//BITMAP bm;
	//pBitmap->GetHBITMAP(NULL, &hBitmap);
	//CBitmap* bmp;
	//bmp.Attach(hBitmap);

	CString str = _T("F:\\Temp\\12.21.bmp");
	HBITMAP hBitmap = (HBITMAP)::LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BITMAP bm;
	::GetObject(hBitmap, sizeof(bm), &bm);

	CString StringPath = _T("F:\\Temp\\12.21.png");
	CImage  Img;
	Img.Attach(hBitmap/**pBitmap*/);
	Img.Save(StringPath, Gdiplus::ImageFormatPNG);

	//
	CFileDialog FileDlg(FALSE, _T("png"), _T("未命名"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("PNG 图片格式 (*.png)|*.png|BMP 图片格式 (*.bmp)|*.bmp|JPG 图片格式 (*.jpg)|*.jpg||"));
	int nRet = FileDlg.DoModal();
	if (nRet == IDOK)
	{
		CString StringExe = _T("png");
		StringExe = FileDlg.GetFileExt();
		CString StringPath = FileDlg.GetPathName();

		CImage  Img;
		Img.Attach(hBitmap/**pBitmap*/);

		if (StringExe == _T("png"))
		{
			Img.Save(StringPath, Gdiplus::ImageFormatPNG);
		}
		else if (StringExe == _T("bmp"))
		{
			Img.Save(StringPath, Gdiplus::ImageFormatBMP);
		}
		else if (StringExe == _T("jpg"))
		{
			Img.Save(StringPath, Gdiplus::ImageFormatJPEG);
		}
		Img.Detach();
		PostQuitMessage(0);
	}
}
