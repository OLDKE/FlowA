#ifndef __CONFIG_H__
#define __CONFIG_H__
/*
*	˵����һ����������ע�����ҵ��������Ϣ����
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
	int m_timer;			//flowa��ʱ��
	wchar_t m_atmc[255];	//atm����
	int m_fileCount;		//�ļ�����
	wchar_t m_fileconfig[1024];	//�ļ����ã��ָ���'|'�ֿ���
	wchar_t** m_config;		//�ļ�����������
	FlowaFile* m_flowaFile; //��������Ҫ��ȡ���ļ�����
	wchar_t* m_fileAbsPath;	//Ҫ��ȡ�ļ�ȫ·����ģʽ
public:
	void split(wchar_t* src, wchar_t* delim, wchar_t** res, int ressize);
	void INIT();
	void CLEAN();

};


#endif