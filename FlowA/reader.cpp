#include "reader.h"
#include "typedefine.h"

Reader::Reader()
{
}

Reader::~Reader()
{

}

bool Reader::read(FlowaFile file, wchar_t* context)
{

	return true;
}

bool Reader::validFile(FlowaFile file)
{
	return true;
}

bool Reader::isNewFile(FlowaFile file)
{
	return true;
}

bool Reader::isDirtyFile(FlowaFile file)
{
	return true;
}

bool Reader::isFileReadOver(FlowaFile file)
{
	return true;
}

/*
说明： 用来更新注册表文件配置的函数
参数： 入参 要更新的文件
返回值： true成功， false失败
*/
bool Reader::updateFileStatus(FlowaFile flowafile)
{
	CString state;
	CString key;
	CString msg;
	//如果文件配置为每次从文件头开始读取,则不记录文件跳转位置
	if (flowafile.isAlwaysReadBegin == 1)
	{
		flowafile.fileSize = 0;
		flowafile.lastPos = 0;
	}
	state.Format(_T("%s|%s|%s|%d|%d|%d"), flowafile.businessType, flowafile.tranType, flowafile.fileName, flowafile.fileSize, flowafile.lastPos, flowafile.isAlwaysReadBegin);
	if (!openReg(_T("SOFTWARE\\Ebring\\Agent\\Config\\FLOWA\\FILES")))
	{
		msg.Format(_T("打开注册表失败[%s]"), _T("SOFTWARE\\Ebring\\Agent\\Config\\FLOWA\\FILES"));
		logError(msg.GetBuffer());
		return false;
	}
	key.Format(_T("FILE%d_STATE"), flowafile.index);
	if (!setReg(key.GetBuffer(), state.GetBuffer()))
	{
		msg.Format(_T("设置注册表键值失败[%s]"), state.GetBuffer());
		logError(msg.GetBuffer());
		return false;
	}
	closeReg();
	msg.Format(_T("更新文件状态，key=[FILE%d_STATE]，value=[%s]"), flowafile.index, state.GetBuffer());
	logInfo(msg.GetBuffer());
	return true;
}
