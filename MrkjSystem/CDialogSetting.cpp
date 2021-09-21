/** 
  * Copyright (C) 2021 skarn
  * @file     CDialogSetting.cpp                                                      
  * @brief    ��Ʊ����ϵͳϵͳ���ù��ܵ�Դ�ļ�                                                
  * @author   debugSarn                                                     
  * @date     2021-09-21  
  * @note     
  * @see      
 */


#include "pch.h"
#include "CDialogSetting.h"
#include "Resource.h"

IMPLEMENT_DYNAMIC(CDialogSetting, CDialogEx)

CDialogSetting::CDialogSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
	, m_strID(_T(""))
	, m_strUsername(_T(""))
	, m_strPassword(_T(""))
	, m_b001(FALSE)
	, m_b002(FALSE)
	, m_b003(FALSE)
	, m_b004(FALSE)
	, m_b005(FALSE)
	, m_b006(FALSE)
	, m_b007(FALSE)
	, m_b008(FALSE)
	, m_b009(FALSE)
	, m_b010(FALSE)
{
}

CDialogSetting::~CDialogSetting()
{
}

void CDialogSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA, m_lst);
	DDX_Text(pDX, IDC_EDIT1, m_strID);
	DDX_Text(pDX, IDC_EDIT2, m_strUsername);
	DDX_Text(pDX, IDC_EDIT3, m_strPassword);
	DDX_Control(pDX, IDC_CHECK1, m_btn001);
	DDX_Check(pDX, IDC_CHECK1, m_b001);
	DDX_Control(pDX, IDC_CHECK2, m_btn002);
	DDX_Check(pDX, IDC_CHECK2, m_b002);
	DDX_Control(pDX, IDC_CHECK3, m_btn003);
	DDX_Check(pDX, IDC_CHECK3, m_b003);
	DDX_Control(pDX, IDC_CHECK4, m_btn004);
	DDX_Check(pDX, IDC_CHECK4, m_b004);
	DDX_Control(pDX, IDC_CHECK5, m_btn005);
	DDX_Check(pDX, IDC_CHECK5, m_b005);
	DDX_Control(pDX, IDC_CHECK6, m_btn006);
	DDX_Check(pDX, IDC_CHECK6, m_b006);
	DDX_Control(pDX, IDC_CHECK7, m_btn007);
	DDX_Check(pDX, IDC_CHECK7, m_b007);
	DDX_Control(pDX, IDC_CHECK8, m_btn008);
	DDX_Check(pDX, IDC_CHECK8, m_b008);
	DDX_Control(pDX, IDC_CHECK9, m_btn009);
	DDX_Check(pDX, IDC_CHECK9, m_b009);
	DDX_Control(pDX, IDC_CHECK10, m_btn010);
	DDX_Check(pDX, IDC_CHECK10, m_b010);
}


BEGIN_MESSAGE_MAP(CDialogSetting, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogSetting::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogSetting::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialogSetting::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON8, &CDialogSetting::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_CHECK1, &CDialogSetting::OnBnClickedCheckSystem)
	ON_BN_CLICKED(IDC_CHECK7, &CDialogSetting::OnBnClickedCheckTools)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_DATA, &CDialogSetting::OnLvnItemchangedListData)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDialogSetting ��Ϣ�������
BOOL CDialogSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 1. CListCtrl �ؼ�
	{
		LONG lStyle = GetWindowLong(m_lst.m_hWnd, GWL_STYLE);
		lStyle &= ~LVS_TYPEMASK;
		lStyle |= LVS_REPORT;
		SetWindowLong(m_lst.GetSafeHwnd(), GWL_STYLE, lStyle);
		DWORD dwStyle = m_lst.GetExtendedStyle();
		dwStyle |= LVS_EX_FULLROWSELECT; //ѡ���� ��������
		dwStyle |= LVS_EX_GRIDLINES; //������
		m_lst.SetExtendedStyle(dwStyle);
		// ������,�����ô�С
		{
			CRect rc;
			m_lst.GetClientRect(rc);
			m_lst.InsertColumn(EListIndexID, _T("���"), LVCFMT_LEFT, rc.Width() / EListIndexMaxLimit);
			m_lst.InsertColumn(EListIndexUsername, _T("�û���"), LVCFMT_LEFT, rc.Width() / EListIndexMaxLimit);
			m_lst.InsertColumn(EListIndexPassword, _T("����"), LVCFMT_LEFT, rc.Width() / EListIndexMaxLimit);
			m_lst.InsertColumn(EListIndexP001, _T("ϵͳȨ��"), LVCFMT_LEFT, rc.Width() / EListIndexMaxLimit);
			m_lst.InsertColumn(EListIndexP002, _T("��������ά��Ȩ��"), LVCFMT_LEFT, rc.Width() / EListIndexMaxLimit);
			m_lst.InsertColumn(EListIndexP003, _T("Ʒ��ά��Ȩ��"), LVCFMT_LEFT, rc.Width() / EListIndexMaxLimit);
			m_lst.InsertColumn(EListIndexP004, _T("���뵼��Ȩ��"), LVCFMT_LEFT, rc.Width() / EListIndexMaxLimit);
			m_lst.InsertColumn(EListIndexP005, _T("��ѯȨ��"), LVCFMT_LEFT, rc.Width() / EListIndexMaxLimit);
			m_lst.InsertColumn(EListIndexP006, _T("��ʱ����Ȩ��"), LVCFMT_LEFT, rc.Width() / EListIndexMaxLimit);
			m_lst.InsertColumn(EListIndexP007, _T("����Ȩ��"), LVCFMT_LEFT, rc.Width() / EListIndexMaxLimit);
			m_lst.InsertColumn(EListIndexP008, _T("���ڼ�����Ȩ��"), LVCFMT_LEFT, rc.Width() / EListIndexMaxLimit);
			m_lst.InsertColumn(EListIndexP009, _T("��Ļ��ͼȨ��"), LVCFMT_LEFT, rc.Width() / EListIndexMaxLimit);
			m_lst.InsertColumn(EListIndexP010, _T("ϵͳ����Ȩ��"), LVCFMT_LEFT, rc.Width() / EListIndexMaxLimit);
		}
	}
	UpdateListData();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDialogSetting::OnOK()
{
	ClearList();
	CDialogEx::OnOK();
}

