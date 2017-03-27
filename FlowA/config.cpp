#include "config.h"

Config::Config()
{
	wchar_t fileCount[128];
	ZeroMemory(m_atmc, sizeof(m_atmc));
	ZeroMemory(m_fileconfig, sizeof(m_fileconfig));
	m_config = new wchar_t*[6];
	for (int i = 0; i < 6; i++)
		m_config[i] = new wchar_t[1024];
	m_fileAbsPath = new wchar_t[2048];
	openReg(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\FILES"));
	ZeroMemory(fileCount, sizeof(fileCount));
	readReg(_T("FILE_COUNT"), fileCount);
	m_fileCount = _wtoi(fileCount);
	closeReg();
	m_flowaFile = new FlowaFile[m_fileCount]();
	ZeroMemory(m_flowaFile, sizeof(m_flowaFile));
	
}

Config::~Config()
{
	for (int i = 0; i < 6; i++)
	{
		delete[] m_config[i];
	}
	delete[] m_flowaFile;
	delete[] m_fileAbsPath;
}

/*
	˵����������ע����ȡ�ļ�������Ϣ
*/
bool Config::loadConfig()
{
	wchar_t timer[128];
	wchar_t atmc[255];
	wchar_t fileCount[128];
	CString msg;
	USES_CONVERSION;

	if (!openReg(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA")))
		return false;
	
	//��ȡflowa��ѯʱ��
	if (!readReg(_T("TIMER"), timer))
		return false;
	
	m_timer = _wtoi(timer)*1000;
	msg.Format(_T("LoadConfig����־�ļ���ȡ��ѭʱ�䣬TIMER=[%ss]"), timer);
	logInfo(msg.GetBuffer());
	msg.ReleaseBuffer();

	//ATMCϵͳ���ṩ�̣����������־��ȡ��ͬ�Ľ���ʵ����
	if (!readReg(_T("ATMC_COMPANY"), atmc))
		return false;
	msg.Format(_T("���ATM����[%s]"), atmc);
	logInfo(msg.GetBuffer());
	msg.ReleaseBuffer();
	//�����NCR���ṩ��
	if (StrCmpC(atmc, ATMCF_NCR) == 0)
		StrCpyW(m_atmc, atmc);
	else
	{
		msg.Format(_T("��ʱ��֧�ִ�ATM����[%s]"), atmc);
		logInfo(msg.GetBuffer());
		msg.ReleaseBuffer();
		//�ȴ�������ȷ�ĳ��̲����󣬲Ž����ļ�,�������û������Ҳ���˳�flowa
		//return false;
	}
	closeReg();
	//��ȡ��Ҫ��ȡ���ļ�������Ϣ
	if (!openReg(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\FILES")))
		return false;
	if (!readReg(_T("FILE_COUNT"), fileCount))
		return false;
	if (StrCmpW(fileCount, _T("")) != 0)
	{
		m_fileCount = _wtoi(fileCount);
		msg.Format(_T("LoadConfig����Ҫ�������ļ�����FILE_COUNT=[%d]"), m_fileCount);
		logInfo(msg.GetBuffer());
		msg.ReleaseBuffer();
		for (int i = 0; i < m_fileCount; ++i)
		{
			int fileindex = i + 1;
			CString	key;
			key.Format(_T("FILE%d_STATE"), fileindex);
			if (!readReg(key.GetBuffer(), m_fileconfig))
				return false;
			key.ReleaseBuffer();
			msg.Format(_T("%s"), m_fileconfig);
			logInfo(msg.GetBuffer());
			msg.ReleaseBuffer();
			split(m_fileconfig, _T("|"), m_config, 6);
			wchar_t message[1024] = { 0x00 };
			wsprintfW(message, TEXT("ҵ������[%s]��־����ģʽ[%s]�ϴη����ļ���[%s]�ϴ��ļ���С[%s]�ϴζ�ȡλ��[%s]ѭ����ȡ��־[%s]"), m_config[0], m_config[1], m_config[2], m_config[3], m_config[4], m_config[5]);
			logInfo(message);
			m_flowaFile[i].index = fileindex;
			StrCpyW(m_flowaFile[i].businessType, m_config[0]);	//�õ��������ҵ������
			StrCpyW(m_flowaFile[i].pattern, m_config[1]);		//�ļ�������Ҫ��������ʽ
			StrCpyW(m_flowaFile[i].last_fileName, m_config[2]);	//�ϴζ������ļ���
			m_flowaFile[i].last_fileSize = _wtoi(m_config[3]);	//�ϴ��ļ��Ĵ�С
			m_flowaFile[i].lastPos = _wtoi(m_config[4]);		//�ϴ��ļ���ָ��λ��
			m_flowaFile[i].isAlwaysReadBegin = _wtoi(m_config[5]);	//�ļ�ͷ�ظ�����־
			m_flowaFile[i].sharedPos = -1; //��ʶ�����������ļ�����������ݴ�ŵ�λ��
			//�����ļ������ж�ҵ������
			if ((StrCmpW(m_flowaFile[i].businessType, BTYPE_TRN) != 0) &&
				(StrCmpW(m_flowaFile[i].businessType, BTYPE_RTC) != 0) &&
				(StrCmpW(m_flowaFile[i].businessType, BTYPE_STATE) != 0) &&
				(StrCmpW(m_flowaFile[i].businessType, BTYPE_HARDWARE) != 0) &&
				(StrCmpW(m_flowaFile[i].businessType, BTYPE_HARDPART) != 0) &&
				(StrCmpW(m_flowaFile[i].businessType, BTYPE_SNR) != 0)
				)
			{
				msg.Format(_T("��ʱ��֧�ִ�ҵ������[%s]"), m_flowaFile[i].businessType);
				logInfo(msg.GetBuffer());
				msg.ReleaseBuffer();
				return false;
			}
			//�����ļ����ã���ȡ�ļ���ȫ·����
			key.Format(_T("FILE%d_PATH"), fileindex);
			if (!readReg(key.GetBuffer(), m_fileAbsPath))
				return false;
			key.ReleaseBuffer();
			getDynamicFileName(m_fileAbsPath, m_flowaFile[i].filePath);
			m_flowaFile[i].fileSize = getFileSize(m_flowaFile[i].filePath);
			if (0 == m_flowaFile[i].fileSize)
			{
				msg.Format(_T("[%s]�ļ�������"), m_flowaFile[i].filePath);
				logInfo(msg.GetBuffer());
				msg.ReleaseBuffer();
				//��ʹҪ�����ļ�������Ҳ����flowa�˳���ֱ���ļ����֡�
				//return false;
			}
			getFileName(m_flowaFile[i].filePath, m_flowaFile[i].fileName);
		}
	}
	else
	{
		msg.Format(_T("FileCount��Ӧ������Ϊ��"));
		msg.ReleaseBuffer();
		return false;
	}
	logInfo(_T("�ļ����ü������"));
	closeReg();
	return true;
}

/*
*	˵������ע�����Flowa�ļ���������ļ���ģʽ����ȡ��Ӧ���ڵĶ�̬�ļ���
*	������regdatecfg ��� �ļ�·��������������ļ���ģʽ
*	������filename	���� ���ո�������ģʽ������ļ���
*	���ߣ��ο�	2017/03/15
*/
void Config::getDynamicFileName(wchar_t *regdatecfg, wchar_t* filename)
{
	if (NULL == regdatecfg||filename == NULL)
		return;
	CTime time = CTime::GetCurrentTime();
	CString pattern(regdatecfg);
	pattern.Replace(_T("%Y%M%D"), time.Format(_T("%Y%m%d")));
	StrCpyW(filename, pattern.GetBuffer());
}

/*
*	˵�����ַ����ָ�
*	������src	��� Ҫ�ָ���ַ���
*	������delim	��� �ָ���
*	������res	���� ���ָ����ָ���ŵĽ������
*	������ressize ��� ��Ҫ�ָ��Ĵ���
*	���ߣ��ο�	2017/03/15
*/
void Config::split(wchar_t* src, wchar_t* delim, wchar_t** res, int ressize)
{
	USES_CONVERSION;
	if (NULL == src || *res == NULL)
		return;
	char* p = strtok(T2A(src), T2A(delim));
	StrCpyW(res[0], A2T(p));
	int i = 1;
	while (p && i<ressize)
	{
		p = strtok(NULL, T2A(delim));
		if (NULL == p)
			StrCpyW(res[i], A2T(""));
		else
			StrCpyW(res[i], A2T(p));
		++i;
	}
}

