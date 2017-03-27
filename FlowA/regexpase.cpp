#include "regexparse.h"
#include "stdafx.h"
#include <boost\regex.hpp>
using namespace boost;

RegexPaser::RegexPaser(wchar_t* pattern)
{
	this->m_pattern = new wchar_t[4096];
	ZeroMemory(this->m_pattern, lstrlenW(this->m_pattern)+1);
	if (NULL != pattern)
		StrCpyW(this->m_pattern, pattern);
}

RegexPaser::~RegexPaser()
{
	delete m_pattern;
	m_pattern = NULL;
}

/*
˵��������������ʽ���죬���������
��Σ�������ʽ�ַ���
����ֵ������ģʽ���ɵ����������
*/
RegexPaser *RegexPaser::compile(wchar_t* pattern)
{
	return new RegexPaser(pattern);
}
/*
˵�����ַ���ƥ����ԣ�ֻ��ȫƥ��ʱ�򣬲ŷ����棬���򷵻ؼ�
��Σ�str ��Ҫƥ����ַ���
��Σ�pattern ƥ��ģʽ�ַ���
����ֵ��	���ģʽƥ���ַ����ɹ����� true ���򷵻�false
*/
bool RegexPaser::match(wchar_t*str, wchar_t* pattern)
{
	return true;
}
/*
˵������ָ���ַ������У�����������ʽ��ָ�������ݣ��˺�����װ�򵥣�ֻ֧�ֻ�ȡһ���������
��Σ�str Ҫƥ����ַ���
��Σ�pattern ƥ��ģʽ
���Σ�out ƥ�䵽���Ӵ�
����ֵ:���ƥ��ɹ����򷵻�true ���򷵻� false
*/
/*
bool RegexPaser::search(wchar_t*str, wchar_t*out, wchar_t* pattern)
{
	wregex re(m_pattern);
	wcmatch buffer;
	if (regex_search(str, buffer, re))
	{
		StrCpyW(out, buffer[0].str().c_str());
	}
	else
		return false;
	return true;
}
*/
bool RegexPaser::search(char*str, char*out, char* pattern)
{
	USES_CONVERSION;
	regex re(T2A(m_pattern));
	cmatch buffer;
	if (regex_search(str, buffer, re))
	{
		strcpy(out, buffer[0].str().c_str());
	}
	else
		return false;
	return true;
}