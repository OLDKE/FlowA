#ifndef __FORMATADAPTER_H__
#define __FORMATADAPTER_H__

class FlowaFile;
class FormatAdapter
{
public:
	virtual bool format(FlowaFile* file, wchar_t* context, wchar_t* out) = 0;
};

#endif