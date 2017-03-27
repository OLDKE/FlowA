#ifndef __READADAPTER_H__
#define __READADAPTER_H__


/*
说明：一个用来定义文件读取接口的基类
*/

class FlowaFile;
class ReadAdapter
{
public:
	/*
	说明:	从文件中读取内容的接口
	参数：	入参 file 要读取的文件
	参数：	出参 context  读取到的文本字符串
	返回值：	true 成功， false 失败
	*/
	virtual bool read(FlowaFile* file, wchar_t* context) = 0;
	/*
	说明:	从读取的内容中获取指定模式的块
	参数：	入参 file 要读取的文件
	参数：	出参 context  读取到的文本字符串
	参数：	保留 抓取文本块所用的正则表达式
	返回值：	true 成功， false 失败
	*/
	virtual bool getContextBlock(FlowaFile* file, wchar_t* context, wchar_t* pattern) = 0;
};

#endif