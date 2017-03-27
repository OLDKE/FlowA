#ifndef __READER_H__
#define __READER_H__

#include "regparse.h"
#include "fileparse.h"

class FlowaFile;
class Reader:public RegParse, public FileParse
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
	virtual bool read(FlowaFile* file, wchar_t* context);
	/*
	说明：	判断读取的文件是否有效
	入参：	要判断的文件
	返回值：	true 成功 false 失败
	*/
	virtual bool validFile(FlowaFile* file);
	/*
	说明：	判断读取的文件是否是新的文件
	入参：	要判断的文件
	返回值：	true 成功 false 失败
	*/
	virtual bool isNewFile(FlowaFile* file);
	/*
	说明：	判断读取的文件是否有脏数据
	入参：	要判断的文件
	返回值：	true 文件未处理完毕 false 文件未处理完毕（脏数据）
	*/
	virtual bool isNotDirtyFile(FlowaFile* file);
	/*
	说明：	更新文件状态
	入参：	要更新的文件
	返回值：	true 成功 false 失败， 如果共享队列为满，则不更新这次文件状态
	*/
	virtual bool updateFileStatus(FlowaFile *flowfile);
	
	virtual bool isFree(FlowaFile *flowfile);
	virtual bool update(FlowaFile *flowfile);
	/*
	说明： 读写者模式， 检测共享队列的信号量标志，如果和读者的共享队列里有空余位置（信号量为1已消费），则返回此位置的下标。
	出参	: 共享队列空闲位置的下标
	返回值：	true 队列未满，可以继续往队列里添加数据
	返回值： false 队列以满，不可以继续往队列里追加数据，等待消费者去消费
	*/
	virtual bool getShareDataBufferTrn(int* index);
	virtual bool getShareDataBufferDev(int* index);
	virtual bool getShareDataBufferDevPart(int* index);
	virtual bool getShareDataBufferSNR(int* index);
};

#endif