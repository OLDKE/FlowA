#ifndef __REGPARSE_H__
#define __REGPARSE_H__

/*
*	˵����һ����������ע������
*/

#include "stdafx.h"
#include "logging.h"

class RegParse:public Logging
{
public:
	RegParse();
	virtual ~RegParse();
	bool setReg(wchar_t* key, wchar_t* value);
	bool readReg(wchar_t* key, wchar_t* value);
	bool readReg(wchar_t* key, wchar_t* value, unsigned long* size);
protected:
	bool openReg(wchar_t *subkey);
	bool closeReg();
public:
	HKEY m_hreg;
};

#endif