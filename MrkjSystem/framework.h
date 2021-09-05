﻿#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 的一些常见且经常可放心忽略的隐藏警告消息
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC 支持功能区和控制条

//---------------------------------------------------------------
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

//---------------------------------------------------------------
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define  CHECK_LOGIN 1 // 定义是否进行 登陆权限检查

//---------------------------------------------------------------
// # libcurl
#define BUILDING_LIBCURL
#define HTTP_ONLY
#include "../3thd/libcurl/include/curl/curl.h"
#if (defined DEBUG || defined _DEBUG)
#  pragma comment(lib, "../3thd/libcurl/libcurld.lib")
#else
#  pragma comment(lib, "../3thd/libcurl/libcurl.lib")
#endif
#pragma comment(lib, "ws2_32.lib")  // libcurl 需要的库
#pragma comment(lib, "winmm.lib")   // libcurl 需要的库
#pragma comment(lib, "wldap32.lib") // libcurl 需要的库

//---------------------------------------------------------------
#include <tchar.h>

// C++ 标准库
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <tuple>
#include <algorithm>
#include <iosfwd>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <memory>
#include <functional>
#include <iterator>
using namespace std;

//---------------------------------------------------------------
// GDI
#pragma comment( lib, "gdiplus.lib" )
#include "gdiplus.h"
using namespace Gdiplus;

#include "CStringServices.h"
#include "CConfig.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) do { if(ptr) {delete ptr; ptr = nullptr;} }while(0)
#endif

