#ifndef __READER_H__
#define __READER_H__

#include "regparse.h"

class FlowaFile;
class Reader:public RegParse
{
public:
	Reader();
	virtual ~Reader();
public:
	/*
	说明：	根据文件配置，读取文件内容到context缓存, 此处留下接口实现默认读取，可以通过子类来具体实现具体读取
	出参：	context用来返回读取的内容
	返回值：	true 成功 false 失败
	*/
	virtual bool read(FlowaFile file, wchar_t* context);
	/*
	说明：	判断读取的文件是否有效
	入参：	要判断的文件
	返回值：	true 成功 false 失败
	*/
	virtual bool validFile(FlowaFile file);
	/*
	说明：	判断读取的文件是否是新的文件
	入参：	要判断的文件
	返回值：	true 成功 false 失败
	*/
	virtual bool isNewFile(FlowaFile file);
	/*
	说明：	判断读取的文件是否有脏数据，并记录本次读取文件大小
	入参：	要判断的文件
	返回值：	true 成功 false 失败
	*/
	virtual bool isDirtyFile(FlowaFile file);
	/*
	说明：	判断读取的文件是否读取完成
	入参：	要判断的文件
	返回值：	true 成功 false 失败
	*/
	virtual bool isFileReadOver(FlowaFile file);
	/*
	说明：	更新文件状态
	入参：	要更新的文件
	返回值：	true 成功 false 失败
	*/
	virtual bool updateFileStatus(FlowaFile flowfile);
};

#endif