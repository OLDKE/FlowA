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
	˵����	�����ļ����ã���ȡ�ļ����ݵ�context����, �˴����½ӿ�ʵ��Ĭ�϶�ȡ������ͨ������������ʵ�־����ȡ
	���Σ�	context�������ض�ȡ������
	����ֵ��	true �ɹ� false ʧ��
	*/
	virtual bool read(FlowaFile* file, wchar_t* context);
	/*
	˵����	�ж϶�ȡ���ļ��Ƿ���Ч
	��Σ�	Ҫ�жϵ��ļ�
	����ֵ��	true �ɹ� false ʧ��
	*/
	virtual bool validFile(FlowaFile* file);
	/*
	˵����	�ж϶�ȡ���ļ��Ƿ����µ��ļ�
	��Σ�	Ҫ�жϵ��ļ�
	����ֵ��	true �ɹ� false ʧ��
	*/
	virtual bool isNewFile(FlowaFile* file);
	/*
	˵����	�ж϶�ȡ���ļ��Ƿ���������
	��Σ�	Ҫ�жϵ��ļ�
	����ֵ��	true �ļ�δ������� false �ļ�δ������ϣ������ݣ�
	*/
	virtual bool isNotDirtyFile(FlowaFile* file);
	/*
	˵����	�����ļ�״̬
	��Σ�	Ҫ���µ��ļ�
	����ֵ��	true �ɹ� false ʧ�ܣ� ����������Ϊ�����򲻸�������ļ�״̬
	*/
	virtual bool updateFileStatus(FlowaFile *flowfile);
	
	virtual bool isFree(FlowaFile *flowfile);
	virtual bool update(FlowaFile *flowfile);
	/*
	˵���� ��д��ģʽ�� ��⹲����е��ź�����־������Ͷ��ߵĹ���������п���λ�ã��ź���Ϊ1�����ѣ����򷵻ش�λ�õ��±ꡣ
	����	: ������п���λ�õ��±�
	����ֵ��	true ����δ�������Լ������������������
	����ֵ�� false ���������������Լ�����������׷�����ݣ��ȴ�������ȥ����
	*/
	virtual bool getShareDataBufferTrn(int* index);
	virtual bool getShareDataBufferDev(int* index);
	virtual bool getShareDataBufferDevPart(int* index);
	virtual bool getShareDataBufferSNR(int* index);
};

#endif