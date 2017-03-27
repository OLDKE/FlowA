#include "ncrstoringadapter.h"
#include "stdafx.h"

bool NCRStoringAdapter::storing(FlowaFile* file, wchar_t* context)
{
	if (NULL == file || context == NULL)
		return false;
	CString msg;
	if (file->sharedPos == -1)
	{
		msg.Format(_T("��ǰ��������������ȴ�Agent���͡����β�����[%s]���ͽ���"), file->businessType);
		logInfo(msg.GetBuffer());
		return false;
	}
		
	//sharedPos��ʾ���ù�����е�λ�ã�����������˱�־Ϊ-1����ν��ײ�����
	//�ж�ҵ�����ͣ����洢
	CString key;
	if (StrCmpW(file->businessType, BTYPE_TRN) == 0) //����
	{
		key.Format(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\TRN\\%d"), file->sharedPos);
	}
	else if (StrCmpW(file->businessType, BTYPE_HARDPART) == 0) //�豸����
	{
		key.Format(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\DEVPART\\%d"), file->sharedPos);
	}
	else if (StrCmpW(file->businessType, BTYPE_HARDWARE) == 0) //�豸����
	{
		key.Format(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\DEV\\%d"), file->sharedPos);
	}
	else if (StrCmpW(file->businessType, BTYPE_SNR) == 0) //���ֺ�
	{
		key.Format(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\SNR\\%d"), file->sharedPos);
	}
	else
		return false;
	if (!openReg(key.GetBuffer()))
		return false;
	if (!setReg(_T("PACKET"), context))
		return false;
	//�ͷ��ź���
	if (!setReg(_T("SIGNAL"), _T("0")))
		return false;
	closeReg();
	msg.Format(_T("���δ洢[%s]���ͽ��׳ɹ�"), file->businessType);
	logInfo(msg.GetBuffer());
	return true;
}