#ifndef __XMLPARSE_H__
#define __XMLPARSE_H__

/*
˵����������װlibxml�ĸ��Ӳ���
���ߣ��ο�
ʱ�䣺2017/03/20
*/
//����ʹ��msxml��Ҫʹ��COM��̼�����ʹ���ż��ߣ��Ҹ������Բ�����
//#include <msxml6.h>
//#pragma("lib", "msxml6.lib")
//ʹ�ÿ�ԴC��libxml���в���
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