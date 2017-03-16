#include "ncrreadadapter.h"
#include "typedefine.h"
#include "normalreader.h"

NCRReadAdapter::NCRReadAdapter()
{
	m_reader = new NormalReader();
}

NCRReadAdapter::~NCRReadAdapter()
{
	delete m_reader;
}

bool NCRReadAdapter::read(FlowaFile file, wchar_t* context)
{
	m_reader->read(file, context);
	return (lstrlenW(context) > 0);
}

bool NCRReadAdapter::getContextBlock(FlowaFile file, wchar_t* context, wchar_t* pattern)
{
	return true;
}
