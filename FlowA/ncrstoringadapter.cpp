#include "ncrstoringadapter.h"
#include "stdafx.h"

bool NCRStoringAdapter::storing(FlowaFile* file, wchar_t* context)
{
	if (NULL == file || context == NULL)
		return false;
	CString msg;
	if (file->sharedPos == -1)
	{
		msg.Format(_T("当前共享队列已满，等待Agent上送。本次不处理[%s]类型交易"), file->businessType);
		logInfo(msg.GetBuffer());
		return false;
	}
		
	//sharedPos表示可用共享队列的位置，如果队列满此标志为-1。这次交易不处理
	//判断业务类型，并存储
	CString key;
	if (StrCmpW(file->businessType, BTYPE_TRN) == 0) //交易
	{
		key.Format(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\TRN\\%d"), file->sharedPos);
	}
	else if (StrCmpW(file->businessType, BTYPE_HARDPART) == 0) //设备部件
	{
		key.Format(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\DEVPART\\%d"), file->sharedPos);
	}
	else if (StrCmpW(file->businessType, BTYPE_HARDWARE) == 0) //设备整体
	{
		key.Format(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\DEV\\%d"), file->sharedPos);
	}
	else if (StrCmpW(file->businessType, BTYPE_SNR) == 0) //冠字号
	{
		key.Format(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\SNR\\%d"), file->sharedPos);
	}
	else
		return false;
	if (!openReg(key.GetBuffer()))
		return false;
	if (!setReg(_T("PACKET"), context))
		return false;
	//释放信号量
	if (!setReg(_T("SIGNAL"), _T("0")))
		return false;
	closeReg();
	msg.Format(_T("本次存储[%s]类型交易成功"), file->businessType);
	logInfo(msg.GetBuffer());
	return true;
}