
// Ex0003  ��Ʊ����ϵͳ Wangxiaoyao Add  ������(��������) 2021.2.8

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
	* ��õ�ǰ exe�����Ŀ¼
	*/
	static std::wstring GetDir();

	/*
	* ��õ�ǰ exe�����Ŀ¼����һ��
	*/
	static std::wstring GetParentDir();

	/*
	* �������Ի���,���Խ��и�ʽ����
	*/
	static void MessageBoxFormat(PCTSTR szFmt, ...);
	
	/*
	* �������Ի���,���Խ��и�ʽ����
	*/
	static void MessageBoxFormatA(PCSTR szFmt, ...);

	static HTREEITEM GetTreeItemClicked(NMHDR *pNMHDR);
};

#endif