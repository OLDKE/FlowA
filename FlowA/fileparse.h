#ifndef __FILEPARSE_H__
#define __FILEPARSE_H__

#include "stdafx.h"

class FileParse
{
public:
	/*
	��ȡ�ļ���С
	������ filePath ��� �ļ����ڵ�·��
	����ֵ�� �ļ���С�� ���ļ�������ʱ���� 0
	*/
	long long getFileSize(wchar_t* filePath);
	/*
	��ȡ·��������ļ���,�˺������ж��ļ��Ƿ����
	������	filepath ��� �ļ�·��
	������	filename ���� ��ȡ���ļ��������ļ�������չ
	�����Ҫ������������Ŀ¼���ļ���չ���ȿ����ڴ˺����ڲ�ֱ�ӻ�ȡ
	*/
	void getFileName(wchar_t* filepath, wchar_t* filename);
	//�ж��ļ��Ƿ����
	bool isFileExists(wchar_t* filepath);
};

#endif