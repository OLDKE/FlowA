#ifndef __NORMALREADER_H__
#define __NORMALREADER_H__


/*
说明：	一个读取普通文件类型的读取器
*/

#include "reader.h"

class NormalReader :public Reader
{
public:
	NormalReader() :Reader(){};
	virtual ~NormalReader(){};
public:
	/*
	说明：	一个用来读取普通文件的读取器
	入参：	file 要读取的文件
	出参：	context 保存读取到的文本内容
	返回值：	true 成功 false 失败
	*/
	virtual bool read(FlowaFile file, wchar_t* context) override;
private:
	bool fileProc(FlowaFile file, wchar_t*context);
};

#endif