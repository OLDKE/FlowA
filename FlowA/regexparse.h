#ifndef __REGEXPARSE_H__
#define __REGEXPARSE_H__

class RegexPaser
{
public:
	RegexPaser(wchar_t* m_pattern = (wchar_t*)0);
	virtual ~RegexPaser();
public:
	/*
	说明：根据正则表达式构造，正则解析器
	入参：正则表达式字符串
	返回值：根据模式生成的正则解析器
	*/
	RegexPaser *compile(wchar_t* pattern);
	/*
	说明：字符串匹配测试，只有全匹配时候，才返回真，否则返回假
	入参：str 需要匹配的字符串
	入参：pattern 匹配模式字符串
	返回值：	如果模式匹配字符串成功返回 true 否则返回false
	*/
	bool match(wchar_t*str, wchar_t* pattern = (wchar_t*)0);
	/*
	说明：在指定字符串当中，查找正则表达式所指定的内容，此函数封装简单，只支持获取一个组的内容
	入参：str 要匹配的字符串
	入参：pattern 匹配模式
	出参：out 匹配到的子串
	返回值:如果匹配成功，则返回true 否则返回 false
	*/
	//bool search(wchar_t*str, wchar_t*out, wchar_t* pattern = (wchar_t*)0);
	bool search(char*str, char*out, char* pattern = (char*)0);
private:
	wchar_t* m_pattern;
};

#endif