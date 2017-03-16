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
˵���� ��������ע����ļ����õĺ���
������ ��� Ҫ���µ��ļ�
����ֵ�� true�ɹ��� falseʧ��
*/
bool Reader::updateFileStatus(FlowaFile flowafile)
{
	CString state;
	CString key;
	CString msg;
	//����ļ�����Ϊÿ�δ��ļ�ͷ��ʼ��ȡ,�򲻼�¼�ļ���תλ��
	if (flowafile.isAlwaysReadBegin == 1)
	{
		flowafile.fileSize = 0;
		flowafile.lastPos = 0;
	}
	state.Format(_T("%s|%s|%s|%d|%d|%d"), flowafile.businessType, flowafile.tranType, flowafile.fileName, flowafile.fileSize, flowafile.lastPos, flowafile.isAlwaysReadBegin);
	if (!openReg(_T("SOFTWARE\\Ebring\\Agent\\Config\\FLOWA\\FILES")))
	{
		msg.Format(_T("��ע���ʧ��[%s]"), _T("SOFTWARE\\Ebring\\Agent\\Config\\FLOWA\\FILES"));
		logError(msg.GetBuffer());
		return false;
	}
	key.Format(_T("FILE%d_STATE"), flowafile.index);
	if (!setReg(key.GetBuffer(), state.GetBuffer()))
	{
		msg.Format(_T("����ע����ֵʧ��[%s]"), state.GetBuffer());
		logError(msg.GetBuffer());
		return false;
	}
	closeReg();
	msg.Format(_T("�����ļ�״̬��key=[FILE%d_STATE]��value=[%s]"), flowafile.index, state.GetBuffer());
	logInfo(msg.GetBuffer());
	return true;
}
