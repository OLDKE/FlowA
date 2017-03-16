#ifndef __TYPEDEFINE_H__
#define __TYPEDEFINE_H__

#include "stdafx.h"
//ATMC�������Ͷ���
#define ATMCF_NCR _T("NCR")
//ҵ�����Ͷ���
#define BTYPE_TRN _T("TRN")			//������Ϣ
#define BTYPE_RTC _T("RTC")			//�̿���Ϣ
#define	BTYPE_STATE _T("STATE")		//״̬��Ϣ
#define	BTYPE_HARDWARE _T("HARDWARE")	//Ӳ��������Ϣ
#define	BTYPE_HARDPART _T("HARDPART")	//Ӳ����������Ϣ
//FlowaҪ��ȡ���ļ����Ͷ���
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
	int index;					//ע����д���ļ����б�����
	wchar_t businessType[128];	//ҵ������
	wchar_t tranType[128];		//��������
	wchar_t filePath[1024];		//�ļ����·��
	wchar_t fileName[1024];		//�ļ���
	int fileSize;				//�ļ���С
	int lastPos;				//�ϴδ�����ļ�ָ��λ��
	wchar_t	last_fileName[1024]; //�ϴδ����ļ�����
	int last_fileSize;			//�ϴδ����ļ���С
	int isAlwaysReadBegin;		//�Ƿ�ÿ�ζ����ļ�ͷ��ʼ��ȡ
};

#endif