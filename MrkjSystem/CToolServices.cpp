
// Ex0003  股票仿真系统 Wangxiaoyao Add  服务类(公共方法) 2021.2.8

#include "pch.h"
#include "CToolServices.h"

CToolServices::CToolServices()
{
}

CToolServices::~CToolServices()
{
}

 std::wstring CToolServices::GetDir()
{
	TCHAR szBuf[MAX_PATH] = { 0 };
	DWORD cbRead = GetModuleFileName(NULL, szBuf, _countof(szBuf));
	szBuf[cbRead] = _T('\0');
	PathRemoveFileSpec(szBuf);
	return szBuf;
}

 std::wstring CToolServices::GetParentDir()
 {
	 TCHAR szBuf[MAX_PATH] = { 0 };
	 DWORD cbRead = GetModuleFileName(NULL, szBuf, _countof(szBuf));
	 szBuf[cbRead] = _T('\0');
	 PathRemoveFileSpec(szBuf);
	 PathRemoveFileSpec(szBuf);
	 if (_tcslen(szBuf) == _tcslen(szBuf)) {
		 //AfxMessageBox(_T("没有上一目录"));
		 return L"";
	 }
	 return szBuf;
 }

 void CToolServices::MessageBoxFormat(PCTSTR szFmt, ...)
 {
	 const size_t cbSize = 1024;
	 TCHAR szBuf[cbSize + 1] = { 0 };
	 va_list args;
	 va_start(args, szFmt);
	 int nSize = _vsntprintf_s(szBuf, cbSize,// 单位为字节
		 _TRUNCATE, // 字符数,不包括终止符
		 szFmt, args);
	 szBuf[nSize] = 0;
	 AfxMessageBox(szBuf);
 }

 void CToolServices::MessageBoxFormatA(PCSTR szFmt, ...)
 {
	 const size_t cbSize = 1024;
	 CHAR szBuf[cbSize + 1] = { 0 };
	 va_list args;
	 va_start(args, szFmt);
	 int nSize = _vsnprintf_s(szBuf, sizeof(szBuf),// 单位为字节
		 cbSize, // 字符数,不包括终止符
		 szFmt, args);
	 szBuf[nSize] = 0;
	 MessageBoxA(NULL, szBuf, "", MB_ICONERROR);
 }

 HTREEITEM CToolServices::GetTreeItemClicked(NMHDR *pNMHDR)
 {
	 DWORD dwPos = GetMessagePos();
	 TVHITTESTINFO ht = { 0 };
	 ht.pt.x = GET_X_LPARAM(dwPos);
	 ht.pt.y = GET_Y_LPARAM(dwPos);
	 ::MapWindowPoints(HWND_DESKTOP, pNMHDR->hwndFrom, &ht.pt, 1);
	 TreeView_HitTest(pNMHDR->hwndFrom, &ht);
	 return ht.hItem;
 }