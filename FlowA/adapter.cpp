#include "adapter.h"
#include "ncrreadadapter.h"
#include "ncrformatadapter.h"
#include "ncrcontentadapter.h"
#include "ncrstoringadapter.h"

/*
˵����	����atm���̻�ȡ��Ӧ���ļ���ȡ������
������	��� ���õ��е�atm����
����ֵ��	��Ӧatm���̵�������
*/
ReadAdapter* Adapter::getReadAdapter(wchar_t* atmc)
{
	return new NCRReadAdapter();
}
/*
˵����	����atm���̻�ȡ��Ӧ�ĸ�ʽת��������
������	��� ���õ��е�atm����
����ֵ��	��Ӧatm���̵�������
*/
FormatAdapter* Adapter::getFormatAdapter(wchar_t* atmc)
{
	return new NCRFormatAdapter();
}
/*
˵����	����atm���̻�ȡ��Ӧ�ı��Ĵ���������
������	��� ���õ��е�atm����
����ֵ��	��Ӧatm���̵�������
*/
ContentAdapter* Adapter::getContentAdapter(wchar_t* atmc)
{
	return new NCRContentAdapter();
}
/*
˵����	����atm���̻�ȡ��Ӧ�ı��Ĵ洢������
������	��� ���õ��е�atm����
����ֵ��	��Ӧatm���̵�������
*/
StoringAdapter* Adapter::getStoringAdapter(wchar_t* atmc)
{
	return new NCRStoringAdapter();
}