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
		˵����	����atm���̻�ȡ��Ӧ���ļ���ȡ������
	*/
	ReadAdapter* getReadAdapter(wchar_t* atmc);
	/*
		˵����	����atm���̻�ȡ��Ӧ�ĸ�ʽת��������
	*/
	FormatAdapter* getFormatAdapter(wchar_t* atmc);
	/*
		˵����	����atm���̻�ȡ��Ӧ�ı��Ĵ���������
	*/
	ContentAdapter* getContentAdapter(wchar_t* atmc);
	/*
		˵����	����atm���̻�ȡ��Ӧ�ı��Ĵ洢������
	*/
	StoringAdapter* getStoringAdapter(wchar_t* atmc);
};

#endif