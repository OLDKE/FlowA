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
	//1.�ж��ļ��Ƿ���ڣ�����������򲻽��к����ļ�����
	if (!isFileExists(file->filePath))
		return false;
	//2.�ж�atm�Ƿ��������־����
	//������µ���־�ļ�����ע����Ӧ�ļ����ø���
	if (isNewFile(file))
	{
		file->lastPos = 0;
		file->last_fileSize = 0;
		msg.Format(_T("�ϴη����ļ���[%s]---�仯-->[%s]"), file->last_fileName,file->fileName);
		logInfo(msg.GetBuffer());
		StrCpyW(file->last_fileName, file->fileName);
	}
	//3.��ʾ��ǰ�ļ����û����������У��ʧ�ܣ������к���������ǰ�ļ�����һ�ζ�ȡʱû�иı䣬��������
	if (isNotDirtyFile(file))
		return false;
	//4.��ǰ�ļ�����������׷��ʱ(��ʾ������)��������ȡ��
	return true;
}

bool Reader::isNewFile(FlowaFile* file)
{
	//�����һ�δ�����ļ�������δ�����ļ�������ͬ����˵���ļ����ı�
	if (StrCmpW(file->last_fileName, file->fileName) != 0)
		return true;
	return false;
}

//����ֵ��	true �ļ��Ѿ�������ϣ� false�ļ�û�д������
bool Reader::isNotDirtyFile(FlowaFile* file)
{
	CString msg;
	//���Ϊÿ���ظ���ȡ����ֱ�ӷ��ؼ�������
	if (file->isAlwaysReadBegin == 1)
	{
		msg.Format(_T("���´�[%s]�ļ�ͷ��ȡ�ļ�״̬"), file->filePath);
		logInfo(msg.GetBuffer());
		return false;
	}
	
	//����ϴδ�����ļ���С�������ϴε��ļ�ָ��λ�ã�˵��������׷�ӣ��ļ�δ�����꣬���������ϴ��ļ�
	if (file->last_fileSize > file->lastPos)
	{
		msg.Format(_T("�ļ�[%s]δ�����꣬��������"), file->filePath);
		logInfo(msg.GetBuffer());
		return false;
	}
	//����ļ���СС���ϴ��ļ�ָ���λ�ã�˵�������쳣������������������
	//�ϴ��ļ���С�����ϴε��ļ�λ��ָ�룬˵���ļ��Ѿ���ȡ��ϣ������к����ļ�����
	if (file->last_fileSize <= file->lastPos && file->last_fileSize != 0)
	{
		msg.Format(_T("�ļ�[%s]�Ѿ����꣬�����к�������"), file->filePath);
		logInfo(msg.GetBuffer());
		return true;
	}
	return false;
}

/*
˵���� ��������ע����ļ����õĺ���
������ ��� Ҫ���µ��ļ�
����ֵ�� true�ɹ��� falseʧ��
*/
bool Reader::updateFileStatus(FlowaFile* flowafile)
{
	CString state;
	CString key;
	CString msg;

	//����ļ�����Ϊÿ�δ��ļ�ͷ��ʼ��ȡ,�򲻼�¼�ļ���תλ��
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
	
	//2.������һ�δ�����ϢΪ��ǰ�ļ�״̬
	flowafile->last_fileSize = flowafile->fileSize;
	StrCpyW(flowafile->last_fileName, flowafile->fileName);
	state.Format(_T("%s|%s|%s|%lld|%lld|%d"), flowafile->businessType, flowafile->pattern, flowafile->fileName, flowafile->fileSize, flowafile->lastPos, flowafile->isAlwaysReadBegin);
	if (!openReg(_T("SOFTWARE\\Ebring\\Agent\\Config\\FLOWA\\FILES")))
	{
		msg.Format(_T("��ע���ʧ��[%s]"), _T("SOFTWARE\\Ebring\\Agent\\Config\\FLOWA\\FILES"));
		logError(msg.GetBuffer());
		return false;
	}
	key.Format(_T("FILE%d_STATE"), flowafile->index);
	if (!setReg(key.GetBuffer(), state.GetBuffer()))
	{
		msg.Format(_T("����ע����ֵʧ��[%s]"), state.GetBuffer());
		logError(msg.GetBuffer());
		return false;
	}
	closeReg();
	msg.Format(_T("�����ļ�״̬��key=[FILE%d_STATE]��value=[%s]"), flowafile->index, state.GetBuffer());
	logInfo(msg.GetBuffer());
	msg.ReleaseBuffer();
	return true;
}