void CDialogSetting::OnCancel()
{
	ClearList();
	CDialogEx::OnCancel();
}

BOOL CDialogSetting::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDialogSetting::UpdateListData()
{
	CMrkjDatabase DB = CMrkjDatabase::GetInstance();
	CMrkjDatabase::VDBEntryUser v;
	if (!DB.QueryUser(v)) {
		return;
	}
	UpdateListData(v);
}

// ����m_lst����
void CDialogSetting::ClearList()
{
	m_lst.DeleteAllItems();
}


// ����m_lst�е�����
void CDialogSetting::UpdateListData(const CMrkjDatabase::VDBEntryUser& v)
{
	ClearList();
	for each(auto data in v) {
		int index = m_lst.GetItemCount();
		m_lst.InsertItem(index, data.id.c_str());
		m_lst.SetItemText(index, EListIndexUsername, data.username.c_str());
		m_lst.SetItemText(index, EListIndexPassword, data.password.c_str());
		m_lst.SetItemText(index, EListIndexP001, data.p001.c_str());
		m_lst.SetItemText(index, EListIndexP002, data.p002.c_str());
		m_lst.SetItemText(index, EListIndexP003, data.p003.c_str());
		m_lst.SetItemText(index, EListIndexP004, data.p004.c_str());
		m_lst.SetItemText(index, EListIndexP005, data.p005.c_str());
		m_lst.SetItemText(index, EListIndexP006, data.p006.c_str());
		m_lst.SetItemText(index, EListIndexP007, data.p007.c_str());
		m_lst.SetItemText(index, EListIndexP008, data.p008.c_str());
		m_lst.SetItemText(index, EListIndexP009, data.p009.c_str());
		m_lst.SetItemText(index, EListIndexP010, data.p010.c_str());
	}
}

// ���ĳ������
void CDialogSetting::GetListData(CMrkjDatabase::DBEntryUser& data, int index)
{
	assert(index >= 0 && index < m_lst.GetItemCount());
	UpdateData(TRUE);
	data.id = m_lst.GetItemText(index, EListIndexID).GetString();
	data.username = m_lst.GetItemText(index, EListIndexUsername).GetString();
	data.password = m_lst.GetItemText(index, EListIndexPassword).GetString();
	data.p001 = m_lst.GetItemText(index, EListIndexP001).GetString();
	data.p002 = m_lst.GetItemText(index, EListIndexP002).GetString();
	data.p003 = m_lst.GetItemText(index, EListIndexP003).GetString();
	data.p004 = m_lst.GetItemText(index, EListIndexP004).GetString();
	data.p005 = m_lst.GetItemText(index, EListIndexP005).GetString();
	data.p006 = m_lst.GetItemText(index, EListIndexP006).GetString();
	data.p007 = m_lst.GetItemText(index, EListIndexP007).GetString();
	data.p008 = m_lst.GetItemText(index, EListIndexP008).GetString();
	data.p009 = m_lst.GetItemText(index, EListIndexP009).GetString();
	data.p010 = m_lst.GetItemText(index, EListIndexP010).GetString();
}

void CDialogSetting::OnBnClickedButtonAdd()
{
	CMrkjDatabase DB = CMrkjDatabase::GetInstance();
	UpdateData();
	if (DB.IsExistUsername(m_strUsername)) {
		CToolServices::MessageBoxFormat(_T("�û���'%s'��������"), m_strUsername.GetString());
		return;
	}
	CMrkjDatabase::DBEntryUser user;
	user.id = m_strID.GetString();
	user.username = m_strUsername.GetString();
	user.password = m_strPassword.GetString();
	user.p002 = CStringServices::ToString(m_b002);
	user.p003 = CStringServices::ToString(m_b003);
	user.p004 = CStringServices::ToString(m_b004);
	user.p005 = CStringServices::ToString(m_b005);
	user.p006 = CStringServices::ToString(m_b006);
	user.p008 = CStringServices::ToString(m_b008);
	user.p009 = CStringServices::ToString(m_b009);
	user.p010 = CStringServices::ToString(m_b010);
	if (!DB.AddUser(user)) {
		CToolServices::MessageBoxFormat(_T("�����û�[%s]ʧ��"), m_strUsername.GetString());
	}
	UpdateData(FALSE);
	UpdateListData();
}


