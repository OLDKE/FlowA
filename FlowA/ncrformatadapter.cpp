#include "ncrformatadapter.h"
#include "stdafx.h"

//boost正则表达式
#include "config.h"
#include "regexparse.h"
//boost正则表达式

#ifdef __cplusplus
extern "C"{
#include "include\libxml\xmlmemory.h"
#include "include\libxml\parser.h"
#include "include\libxml\tree.h"
#include "include\libxml\xpath.h"
#pragma comment(lib, ".\\libs\\libxml\\libxml2.lib")
}
#endif

NCRFormatAdapter::NCRFormatAdapter()
{

}

bool NCRFormatAdapter::format(FlowaFile* file, wchar_t* context, wchar_t* out)
{
	if (NULL == context || out == NULL)
		return false;
	if (StrCmpW(file->businessType, BTYPE_TRN) == 0) //交易
	{
		if (!formatTrn(file, context, out))
			return false;
	}

	if (StrCmpW(file->businessType, BTYPE_HARDWARE) == 0) //设备
	{
		if (!formatDev(file, context, out))
			return false;
	}

	if (StrCmpW(file->businessType, BTYPE_HARDPART) == 0) //设备部件
	{
		if (!formatDevPart(file, context, out))
			return false;
	}

	if (StrCmpW(file->businessType, BTYPE_SNR) == 0) //冠字号
	{
		if (!formatSNR(file, context, out))
			return false;
	}
	//如果是设备报文则需要组合设备部件和设备整体状态成一个报文
	return true;
}

bool NCRFormatAdapter::formatTrn(FlowaFile* file, wchar_t* context, wchar_t* out)
{
	//格式化交易报文
	StrCpyW(out, context);
	return true;
}

bool NCRFormatAdapter::formatDev(FlowaFile* file, wchar_t* context, wchar_t* out)
{
	//defalut
	StrCpyW(out, context);
	return true;
}

bool NCRFormatAdapter::formatDevPart(FlowaFile* file, wchar_t* context, wchar_t* out)
{
	StrCpyW(out, context);
	return true;
}

bool NCRFormatAdapter::formatSNR(FlowaFile* file, wchar_t* context, wchar_t* out)
{
//	AfxMessageBox(context);
	StrCpyW(out, context);
	return true;
}