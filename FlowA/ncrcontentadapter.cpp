#include "ncrcontentadapter.h"
#include "stdafx.h"

NCRContentAdapter::NCRContentAdapter()
{

}

bool NCRContentAdapter::format(FlowaFile* file, wchar_t* context, wchar_t* out)
{
	if (NULL == context || NULL == out)
		return false;
	StrCpyW(out, context);
	return true;
}