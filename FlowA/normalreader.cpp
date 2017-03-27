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
	//处理读取文件
	if (!fileProc(file, context))
		return false;
	logInfo(context);
	msg.ReleaseBuffer();
	return true;
}

/*
说明：	处理读取文件,暂时实现为共享读取，不对文件读取进行加锁处理
入参:	file 要读取的文件
出参：	context 保存读取到的内容
*/
bool NormalReader::fileProc(FlowaFile* file, wchar_t*context)
{
	try
	{
		USES_CONVERSION;
		//1.打开文件
		CFile mFile(file->filePath, CFile::shareDenyRead | CFile::typeBinary);
		char *buffer = new char[mFile.GetLength() + 1];
		ZeroMemory(buffer, strlen(buffer) + 1);
		//这里需要指定每次读取的快的大小，不能超过context的空间
		//首先定位到上次读取到的位置
		mFile.Seek(file->lastPos, CFile::begin);
		mFile.Read(buffer, CHUNKSIZE);
		//关闭文件
		mFile.Close();
		//根据每个文件的解析配置构造每个要解析文件对应的正则解析对象
		RegexPaser regex(file->pattern);
		//返回模式匹配到的记录,如果匹配失败返回false
		char temp[CHUNKSIZE];
		ZeroMemory(temp, sizeof(temp));
		if (!regex.search(buffer, temp))
			return false;
		//DEBUG
		//AfxMessageBox(context);
		int len_context = strlen(temp);//lstrlenW(context);
		//记录指针上次偏移的位置,上次的偏移等于每次读的长度的累加再加上2字节回车换行
		CString msg;
		msg.Format(_T("业务[%s]本次[%s]文件指针起始偏移[%lld]bytes"), file->businessType, file->fileName, file->lastPos);
		logInfo(msg.GetBuffer());
		StrCpyW(context, A2T(temp));

		if (!isFree(file))
			return false;
		//将上一次的位置指针，存放在注册表当中
		//如果本次文件处理成功，才设置新的文件指针位置
		file->lastPos += (len_context + 2);
		int len = file->lastPos;
		if (file->isAlwaysReadBegin == 1)
		{
			len = (len_context + 2);
		}
		msg.Format(_T("业务[%s]文件[%s]当前共处理[%d]bytes"),file->businessType, file->fileName, len);
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
