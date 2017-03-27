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
说明：根据正则表达式构造，正则解析器
入参：正则表达式字符串
返回值：根据模式生成的正则解析器
*/
RegexPaser *RegexPaser::compile(wchar_t* pattern)
{
	return new RegexPaser(pattern);
}
/*
说明：字符串匹配测试，只有全匹配时候，才返回真，否则返回假
入参：str 需要匹配的字符串
入参：pattern 匹配模式字符串
返回值：	如果模式匹配字符串成功返回 true 否则返回false
*/
bool RegexPaser::match(wchar_t*str, wchar_t* pattern)
{
	return true;
}
/*
说明：在指定字符串当中，查找正则表达式所指定的内容，此函数封装简单，只支持获取一个组的内容
入参：str 要匹配的字符串
入参：pattern 匹配模式
出参：out 匹配到的子串
返回值:如果匹配成功，则返回true 否则返回 false
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