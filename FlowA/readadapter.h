#ifndef __READADAPTER_H__
#define __READADAPTER_H__


/*
˵����һ�����������ļ���ȡ�ӿڵĻ���
*/

class FlowaFile;
class ReadAdapter
{
public:
	/*
	˵��:	���ļ��ж�ȡ���ݵĽӿ�
	������	��� file Ҫ��ȡ���ļ�
	������	���� context  ��ȡ�����ı��ַ���
	����ֵ��	true �ɹ��� false ʧ��
	*/
	virtual bool read(FlowaFile* file, wchar_t* context) = 0;
	/*
	˵��:	�Ӷ�ȡ�������л�ȡָ��ģʽ�Ŀ�
	������	��� file Ҫ��ȡ���ļ�
	������	���� context  ��ȡ�����ı��ַ���
	������	���� ץȡ�ı������õ�������ʽ
	����ֵ��	true �ɹ��� false ʧ��
	*/
	virtual bool getContextBlock(FlowaFile* file, wchar_t* context, wchar_t* pattern) = 0;
};

#endif