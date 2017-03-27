#ifndef __NCRREADADAPTER_H__
#define __NCRREADADAPTER_H__

#include "readadapter.h"

class Reader;
class NCRReadAdapter :public ReadAdapter
{
public:
	NCRReadAdapter();
	virtual ~NCRReadAdapter();
	virtual bool read(FlowaFile* file, wchar_t* context) override;
	virtual bool getContextBlock(FlowaFile* file, wchar_t* context, wchar_t* pattern) override;
protected:
	Reader *m_reader;
};

#endif