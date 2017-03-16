#ifndef __XMLPARSE_H__
#define __XMLPARSE_H__

//#include <msxml6.h>
//#pragma("lib", "msxml6.lib")

#ifdef __cplusplus
extern "C"{
#include "include\libxml\xmlmemory.h"
#pragma comment(lib, ".\\libs\\libxml\\libxml2.lib")
}
#endif

class XMLParse
{
public:
	XMLParse();
	virtual ~XMLParse();
};

#endif