
// Ex0003  股票仿真系统 Wangxiaoyao Add  数据中表中文件操作 2021.2.10

#include "pch.h"
#include "CTableFiles.h"
namespace CTableFiles
{
	wchar_t * DATA_DATE = L"DATA_DATE";
	wchar_t * PRICE_OPEN = L"PRICE_OPEN";
	wchar_t * PRICE_CLOSE = L"PRICE_CLOSE";
	wchar_t * PRICE_MAX = L"PRICE_MAX";
	wchar_t * PRICE_MIN = L"PRICE_MIN";
	wchar_t * TURNOVER = L"TURNOVER";
	wchar_t * TRADING_VOLUME = L"TRADING_VOLUME";


	/* T_CODE_NAME */
	wchar_t * CODE = L"CODE";
	wchar_t * NAME = L"NAME";


	/*股票代码的最大长度*/
	extern const size_t STOCK_LEN = 6;
}
