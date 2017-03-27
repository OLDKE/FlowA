#ifndef __CONTENTADAPTER_H__
#define __CONTENTADAPTER_H__

class FlowaFile;
class ContentAdapter
{
public:
	virtual bool format(FlowaFile *file, wchar_t* context, wchar_t* out) = 0;
};

#endif