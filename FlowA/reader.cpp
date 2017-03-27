#include "reader.h"
#include "typedefine.h"

Reader::Reader()
{
}

Reader::~Reader()
{

}

bool Reader::read(FlowaFile* file, wchar_t* context)
{

	return true;
}

bool Reader::validFile(FlowaFile* file)
{
	CString msg;
	//1.判断文件是否存在，如果不存在则不进行后续文件处理
	if (!isFileExists(file->filePath))
		return false;
	//2.判断atm是否更新了日志名字
	//如果是新的日志文件，则将注册表对应文件配置更新
	if (isNewFile(file))
	{
		file->lastPos = 0;
		file->last_fileSize = 0;
		msg.Format(_T("上次分析文件名[%s]---变化-->[%s]"), file->last_fileName,file->fileName);
		logInfo(msg.GetBuffer());
		StrCpyW(file->last_fileName, file->fileName);
	}
	//3.表示当前文件如果没有脏数据则校验失败，不进行后续处理，当前文件和上一次读取时没有改变，则不做处理。
	if (isNotDirtyFile(file))
		return false;
	//4.当前文件有有新内容追加时(表示脏数据)，继续读取。
	return true;
}

bool Reader::isNewFile(FlowaFile* file)
{
	//如果上一次处理的文件名和这次处理的文件名不相同，则说明文件名改变
	if (StrCmpW(file->last_fileName, file->fileName) != 0)
		return true;
	return false;
}

//返回值：	true 文件已经处理完毕， false文件没有处理完毕
bool Reader::isNotDirtyFile(FlowaFile* file)
{
	CString msg;
	//如果为每次重复读取，则直接返回继续处理
	if (file->isAlwaysReadBegin == 1)
	{
		msg.Format(_T("重新从[%s]文件头读取文件状态"), file->filePath);
		logInfo(msg.GetBuffer());
		return false;
	}
	
	//如果上次处理的文件大小，大于上次的文件指针位置，说明有数据追加，文件未处理完，继续处理上次文件
	if (file->last_fileSize > file->lastPos)
	{
		msg.Format(_T("文件[%s]未处理完，继续处理"), file->filePath);
		logInfo(msg.GetBuffer());
		return false;
	}
	//如果文件大小小于上次文件指针的位置，说明出现异常，不做后续处理，或者
	//上次文件大小等于上次的文件位置指针，说明文件已经读取完毕，不进行后面文件处理
	if (file->last_fileSize <= file->lastPos && file->last_fileSize != 0)
	{
		msg.Format(_T("文件[%s]已经读完，不进行后续处理"), file->filePath);
		logInfo(msg.GetBuffer());
		return true;
	}
	return false;
}

/*
说明： 用来更新注册表文件配置的函数
参数： 入参 要更新的文件
返回值： true成功， false失败
*/
bool Reader::updateFileStatus(FlowaFile* flowafile)
{
	CString state;
	CString key;
	CString msg;

	//如果文件配置为每次从文件头开始读取,则不记录文件跳转位置
	if (flowafile->isAlwaysReadBegin == 1)
	{
		flowafile->fileSize = 0;
		flowafile->lastPos = 0;
	}

	if (!update(flowafile))
		return false;
	return true;
}

bool Reader::update(FlowaFile *flowafile)
{
	CString state;
	CString key;
	CString msg;
	
	//2.设置上一次处理信息为当前文件状态
	flowafile->last_fileSize = flowafile->fileSize;
	StrCpyW(flowafile->last_fileName, flowafile->fileName);
	state.Format(_T("%s|%s|%s|%lld|%lld|%d"), flowafile->businessType, flowafile->pattern, flowafile->fileName, flowafile->fileSize, flowafile->lastPos, flowafile->isAlwaysReadBegin);
	if (!openReg(_T("SOFTWARE\\Ebring\\Agent\\Config\\FLOWA\\FILES")))
	{
		msg.Format(_T("打开注册表失败[%s]"), _T("SOFTWARE\\Ebring\\Agent\\Config\\FLOWA\\FILES"));
		logError(msg.GetBuffer());
		return false;
	}
	key.Format(_T("FILE%d_STATE"), flowafile->index);
	if (!setReg(key.GetBuffer(), state.GetBuffer()))
	{
		msg.Format(_T("设置注册表键值失败[%s]"), state.GetBuffer());
		logError(msg.GetBuffer());
		return false;
	}
	closeReg();
	msg.Format(_T("更新文件状态，key=[FILE%d_STATE]，value=[%s]"), flowafile->index, state.GetBuffer());
	logInfo(msg.GetBuffer());
	msg.ReleaseBuffer();
	return true;
}

