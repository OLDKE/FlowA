#include "fileparse.h"

long long FileParse::getFileSize(wchar_t* filePath)
{
	HANDLE hfile;	//文件句柄
	LARGE_INTEGER	ifilesize;	//用来保存文件大小
	//打开已经存在的文件
	hfile = CreateFile(
		filePath,					//要打开的文件名
		GENERIC_READ,				//以只读的方式打开
		FILE_SHARE_READ,			//共享读取
		NULL,						//安全设置
		OPEN_EXISTING,				//只打开已经存在的文件
		FILE_ATTRIBUTE_NORMAL,		//普通文件
		NULL						//无模板
		);
	if (hfile == INVALID_HANDLE_VALUE)
		return 0l;
	if (!GetFileSizeEx(hfile, &ifilesize))
		return 0l;
	CloseHandle(hfile);//关闭文件
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
		filepath,		//文件所在路径
		drive,			//驱动器
		dir,			//目录
		fname,			//文件名
		ext				//文件名扩展
		);
	StrCatW(fname, ext);
	StrCpyW(filename, fname);
}

bool FileParse::isFileExists(wchar_t* filepath)
{
	WIN32_FIND_DATAW fd;
	HANDLE hFind = FindFirstFile(filepath, &fd);
	if (INVALID_HANDLE_VALUE == hFind)
		return false;
	FindClose(hFind);//记住一定要关闭文件
	return true;
}