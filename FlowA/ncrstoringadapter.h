#ifndef __NCRSTORINGADAPTER_H__
#define __NCRSTORINGADAPTER_H__

#include "storingadapter.h"

class NCRStoringAdapter :public StoringAdapter
{
public:
	virtual bool storing() override;
};

#endif