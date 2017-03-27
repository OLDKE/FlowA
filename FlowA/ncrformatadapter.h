#ifndef __NCRFORMATADAPTER_H__
#define __NCRFORMATADAPTER_H__

#include "formatadapter.h"

class FlowaFile;
class NCRFormatAdapter :public FormatAdapter
{
public:
	NCRFormatAdapter();
	virtual bool format(FlowaFile* file, wchar_t* context, wchar_t* out)override;
private:
	bool formatTrn(FlowaFile* file, wchar_t* context, wchar_t* out);
	bool formatDev(FlowaFile* file, wchar_t* context, wchar_t* out);
	bool formatDevPart(FlowaFile* file, wchar_t* context, wchar_t* out);
	bool formatSNR(FlowaFile* file, wchar_t* context, wchar_t* out);
};

#endif