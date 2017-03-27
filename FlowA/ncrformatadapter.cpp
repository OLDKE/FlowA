#include "ncrformatadapter.h"
#include "stdafx.h"

//boost������ʽ
#include "config.h"
#include "regexparse.h"
//boost������ʽ

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
	if (StrCmpW(file->businessType, BTYPE_TRN) == 0) //����
	{
		if (!formatTrn(file, context, out))
			return false;
	}

	if (StrCmpW(file->businessType, BTYPE_HARDWARE) == 0) //�豸
	{
		if (!formatDev(file, context, out))
			return false;
	}

	if (StrCmpW(file->businessType, BTYPE_HARDPART) == 0) //�豸����
	{
		if (!formatDevPart(file, context, out))
			return false;
	}

	if (StrCmpW(file->businessType, BTYPE_SNR) == 0) //���ֺ�
	{
		if (!formatSNR(file, context, out))
			return false;
	}
	//������豸��������Ҫ����豸�������豸����״̬��һ������
	return true;
}

bool NCRFormatAdapter::formatTrn(FlowaFile* file, wchar_t* context, wchar_t* out)
{
	//��ʽ�����ױ���
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