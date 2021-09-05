
// Ex0003  ��Ʊ����ϵͳ Wangxiaoyao Add  �����ļ����� 2021.2.8

#pragma once
#include "pch.h"

#include "string"
#include "CToolServices.h"
#include "CStringServices.h"

const std::wstring FILENAME{ L"sys.ini" };

#ifndef Config_H_
#define Config_H_

// ������
class CConfig
{
public:
	//-----------------------------------------------
	/*
	* ���캯��
	*/
	CConfig();

	/*
	* ��������
	*/
	~CConfig();

	/*
	* ��ȡ�ַ���
	*/
	std::wstring ReadString(const TCHAR *szApp, const TCHAR *szKey, const TCHAR* szDefault = _T("")) const;

	/*
	* ��ȡ�ַ���
	*/
	std::string ReadString(const char *szApp, const char *szKey, const char* szDefault = "") const;

	/*
	* ��ȡ BOOl ����ֵ(ֻ���� 1 or 0)
	*/
	BOOL ReadBOOL(const wchar_t *szApp, const wchar_t *szKey, BOOL bDefault = FALSE) const;

	/*
	* ����
	*/
	void SaveFormat(const TCHAR *const szAppName, TCHAR const* const szKeyName, TCHAR const* const szFormat, ...);

	/*
	* ���ر����ʵ�� ���� ����ģʽ
	*/
	static CConfig& GetInstance();

	//------------------------------------------------
	// ���������ļ���·��
	std::wstring m_strFilepath;

	static CConfig cfg;
};
#endif
