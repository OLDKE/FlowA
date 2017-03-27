#include "normalreader.h"
#include "typedefine.h"
#include "regexparse.h"

NormalReader::~NormalReader()
{
}

bool NormalReader::read(FlowaFile* file, wchar_t* context)
{
	CString msg;
	if (!validFile(file))
		return false;
	//�����ȡ�ļ�
	if (!fileProc(file, context))
		return false;
	logInfo(context);
	msg.ReleaseBuffer();
	return true;
}

/*
˵����	�����ȡ�ļ�,��ʱʵ��Ϊ�����ȡ�������ļ���ȡ���м�������
���:	file Ҫ��ȡ���ļ�
���Σ�	context �����ȡ��������
*/
bool NormalReader::fileProc(FlowaFile* file, wchar_t*context)
{
	try
	{
		USES_CONVERSION;
		//1.���ļ�
		CFile mFile(file->filePath, CFile::shareDenyRead | CFile::typeBinary);
		char *buffer = new char[mFile.GetLength() + 1];
		ZeroMemory(buffer, strlen(buffer) + 1);
		//������Ҫָ��ÿ�ζ�ȡ�Ŀ�Ĵ�С�����ܳ���context�Ŀռ�
		//���ȶ�λ���ϴζ�ȡ����λ��
		mFile.Seek(file->lastPos, CFile::begin);
		mFile.Read(buffer, CHUNKSIZE);
		//�ر��ļ�
		mFile.Close();
		//����ÿ���ļ��Ľ������ù���ÿ��Ҫ�����ļ���Ӧ�������������
		RegexPaser regex(file->pattern);
		//����ģʽƥ�䵽�ļ�¼,���ƥ��ʧ�ܷ���false
		char temp[CHUNKSIZE];
		ZeroMemory(temp, sizeof(temp));
		if (!regex.search(buffer, temp))
			return false;
		//DEBUG
		//AfxMessageBox(context);
		int len_context = strlen(temp);//lstrlenW(context);
		//��¼ָ���ϴ�ƫ�Ƶ�λ��,�ϴε�ƫ�Ƶ���ÿ�ζ��ĳ��ȵ��ۼ��ټ���2�ֽڻس�����
		CString msg;
		msg.Format(_T("ҵ��[%s]����[%s]�ļ�ָ����ʼƫ��[%lld]bytes"), file->businessType, file->fileName, file->lastPos);
		logInfo(msg.GetBuffer());
		StrCpyW(context, A2T(temp));

		if (!isFree(file))
			return false;
		//����һ�ε�λ��ָ�룬�����ע�����
		//��������ļ�����ɹ����������µ��ļ�ָ��λ��
		file->lastPos += (len_context + 2);
		int len = file->lastPos;
		if (file->isAlwaysReadBegin == 1)
		{
			len = (len_context + 2);
		}
		msg.Format(_T("ҵ��[%s]�ļ�[%s]��ǰ������[%d]bytes"),file->businessType, file->fileName, len);
		logInfo(msg.GetBuffer());
		msg.ReleaseBuffer();

		if (!updateFileStatus(file))
			return false;
	}
	catch (CFileException e)
	{
		logInfo(_T("Seek Exception!"));
	}
	return true;
}
