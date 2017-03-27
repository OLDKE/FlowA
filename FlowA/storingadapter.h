#ifndef __STORING_H__
#define __STORING_H__

#include "typedefine.h"

class StoringAdapter
{
public:
	virtual bool storing(FlowaFile* file, wchar_t *context)=0;
};

#endif