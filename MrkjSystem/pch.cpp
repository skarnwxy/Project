// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。
#if CHECK_LOGIN
CMrkjDatabase::DBEntryUser g_loginUser;
#else
CMrkjDatabase::DBEntryUser g_loginUser{ L"1", L"admin", L"admin", L"1", L"1", L"1", L"1", L"1", L"1", L"1", L"1", L"1", L"1" };
#endif