//1.����agent�Ĺ�������Ƿ���λ�ÿ��Դ�����ݣ�
//��������������ź�����־��Ϊ1��ʾ��1��ʾ�Ա�agent�����ٽ�����û���ͷţ�Agent��û�����ͣ�
//�򱾴��ļ�״̬�����£����ײ������´����¶�ȡ����
bool Reader::isFree(FlowaFile *flowafile)
{
	if (flowafile->isAlwaysReadBegin == 1)
	{
		//���Ϊÿ���ظ���ȡ���ļ��������ж϶����Ƿ�Ϊ����Ĭ�ϸ��ǹ�����еĵ�һ��λ�õ�����
		flowafile->sharedPos = 0;
		return true;
	}
	
	if (StrCmpW(flowafile->businessType, BTYPE_TRN) == 0) //����ҵ��
	{
		int pos;
		if (!getShareDataBufferTrn(&pos))
		{
			flowafile->sharedPos = -1;
			return false;
		}
		//����ǰ������ļ�����ָ��Ҫ�洢�ڶ��е�λ��
		flowafile->sharedPos = pos;
	}
	else if (StrCmpW(flowafile->businessType, BTYPE_HARDWARE) == 0) //�豸���
	{
		int pos;
		if (!getShareDataBufferDev(&pos))
		{
			flowafile->sharedPos = -1;
			return false;
		}
		
		//����ǰ������ļ�����ָ��Ҫ�洢�ڶ��е�λ��
		flowafile->sharedPos = pos;
	}
	else if (StrCmpW(flowafile->businessType, BTYPE_HARDPART) == 0) //�豸����
	{
		int pos;
		if (!getShareDataBufferDevPart(&pos))
		{
			flowafile->sharedPos = -1;
			return false;
		}
		
		//����ǰ������ļ�����ָ��Ҫ�洢�ڶ��е�λ��
		flowafile->sharedPos = pos;
	}
	else if (StrCmpW(flowafile->businessType, BTYPE_SNR) == 0) //���ֺ�
	{
		int pos;
		if (!getShareDataBufferSNR(&pos))
		{
			flowafile->sharedPos = -1;
			return false;
		}
		
		//����ǰ������ļ�����ָ��Ҫ�洢�ڶ��е�λ��
		flowafile->sharedPos = pos;
	}
	
	return true;
}

/*
˵���� ��д��ģʽ�� ��⹲����е��ź�����־������Ͷ��ߵĹ���������п���λ�ã��ź���Ϊ1�����ѣ����򷵻ش�λ�õ��±ꡣ
����	: ������п���λ�õ��±�
����ֵ��	true ����δ�������Լ������������������
����ֵ�� false ���������������Լ�����������׷�����ݣ��ȴ�������ȥ����
*/
bool Reader::getShareDataBufferTrn(int* index)
{
	if (!openReg(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\TRN")))
		return false;
	wchar_t size[1024];
	ZeroMemory(size, sizeof(size));
	//��ȡ������еĳ���
	if (!readReg(_T("SIZE"), size))
		return false;
	closeReg();
	int qsize = _wtoi(size);
	CString key;
	//��ʼ��������ÿ��λ�õ��ź���
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
	if (i != qsize) //˵���ڹ���������ҵ��˿ɴ洢λ��
	{
		*index = i;
		return true;
	}
	else
		return false;
	//Ĭ�ϲ����洢����
	return false;
}

bool Reader::getShareDataBufferDev(int* index)
{	
	if (!openReg(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\DEV")))
		return false;
	wchar_t size[1024];
	ZeroMemory(size, sizeof(size));
	//��ȡ������еĳ���
	if (!readReg(_T("SIZE"), size))
		return false;
	closeReg();
	int qsize = _wtoi(size);
	CString key;
	//��ʼ��������ÿ��λ�õ��ź���
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
	if (i != qsize) //˵���ڹ���������ҵ��˿ɴ洢λ��
	{
		*index = i;
		return true;
	}
	else
		return false;
	//Ĭ�ϲ����洢����
	return false;
}

bool Reader::getShareDataBufferDevPart(int* index)
{
	if (!openReg(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\DEVPART")))
		return false;
	wchar_t size[1024];
	ZeroMemory(size, sizeof(size));
	//��ȡ������еĳ���
	if (!readReg(_T("SIZE"), size))
		return false;
	closeReg();
	int qsize = _wtoi(size);
	CString key;
	//��ʼ��������ÿ��λ�õ��ź���
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
	if (i != qsize) //˵���ڹ���������ҵ��˿ɴ洢λ��
	{
		*index = i;
		return true;
	}
	else
		return false;
	//Ĭ�ϲ����洢����
	return false;
}

bool Reader::getShareDataBufferSNR(int* index)
{
	if (!openReg(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\MESSAGES\\SNR")))
		return false;
	wchar_t size[1024];
	ZeroMemory(size, sizeof(size));
	//��ȡ������еĳ���
	if (!readReg(_T("SIZE"), size))
		return false;
	closeReg();
	int qsize = _wtoi(size);
	CString key;
	//��ʼ��������ÿ��λ�õ��ź���
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
	if (i != qsize) //˵���ڹ���������ҵ��˿ɴ洢λ��
	{
		*index = i;
		return true;
	}
	else
		return false;
	//Ĭ�ϲ����洢����
	return false;
}