#ifndef __FILEPARSE_H__
#define __FILEPARSE_H__

#include "stdafx.h"

class FileParse
{
public:
	/*
	获取文件大小
	参数： filePath 入参 文件所在的路径
	返回值： 文件大小， 当文件不存在时返回 0
	*/
	long long getFileSize(wchar_t* filePath);
	/*
	获取路径后面的文件名,此函数不判断文件是否存在
	参数：	filepath 入参 文件路径
	参数：	filename 出参 获取的文件名包含文件名的扩展
	如果需要驱动器，所在目录，文件扩展名等可以在此函数内部直接获取
	*/
	void getFileName(wchar_t* filepath, wchar_t* filename);
	//判断文件是否存在
	bool isFileExists(wchar_t* filepath);
};

#endif