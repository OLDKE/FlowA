#ifndef __NCRSTORINGADAPTER_H__
#define __NCRSTORINGADAPTER_H__

#include "storingadapter.h"
#include "regparse.h"

class NCRStoringAdapter :public StoringAdapter, public RegParse
{
public:
	virtual bool storing(FlowaFile* file, wchar_t* context) override;
};

#endif