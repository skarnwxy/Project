// Ex0003  股票仿真系统 Wangxiaoyao Add  配置文件设置 2021.2.8

#include "pch.h"
#include "CConfig.h"

// 类定义
CConfig CConfig::cfg;

CConfig::CConfig()
{
	std::wstring strFilepath = CToolServices::GetDir();
	if (PathFileExists((strFilepath + L"\\" + FILENAME).c_str())) {
		m_strFilepath = (strFilepath + L"\\" + FILENAME);
		return;
	}
	AfxMessageBox(_T("没发现配置文件"));
}

CConfig::~CConfig()
{
	// to do nothing 
}

std::wstring CConfig::ReadString(const TCHAR *szApp, const TCHAR *szKey, const TCHAR* szDefault) const
{
	std::wstring strRet = _T("");
	DWORD dwBufSize = 64;
	TCHAR *szBuffer = nullptr;
	for (int _ = 0; _ < 10; ++_) {
		szBuffer = new TCHAR[dwBufSize + 1];
		ZeroMemory(szBuffer, (1 + dwBufSize) + sizeof(TCHAR));
		DWORD dwRead = ::GetPrivateProfileString(szApp, szKey, szDefault, szBuffer, 1 + dwBufSize, m_strFilepath.c_str());
		//读入的长度 == 缓冲区长度-sizeof(TCHAR),可能有未读完的数据
		if (dwRead == dwBufSize) {
			// 删除原来的缓冲区,并把长度X4
			delete[] szBuffer;
			szBuffer = nullptr;
			dwBufSize *= 4;
		}
		else {
			strRet = szBuffer;
			delete[] szBuffer;
			szBuffer = nullptr;
			break;
		}
	}
	if (szBuffer) {
		delete[] szBuffer;
		szBuffer = nullptr;
	}
	return strRet;
}

std::string CConfig::ReadString(const char *szApp, const char *szKey, const char* szDefault) const
{
	//这种做法,只能读到1023个字符
	char buf[1024] = {};
	DWORD cbRead = 0;
	cbRead = ::GetPrivateProfileStringA(szApp, szKey, szDefault, buf
		, _countof(buf), CStringServices::UnicodeToANSI(m_strFilepath).c_str());
	if (cbRead == 0) {
		return szDefault;
	}
	else {
		buf[cbRead] = '\0';
		return buf;
	}
}

BOOL CConfig::ReadBOOL(const wchar_t *szApp, const wchar_t *szKey, BOOL bDefault) const
{
	return GetPrivateProfileInt(szApp, szKey, bDefault, m_strFilepath.c_str());
}

void CConfig::SaveFormat(const TCHAR *const szAppName, TCHAR const* const szKeyName, TCHAR const* const szFormat, ...)
{
	std::wstring strContent = L"";
	//格式化字符串
	{
		va_list args;
		int len;
		TCHAR *buffer = NULL;
		va_start(args, szFormat);
		len = _vsctprintf(szFormat, args) + 1;
		buffer = new TCHAR[len * sizeof(TCHAR)];
		if (!buffer) {
			goto _fend;
		}
		_vstprintf_s(buffer, len, szFormat, args);
		buffer[len - 1] = _T('\0');
		strContent = buffer;
	_fend:
		if (buffer) {
			delete[] buffer;
		}
	}
	if (strContent.empty()) {
		return;
	}
	WritePrivateProfileString(szAppName, szKeyName, strContent.c_str(), m_strFilepath.c_str());
}

CConfig& CConfig::GetInstance()
{
	//static CConfig cfg;
	return cfg;
}