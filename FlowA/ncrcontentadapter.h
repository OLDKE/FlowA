#ifndef __NCRCONTENTADAPTER_H__
#define __NCRCONTENTADAPTER_H__

#include "contentadapter.h"

class NCRContentAdapter :public ContentAdapter
{
public:
	NCRContentAdapter();
	virtual bool format()override;
};

#endif