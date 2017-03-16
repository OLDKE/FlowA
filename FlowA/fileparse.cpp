#include "fileparse.h"

long long FileParse::getFileSize(wchar_t* filePath)
{
	HANDLE hfile;	//�ļ����
	LARGE_INTEGER	ifilesize;	//���������ļ���С
	//���Ѿ����ڵ��ļ�
	hfile = CreateFile(
		filePath,					//Ҫ�򿪵��ļ���
		GENERIC_READ,				//��ֻ���ķ�ʽ��
		FILE_SHARE_READ,			//�����ȡ
		NULL,						//��ȫ����
		OPEN_EXISTING,				//ֻ���Ѿ����ڵ��ļ�
		FILE_ATTRIBUTE_NORMAL,		//��ͨ�ļ�
		NULL						//��ģ��
		);
	if (hfile == INVALID_HANDLE_VALUE)
		return 0l;
	if (!GetFileSizeEx(hfile, &ifilesize))
		return 0l;
	return ifilesize.QuadPart;
}

void FileParse::getFileName(wchar_t* filepath, wchar_t* filename)
{
	if (NULL == filepath || filename == NULL)
		return;
	wchar_t drive[_MAX_DRIVE];
	wchar_t dir[_MAX_DIR];
	wchar_t fname[_MAX_FNAME];
	wchar_t ext[_MAX_EXT];
	_wsplitpath(
		filepath,		//�ļ�����·��
		drive,			//������
		dir,			//Ŀ¼
		fname,			//�ļ���
		ext				//�ļ�����չ
		);
	StrCatW(fname, ext);
	StrCpyW(filename, fname);
}