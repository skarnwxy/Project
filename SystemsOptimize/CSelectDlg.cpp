// 2020.12.27 Add CSelectDlg — 垃圾文件选择类型

#include "pch.h"
#include "CSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSelectDlg::CSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDlg::IDD, pParent)
{

}

void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectDlg)
	ON_BN_CLICKED(IDC_BUTOK, OnButok)
	ON_BN_CLICKED(IDC_BUTCANCEL, OnButcancel)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CSelectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	CString num;
	for (int i = 0; i < 25; i++)
	{
		num.Format("%d", i + 1);

		// 获得复选框指针
		CButton* check = (CButton*)GetDlgItem(IDC_CHECK1 + i);
		char ischeck[2];
		GetPrivateProfileString("垃圾文件类型", num, "", ischeck, 2, "./litterfile.ini");
		num = ischeck;

		// 设置复选框状态
		check->SetCheck(atoi(num));
	}
	return TRUE;
}

void CSelectDlg::OnButok()
{
	// TODO: Add your control notification handler code here
	CString num, ischeck;
	for (int i = 0; i < 25; i++)
	{
		num.Format("%d", i + 1);
		CButton* check = (CButton*)GetDlgItem(IDC_CHECK1 + i);// 获得复选框指针
		ischeck.Format("%d", check->GetCheck());              // 设置复选框状态	
		WritePrivateProfileString("垃圾文件类型", num, ischeck, "./litterfile.ini");
	}
	CDialog::OnCancel();
}

void CSelectDlg::OnButcancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

HBRUSH CSelectDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	CBitmap m_BKGround;
	m_BKGround.LoadBitmap(IDB_BITBLANK);
	if (nCtlColor == CTLCOLOR_DLG)
	{
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
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
	}
	return hbr;
}
