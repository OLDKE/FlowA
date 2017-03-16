#ifndef __ADAPTER_H__
#define __ADAPTER_H__

#include "readadapter.h"
#include "formatadapter.h"
#include "contentadapter.h"
#include "storingadapter.h"

class Adapter
{
public:
	/*
		说明：	根据atm厂商获取对应的文件读取适配器
	*/
	ReadAdapter* getReadAdapter(wchar_t* atmc);
	/*
		说明：	根据atm厂商获取对应的格式转换适配器
	*/
	FormatAdapter* getFormatAdapter(wchar_t* atmc);
	/*
		说明：	根据atm厂商获取对应的报文处理适配器
	*/
	ContentAdapter* getContentAdapter(wchar_t* atmc);
	/*
		说明：	根据atm厂商获取对应的报文存储适配器
	*/
	StoringAdapter* getStoringAdapter(wchar_t* atmc);
};

#endif