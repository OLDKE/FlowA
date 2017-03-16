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
	˵����	�����ļ����ã���ȡ�ļ����ݵ�context����, �˴����½ӿ�ʵ��Ĭ�϶�ȡ������ͨ������������ʵ�־����ȡ
	���Σ�	context�������ض�ȡ������
	����ֵ��	true �ɹ� false ʧ��
	*/
	virtual bool read(FlowaFile file, wchar_t* context);
	/*
	˵����	�ж϶�ȡ���ļ��Ƿ���Ч
	��Σ�	Ҫ�жϵ��ļ�
	����ֵ��	true �ɹ� false ʧ��
	*/
	virtual bool validFile(FlowaFile file);
	/*
	˵����	�ж϶�ȡ���ļ��Ƿ����µ��ļ�
	��Σ�	Ҫ�жϵ��ļ�
	����ֵ��	true �ɹ� false ʧ��
	*/
	virtual bool isNewFile(FlowaFile file);
	/*
	˵����	�ж϶�ȡ���ļ��Ƿ��������ݣ�����¼���ζ�ȡ�ļ���С
	��Σ�	Ҫ�жϵ��ļ�
	����ֵ��	true �ɹ� false ʧ��
	*/
	virtual bool isDirtyFile(FlowaFile file);
	/*
	˵����	�ж϶�ȡ���ļ��Ƿ��ȡ���
	��Σ�	Ҫ�жϵ��ļ�
	����ֵ��	true �ɹ� false ʧ��
	*/
	virtual bool isFileReadOver(FlowaFile file);
	/*
	˵����	�����ļ�״̬
	��Σ�	Ҫ���µ��ļ�
	����ֵ��	true �ɹ� false ʧ��
	*/
	virtual bool updateFileStatus(FlowaFile flowfile);
};

#endif