void CDialogSetting::OnBnClickedButtonUpdate()
{
	CMrkjDatabase DB = CMrkjDatabase::GetInstance();
	UpdateData();
	{
		CMrkjDatabase::DBEntryUser user;
		if (!DB.QueryUser(user, m_strID)) {
			AfxMessageBox(_T("û�д��û�?"));
			return;
		}
		// ��� ��ǰ���� != ���ݿ��е��û��� and ��ǰ�û��������ݿ��д���,��Ӧ���޸ĸ��û�
		// ��Ϊ�޸Ĺ�����û� �����ݿ��е������û�����
		if (user.username != m_strUsername.GetString()) {
			if (DB.IsExistUsername(m_strUsername)) {
				CToolServices::MessageBoxFormat(_T("�û���'%s'��������"), m_strUsername.GetString());
				return;
			}
		}
	}
	CMrkjDatabase::DBEntryUser user;
	user.id = m_strID.GetString();
	user.username = m_strUsername.GetString();
	user.password = m_strPassword.GetString();
	user.p001 = CStringServices::ToString(m_b001);
	user.p002 = CStringServices::ToString(m_b002);
	user.p003 = CStringServices::ToString(m_b003);
	user.p004 = CStringServices::ToString(m_b004);
	user.p005 = CStringServices::ToString(m_b005);
	user.p006 = CStringServices::ToString(m_b006);
	user.p007 = CStringServices::ToString(m_b007);
	user.p008 = CStringServices::ToString(m_b008);
	user.p009 = CStringServices::ToString(m_b009);
	user.p010 = CStringServices::ToString(m_b010);
	if (!DB.UpdUser(user)) {
		CToolServices::MessageBoxFormat(_T("�����û�[%s]ʧ��"), m_strUsername.GetString());
	}
	UpdateData(FALSE);
	UpdateListData();
}


void CDialogSetting::OnBnClickedButtonDelete()
{
	CMrkjDatabase::DBEntryUser d;
	// ��ȡѡ�е��û�
	int index = GetSelectLineIndex();
	if (index >= 0) {
		GetListData(d, index);
	}
	else {
		return;
	}
	// ����ǵ�ǰ��½���û�����ɾ��
	if (d.id == g_loginUser.id) {
		AfxMessageBox(_T("����ɾ�����ڵ�½���û�"));
		return;
	}
	
	CMrkjDatabase DB = CMrkjDatabase::GetInstance();
	if (!DB.DelUser(d.id.c_str())) {
		CToolServices::MessageBoxFormat(_T("ɾ���û�[%s]ʧ��"), m_strUsername.GetString());
	}
	UpdateListData();
}


void CDialogSetting::OnBnClickedButtonClose()
{
	OnOK();
}


void CDialogSetting::OnBnClickedCheckSystem()
{
	UpdateData(TRUE);
	m_b002 = m_b001;
	m_b003 = m_b001;
	m_b004 = m_b001;
	UpdateData(FALSE);
}


void CDialogSetting::OnBnClickedCheckTools()
{
	UpdateData(TRUE);
	m_b008 = m_b007;
	m_b009 = m_b007;
	m_b010 = m_b007;
	UpdateData(FALSE);
}


int CDialogSetting::GetSelectLineIndex()
{
	int index = -1;
	POSITION pos = m_lst.GetFirstSelectedItemPosition();
	if (pos) {
		index = m_lst.GetNextSelectedItem(pos);
	}
	return index;
}


void CDialogSetting::OnLvnItemchangedListData(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem >= 0) {
		CMrkjDatabase::DBEntryUser data;
		GetListData(data, pNMListView->iItem);
		m_strID = data.id.c_str();
		m_strUsername = data.username.c_str();
		m_strPassword = data.password.c_str();
		m_b001 = CStringServices::StringTo<int>(data.p001.c_str());
		m_b002 = CStringServices::StringTo<int>(data.p002.c_str());
		m_b003 = CStringServices::StringTo<int>(data.p003.c_str());
		m_b004 = CStringServices::StringTo<int>(data.p004.c_str());
		m_b005 = CStringServices::StringTo<int>(data.p005.c_str());
		m_b006 = CStringServices::StringTo<int>(data.p006.c_str());
		m_b007 = CStringServices::StringTo<int>(data.p007.c_str());
		m_b008 = CStringServices::StringTo<int>(data.p008.c_str());
		m_b009 = CStringServices::StringTo<int>(data.p009.c_str());
		m_b010 = CStringServices::StringTo<int>(data.p010.c_str());
		UpdateData(FALSE);
	}
	//__End:
	*pResult = 0;
}


void CDialogSetting::OnDestroy()
{
	CDialogEx::OnDestroy();
}
