#ifndef __CONFIG_H__
#define __CONFIG_H__
/*
*	说明：一个用来加载注册表当中业务配置信息的类
*
*/
#include "regparse.h"
#include "fileparse.h"
#include "typedefine.h"

class Config :public RegParse, public FileParse
{
public:
	Config();
	~Config();
public:
	bool loadConfig();
	void getDynamicFileName(wchar_t *regdatecfg, wchar_t* filename);
public:
	int m_timer;			//flowa定时器
	wchar_t m_atmc[255];	//atm厂商
	int m_fileCount;		//文件数量
	wchar_t m_fileconfig[1024];	//文件配置（分隔符'|'分开）
	wchar_t** m_config;		//文件配置域数组
	FlowaFile* m_flowaFile; //用来保存要读取的文件数组
	wchar_t* m_fileAbsPath;	//要读取文件全路径的模式
public:
	void split(wchar_t* src, wchar_t* delim, wchar_t** res, int ressize);
	void INIT();
	void CLEAN();

};


#endif