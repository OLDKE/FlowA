#ifndef __XMLPARSE_H__
#define __XMLPARSE_H__

/*
说明：用来封装libxml的复杂操作
作者：任康
时间：2017/03/20
*/
//由于使用msxml需要使用COM编程技术，使用门槛高，且复杂所以不采用
//#include <msxml6.h>
//#pragma("lib", "msxml6.lib")
//使用开源C库libxml进行操作
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