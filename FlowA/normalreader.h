#ifndef __NORMALREADER_H__
#define __NORMALREADER_H__


/*
˵����	һ����ȡ��ͨ�ļ����͵Ķ�ȡ��
*/

#include "reader.h"

class NormalReader :public Reader
{
public:
	NormalReader() :Reader(){};
	virtual ~NormalReader(){};
public:
	/*
	˵����	һ��������ȡ��ͨ�ļ��Ķ�ȡ��
	��Σ�	file Ҫ��ȡ���ļ�
	���Σ�	context �����ȡ�����ı�����
	����ֵ��	true �ɹ� false ʧ��
	*/
	virtual bool read(FlowaFile file, wchar_t* context) override;
private:
	bool fileProc(FlowaFile file, wchar_t*context);
};

#endif