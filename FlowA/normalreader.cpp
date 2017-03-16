#include "normalreader.h"
#include "typedefine.h"

bool NormalReader::read(FlowaFile file, wchar_t* context)
{
	if (!validFile(file))
		return false;
	CString msg;
	//处理读取文件
	if (!fileProc(file, context))
		return false;
	//处理完成后，设置最后一次处理信息为当前文件状态
	file.last_fileSize = file.fileSize;
	StrCpyW(file.last_fileName, file.fileName);
	updateFileStatus(file);
	msg.Format(_T("当前文本读取器读取内容\n%s"), context);
	logInfo(msg.GetBuffer());
	return true;
}

/*
说明：	处理读取文件,暂时实现为共享读取，不对文件读取进行加锁处理
入参:	file 要读取的文件
出参：	context 保存读取到的内容
*/
bool NormalReader::fileProc(FlowaFile file, wchar_t*context)
{

	return false;
}
