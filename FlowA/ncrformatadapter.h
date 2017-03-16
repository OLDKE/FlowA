#ifndef __NCRFORMATADAPTER_H__
#define __NCRFORMATADAPTER_H__

#include "formatadapter.h"

class NCRFormatAdapter :public FormatAdapter
{
public:
	NCRFormatAdapter();
	virtual bool format()override;
};

#endif