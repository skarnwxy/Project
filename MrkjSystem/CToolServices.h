
// Ex0003  股票仿真系统 Wangxiaoyao Add  服务类(公共方法) 2021.2.8

#ifndef CToolServices_H
#define CToolServices_H

#pragma once
class CToolServices
{
public:
	//-------------------------------------------
	CToolServices();
	~CToolServices();

	//-------------------------------------------
	/*
	* 获得当前 exe程序的目录
	*/
	static std::wstring GetDir();

	/*
	* 获得当前 exe程序的目录的上一级
	*/
	static std::wstring GetParentDir();

	/*
	* 报告错误对话框,可以进行格式化的
	*/
	static void MessageBoxFormat(PCTSTR szFmt, ...);
	
	/*
	* 报告错误对话框,可以进行格式化的
	*/
	static void MessageBoxFormatA(PCSTR szFmt, ...);

	static HTREEITEM GetTreeItemClicked(NMHDR *pNMHDR);
};

#endif