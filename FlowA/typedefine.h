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
		StrCpyW(tranType, file.tranType);
		StrCpyW(filePath, file.filePath);
		StrCpyW(fileName, file.fileName);
		fileSize = file.fileSize;
		lastPos = file.lastPos;
		StrCpyW(last_fileName, file.last_fileName);
		last_fileSize = file.last_fileSize;
		isAlwaysReadBegin = file.isAlwaysReadBegin;
	}
public:
	int index;					//注册表当中存放文件的列表索引
	wchar_t businessType[128];	//业务类型
	wchar_t tranType[128];		//交易类型
	wchar_t filePath[1024];		//文件存放路径
	wchar_t fileName[1024];		//文件名
	int fileSize;				//文件大小
	int lastPos;				//上次处理的文件指针位置
	wchar_t	last_fileName[1024]; //上次处理文件名字
	int last_fileSize;			//上次处理文件大小
	int isAlwaysReadBegin;		//是否每次都从文件头开始读取
};

#endif