//1.检测和agent的共享队列是否有位置可以存放数据，
//队列如果满或者信号量标志不为1表示（1表示以被agent处理）临界区还没被释放（Agent还没有上送）
//则本次文件状态不更新，交易不处理，下次重新读取处理。
bool Reader::isFree(FlowaFile *flowafile)
{
	if (flowafile->isAlwaysReadBegin == 1)
	{
		//如果为每次重复读取的文件，则不用判断队列是否为满，默认覆盖共享队列的第一个位置的数据
		flowafile->sharedPos = 0;
		return true;
	}
	
	if (StrCmpW(flowafile->businessType, BTYPE_TRN) == 0) //交易业务
	{
		int pos;
		if (!getShareDataBufferTrn(&pos))
		{
			flowafile->sharedPos = -1;
			return false;
		}
		//给当前处理的文件数据指定要存储在队列的位置
		flowafile->sharedPos = pos;
	}
	else if (StrCmpW(flowafile->businessType, BTYPE_HARDWARE) == 0) //设备相关
	{
		int pos;
		if (!getShareDataBufferDev(&pos))
		{
			flowafile->sharedPos = -1;
			return false;
		}
		
		//给当前处理的文件数据指定要存储在队列的位置
		flowafile->sharedPos = pos;
	}
	else if (StrCmpW(flowafile->businessType, BTYPE_HARDPART) == 0) //设备部件
	{
		int pos;
		if (!getShareDataBufferDevPart(&pos))
		{
			flowafile->sharedPos = -1;
			return false;
		}
		
		//给当前处理的文件数据指定要存储在队列的位置
		flowafile->sharedPos = pos;
	}
	else if (StrCmpW(flowafile->businessType, BTYPE_SNR) == 0) //冠字号
	{
		int pos;
		if (!getShareDataBufferSNR(&pos))
		{
			flowafile->sharedPos = -1;
			return false;
		}
		
		//给当前处理的文件数据指定要存储在队列的位置
		flowafile->sharedPos = pos;
	}
	
	return true;
}

/*
说明： 读写者模式， 检测共享队列的信号量标志，如果和读者的共享队列里有空余位置（信号量为1已消费），则返回此位置的下标。
出参	: 共享队列空闲位置的下标
返回值：	true 队列未满，可以继续往队列里添加数据
返回值： false 队列以满，不可以继续往队列里追加数据，等待消费者去消费
*/
bool Reader::getShareDataBufferTrn(int* index)
{
	if (!openReg(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\TRN")))
		return false;
	wchar_t size[1024];
	ZeroMemory(size, sizeof(size));
	//获取共享队列的长度
	if (!readReg(_T("SIZE"), size))
		return false;
	closeReg();
	int qsize = _wtoi(size);
	CString key;
	//开始检测队列里每个位置的信号量
	int i = 0;
	for (; i < qsize; ++i)
	{
		key.Format(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\TRN\\%d"), i);
		if (!openReg(key.GetBuffer()))
			return false;
		key.ReleaseBuffer();
		wchar_t resp[1024];
		ZeroMemory(resp, sizeof(resp));
		if (!readReg(_T("SIGNAL"), resp))
			return false;
		int signal = _wtoi(resp);
		closeReg();
		if (signal == 1)
			break;
	}
	if (i != qsize) //说明在共享队列里找到了可存储位置
	{
		*index = i;
		return true;
	}
	else
		return false;
	//默认不做存储处理
	return false;
}

bool Reader::getShareDataBufferDev(int* index)
{	
	if (!openReg(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\DEV")))
		return false;
	wchar_t size[1024];
	ZeroMemory(size, sizeof(size));
	//获取共享队列的长度
	if (!readReg(_T("SIZE"), size))
		return false;
	closeReg();
	int qsize = _wtoi(size);
	CString key;
	//开始检测队列里每个位置的信号量
	int i = 0;
	for (; i < qsize; ++i)
	{
		key.Format(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\DEV\\%d"), i);
		if (!openReg(key.GetBuffer()))
			return false;
		key.ReleaseBuffer();
		wchar_t resp[1024];
		ZeroMemory(resp, sizeof(resp));
		if (!readReg(_T("SIGNAL"), resp))
			return false;
		int signal = _wtoi(resp);
		closeReg();
		if (signal == 1)
			break;
	}
	if (i != qsize) //说明在共享队列里找到了可存储位置
	{
		*index = i;
		return true;
	}
	else
		return false;
	//默认不做存储处理
	return false;
}

bool Reader::getShareDataBufferDevPart(int* index)
{
	if (!openReg(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\DEVPART")))
		return false;
	wchar_t size[1024];
	ZeroMemory(size, sizeof(size));
	//获取共享队列的长度
	if (!readReg(_T("SIZE"), size))
		return false;
	closeReg();
	int qsize = _wtoi(size);
	CString key;
	//开始检测队列里每个位置的信号量
	int i = 0;
	for (; i < qsize; ++i)
	{
		key.Format(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\DEVPART\\%d"), i);
		if (!openReg(key.GetBuffer()))
			return false;
		key.ReleaseBuffer();
		wchar_t resp[1024];
		ZeroMemory(resp, sizeof(resp));
		if (!readReg(_T("SIGNAL"), resp))
			return false;
		int signal = _wtoi(resp);
		closeReg();
		if (signal == 1)
			break;
	}
	if (i != qsize) //说明在共享队列里找到了可存储位置
	{
		*index = i;
		return true;
	}
	else
		return false;
	//默认不做存储处理
	return false;
}

bool Reader::getShareDataBufferSNR(int* index)
{
	if (!openReg(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\SNR")))
		return false;
	wchar_t size[1024];
	ZeroMemory(size, sizeof(size));
	//获取共享队列的长度
	if (!readReg(_T("SIZE"), size))
		return false;
	closeReg();
	int qsize = _wtoi(size);
	CString key;
	//开始检测队列里每个位置的信号量
	int i = 0;
	for (; i < qsize; ++i)
	{
		key.Format(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\SNR\\%d"), i);
		if (!openReg(key.GetBuffer()))
			return false;
		key.ReleaseBuffer();
		wchar_t resp[1024];
		ZeroMemory(resp, sizeof(resp));
		if (!readReg(_T("SIGNAL"), resp))
			return false;
		int signal = _wtoi(resp);
		closeReg();
		if (signal == 1)
			break;
	}
	if (i != qsize) //说明在共享队列里找到了可存储位置
	{
		*index = i;
		return true;
	}
	else
		return false;
	//默认不做存储处理
	return false;
}