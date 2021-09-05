
// Ex0003  股票仿真系统 Wangxiaoyao Add  登录界面头文件 2021.2.8

#include "pch.h"

#include "CMrkjSystemApp.h"
#include "CDialogLogin.h" // 登录界面头文件

IMPLEMENT_DYNAMIC(CDialogLogin, CDialogEx)

CDialogLogin::CDialogLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_strUsername(_T(""))
	, m_strPassword(_T(""))
	, m_bRecordPass(FALSE)
{
	// 获取配置文件对象的实例
	m_Config = CConfig::GetInstance();
}

CDialogLogin::~CDialogLogin()
{

}

void CDialogLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUsername);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Check(pDX, IDC_CHECK_RECORD, m_bRecordPass);
}

BEGIN_MESSAGE_MAP(CDialogLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogLogin::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogLogin::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_CHECK_RECORD, &CDialogLogin::OnBnClickedCheckRecord)
END_MESSAGE_MAP()

BOOL CDialogLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	std::wstring username = m_Config.ReadString(L"登陆用户", L"用户名", L"");
	m_strUsername = username.c_str();
	BOOL bRecord = m_Config.ReadBOOL(L"登陆用户", L"是否记录密码", 0);
	std::wstring password = m_Config.ReadString(L"登陆用户", L"密码", L"");
	if (bRecord) {
		m_strPassword = password.c_str();
	}
	m_bRecordPass = bRecord;

	UpdateData(FALSE);
	return TRUE;
}

void CDialogLogin::OnBnClickedButtonLogin()
{
	// (1):
	UpdateData(TRUE);

	// (2):记录配置文件
	RecordInfo();

	// (3):在数据库中查询对比
	// 获取数据库
	CMrkjDatabase DB = CMrkjDatabase::GetInstance();
	if (!DB.QueryUserByUsername(g_loginUser, m_strUsername)) {
		AfxMessageBox(_T("用户名或密码错误"));
		return;
	}

	// (4):查询数据库中的权限信息
	if (!DB.QueryUserByUsername(g_loginUser, m_strUsername)) {
		AfxMessageBox(_T("获取用户信息失败"));
		return;
	}

	// 退出当前对话框
	OnOK();
}

void CDialogLogin::OnBnClickedButtonCancel()
{
	OnCancel();
}

void CDialogLogin::RecordInfo()
{
	// 保存"用户名"到配置文件中
	m_Config.SaveFormat(L"登陆用户", L"用户名", L"%s", m_strUsername.GetString());
	// 保存"是否记录密码"到配置文件中
	m_Config.SaveFormat(L"登陆用户", L"是否记录密码", L"%d", m_bRecordPass);
	// 如果 选定了了 "记录登陆密码",则记录密码到配置文件中
	if (m_bRecordPass) {
		m_Config.SaveFormat(L"登陆用户", L"密码", L"%s", m_strPassword.GetString());
	}
}

void CDialogLogin::OnBnClickedCheckRecord()
{
	UpdateData(TRUE);
	RecordInfo();
	UpdateData(FALSE);
}

void CDialogLogin::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	CDialogEx::OnOK();
}

void CDialogLogin::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	CDialogEx::OnCancel();
}

BOOL CDialogLogin::PreTranslateMessage(MSG* pMsg)
{
	return CDialogEx::PreTranslateMessage(pMsg);
}