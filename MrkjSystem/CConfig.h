
// Ex0003  股票仿真系统 Wangxiaoyao Add  配置文件设置 2021.2.8

#pragma once
#include "pch.h"

#include "string"
#include "CToolServices.h"
#include "CStringServices.h"

const std::wstring FILENAME{ L"sys.ini" };

#ifndef Config_H_
#define Config_H_

// 类声明
class CConfig
{
public:
	//-----------------------------------------------
	/*
	* 构造函数
	*/
	CConfig();

	/*
	* 析构函数
	*/
	~CConfig();

	/*
	* 读取字符串
	*/
	std::wstring ReadString(const TCHAR *szApp, const TCHAR *szKey, const TCHAR* szDefault = _T("")) const;

	/*
	* 读取字符串
	*/
	std::string ReadString(const char *szApp, const char *szKey, const char* szDefault = "") const;

	/*
	* 读取 BOOl 类型值(只能是 1 or 0)
	*/
	BOOL ReadBOOL(const wchar_t *szApp, const wchar_t *szKey, BOOL bDefault = FALSE) const;

	/*
	* 保存
	*/
	void SaveFormat(const TCHAR *const szAppName, TCHAR const* const szKeyName, TCHAR const* const szFormat, ...);

	/*
	* 返回本类的实例 —— 单例模式
	*/
	static CConfig& GetInstance();

	//------------------------------------------------
	// 保存配置文件的路径
	std::wstring m_strFilepath;

	static CConfig cfg;
};
#endif
