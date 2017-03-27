#ifndef __NCRCONTENTADAPTER_H__
#define __NCRCONTENTADAPTER_H__

#include "contentadapter.h"

class FlowaFile;
class NCRContentAdapter :public ContentAdapter
{
public:
	NCRContentAdapter();
	virtual bool format(FlowaFile* file, wchar_t* context, wchar_t* out)override;
};

#endif