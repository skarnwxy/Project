
// Ex0003  ��Ʊ����ϵͳ Wangxiaoyao Add  ��¼����ͷ�ļ� 2021.2.8

#include "pch.h"

#include "CMrkjSystemApp.h"
#include "CDialogLogin.h" // ��¼����ͷ�ļ�

IMPLEMENT_DYNAMIC(CDialogLogin, CDialogEx)

CDialogLogin::CDialogLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_strUsername(_T(""))
	, m_strPassword(_T(""))
	, m_bRecordPass(FALSE)
{
	// ��ȡ�����ļ������ʵ��
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
	std::wstring username = m_Config.ReadString(L"��½�û�", L"�û���", L"");
	m_strUsername = username.c_str();
	BOOL bRecord = m_Config.ReadBOOL(L"��½�û�", L"�Ƿ��¼����", 0);
	std::wstring password = m_Config.ReadString(L"��½�û�", L"����", L"");
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

	// (2):��¼�����ļ�
	RecordInfo();

	// (3):�����ݿ��в�ѯ�Ա�
	// ��ȡ���ݿ�
	CMrkjDatabase DB = CMrkjDatabase::GetInstance();
	if (!DB.QueryUserByUsername(g_loginUser, m_strUsername)) {
		AfxMessageBox(_T("�û������������"));
		return;
	}

	// (4):��ѯ���ݿ��е�Ȩ����Ϣ
	if (!DB.QueryUserByUsername(g_loginUser, m_strUsername)) {
		AfxMessageBox(_T("��ȡ�û���Ϣʧ��"));
		return;
	}

	// �˳���ǰ�Ի���
	OnOK();
}

void CDialogLogin::OnBnClickedButtonCancel()
{
	OnCancel();
}

void CDialogLogin::RecordInfo()
{
	// ����"�û���"�������ļ���
	m_Config.SaveFormat(L"��½�û�", L"�û���", L"%s", m_strUsername.GetString());
	// ����"�Ƿ��¼����"�������ļ���
	m_Config.SaveFormat(L"��½�û�", L"�Ƿ��¼����", L"%d", m_bRecordPass);
	// ��� ѡ������ "��¼��½����",���¼���뵽�����ļ���
	if (m_bRecordPass) {
		m_Config.SaveFormat(L"��½�û�", L"����", L"%s", m_strPassword.GetString());
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
	// TODO: �ڴ����ר�ô����/����û���
	CDialogEx::OnOK();
}

void CDialogLogin::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialogEx::OnCancel();
}

BOOL CDialogLogin::PreTranslateMessage(MSG* pMsg)
{
	return CDialogEx::PreTranslateMessage(pMsg);
}