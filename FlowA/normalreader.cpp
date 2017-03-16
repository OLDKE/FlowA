#include "normalreader.h"
#include "typedefine.h"

bool NormalReader::read(FlowaFile file, wchar_t* context)
{
	if (!validFile(file))
		return false;
	CString msg;
	//�����ȡ�ļ�
	if (!fileProc(file, context))
		return false;
	//������ɺ��������һ�δ�����ϢΪ��ǰ�ļ�״̬
	file.last_fileSize = file.fileSize;
	StrCpyW(file.last_fileName, file.fileName);
	updateFileStatus(file);
	msg.Format(_T("��ǰ�ı���ȡ����ȡ����\n%s"), context);
	logInfo(msg.GetBuffer());
	return true;
}

/*
˵����	�����ȡ�ļ�,��ʱʵ��Ϊ�����ȡ�������ļ���ȡ���м�������
���:	file Ҫ��ȡ���ļ�
���Σ�	context �����ȡ��������
*/
bool NormalReader::fileProc(FlowaFile file, wchar_t*context)
{

	return false;
}
