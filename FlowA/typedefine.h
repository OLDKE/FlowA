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
#define BTYPE_SNR _T("SNR")	//���ֺ�

//ÿ�ζ�ȡ�ļ���ȡ�Ŀ��С
#define CHUNKSIZE	8192

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
	int index;					//ע����д���ļ����б�����
	wchar_t businessType[128];	//ҵ������
	wchar_t pattern[2048];		//�����ļ���Ҫ��������ʽ
	wchar_t filePath[1024];		//�ļ����·��
	wchar_t fileName[1024];		//�ļ���
	long long fileSize;				//�ļ���С
	long long lastPos;				//�ϴδ�����ļ�ָ��λ��
	wchar_t	last_fileName[1024]; //�ϴδ����ļ�����
	long long last_fileSize;			//�ϴδ����ļ���С
	int isAlwaysReadBegin;		//�Ƿ�ÿ�ζ����ļ�ͷ��ʼ��ȡ
	int sharedPos; //��ʶ�����������ļ�����������ݴ�ŵ�λ�ã����û�п���λ�ã��˱���ֵΪ-1����ʼΪ-1
};

#endif