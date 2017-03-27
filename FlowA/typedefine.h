#ifndef __TYPEDEFINE_H__
#define __TYPEDEFINE_H__

#include "stdafx.h"
//ATMC厂商类型定义
#define ATMCF_NCR _T("NCR")
//业务类型定义
#define BTYPE_TRN _T("TRN")			//交易信息
#define BTYPE_RTC _T("RTC")			//吞卡信息
#define	BTYPE_STATE _T("STATE")		//状态信息
#define	BTYPE_HARDWARE _T("HARDWARE")	//硬件整体信息
#define	BTYPE_HARDPART _T("HARDPART")	//硬件各部分信息
#define BTYPE_SNR _T("SNR")	//冠字号

//每次读取文件读取的块大小
#define CHUNKSIZE	8192

//Flowa要读取的文件类型定义
class FlowaFile
{
public:
	FlowaFile(){};
	~FlowaFile(){};
	FlowaFile(FlowaFile& file)
	{
		index = file.index;
		StrCpyW(businessType, file.businessType);
		StrCpyW(pattern, file.pattern);
		StrCpyW(filePath, file.filePath);
		StrCpyW(fileName, file.fileName);
		fileSize = file.fileSize;
		lastPos = file.lastPos;
		StrCpyW(last_fileName, file.last_fileName);
		last_fileSize = file.last_fileSize;
		isAlwaysReadBegin = file.isAlwaysReadBegin;
		sharedPos = file.sharedPos;
	}
public:
	int index;					//注册表当中存放文件的列表索引
	wchar_t businessType[128];	//业务类型
	wchar_t pattern[2048];		//解析文件需要的正则表达式
	wchar_t filePath[1024];		//文件存放路径
	wchar_t fileName[1024];		//文件名
	long long fileSize;				//文件大小
	long long lastPos;				//上次处理的文件指针位置
	wchar_t	last_fileName[1024]; //上次处理文件名字
	long long last_fileSize;			//上次处理文件大小
	int isAlwaysReadBegin;		//是否每次都从文件头开始读取
	int sharedPos; //标识共享队列里该文件处理过后数据存放的位置，如果没有可用位置，此变量值为-1。初始为-1
};

#endif