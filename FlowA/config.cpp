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
	说明：用来从注册表获取文件配置信息
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
	
	//获取flowa轮询时间
	if (!readReg(_T("TIMER"), timer))
		return false;
	
	m_timer = _wtoi(timer)*1000;
	msg.Format(_T("LoadConfig，日志文件读取轮循时间，TIMER=[%ss]"), timer);
	logInfo(msg.GetBuffer());
	msg.ReleaseBuffer();

	//ATMC系统的提供商，根据这个标志获取不同的解析实现类
	if (!readReg(_T("ATMC_COMPANY"), atmc))
		return false;
	msg.Format(_T("获得ATM厂商[%s]"), atmc);
	logInfo(msg.GetBuffer());
	msg.ReleaseBuffer();
	//如果是NCR的提供商
	if (StrCmpC(atmc, ATMCF_NCR) == 0)
		StrCpyW(m_atmc, atmc);
	else
	{
		msg.Format(_T("暂时不支持此ATM厂商[%s]"), atmc);
		logInfo(msg.GetBuffer());
		msg.ReleaseBuffer();
		//等待配置正确的厂商参数后，才解析文件,否则就算没有配置也不退出flowa
		//return false;
	}
	closeReg();
	//获取需要读取的文件配置信息
	if (!openReg(_T("SOFTWARE\\EBRING\\Agent\\Config\\FLOWA\\FILES")))
		return false;
	if (!readReg(_T("FILE_COUNT"), fileCount))
		return false;
	if (StrCmpW(fileCount, _T("")) != 0)
	{
		m_fileCount = _wtoi(fileCount);
		msg.Format(_T("LoadConfig，需要分析的文件数，FILE_COUNT=[%d]"), m_fileCount);
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
			wsprintfW(message, TEXT("业务类型[%s]日志解析模式[%s]上次分析文件名[%s]上次文件大小[%s]上次读取位置[%s]循环读取标志[%s]"), m_config[0], m_config[1], m_config[2], m_config[3], m_config[4], m_config[5]);
			logInfo(message);
			m_flowaFile[i].index = fileindex;
			StrCpyW(m_flowaFile[i].businessType, m_config[0]);	//拿到配置里的业务配置
			StrCpyW(m_flowaFile[i].pattern, m_config[1]);		//文件解析需要的正则表达式
			StrCpyW(m_flowaFile[i].last_fileName, m_config[2]);	//上次读过的文件名
			m_flowaFile[i].last_fileSize = _wtoi(m_config[3]);	//上次文件的大小
			m_flowaFile[i].lastPos = _wtoi(m_config[4]);		//上次文件的指针位置
			m_flowaFile[i].isAlwaysReadBegin = _wtoi(m_config[5]);	//文件头重复读标志
			m_flowaFile[i].sharedPos = -1; //标识共享队列里该文件处理过后数据存放的位置
			//根据文件配置判断业务类型
			if ((StrCmpW(m_flowaFile[i].businessType, BTYPE_TRN) != 0) &&
				(StrCmpW(m_flowaFile[i].businessType, BTYPE_RTC) != 0) &&
				(StrCmpW(m_flowaFile[i].businessType, BTYPE_STATE) != 0) &&
				(StrCmpW(m_flowaFile[i].businessType, BTYPE_HARDWARE) != 0) &&
				(StrCmpW(m_flowaFile[i].businessType, BTYPE_HARDPART) != 0) &&
				(StrCmpW(m_flowaFile[i].businessType, BTYPE_SNR) != 0)
				)
			{
				msg.Format(_T("暂时不支持此业务类型[%s]"), m_flowaFile[i].businessType);
				logInfo(msg.GetBuffer());
				msg.ReleaseBuffer();
				return false;
			}
			//根据文件配置，获取文件的全路径名
			key.Format(_T("FILE%d_PATH"), fileindex);
			if (!readReg(key.GetBuffer(), m_fileAbsPath))
				return false;
			key.ReleaseBuffer();
			getDynamicFileName(m_fileAbsPath, m_flowaFile[i].filePath);
			m_flowaFile[i].fileSize = getFileSize(m_flowaFile[i].filePath);
			if (0 == m_flowaFile[i].fileSize)
			{
				msg.Format(_T("[%s]文件不存在"), m_flowaFile[i].filePath);
				logInfo(msg.GetBuffer());
				msg.ReleaseBuffer();
				//即使要读的文件不存在也不让flowa退出，直到文件出现。
				//return false;
			}
			getFileName(m_flowaFile[i].filePath, m_flowaFile[i].fileName);
		}
	}
	else
	{
		msg.Format(_T("FileCount不应该设置为空"));
		msg.ReleaseBuffer();
		return false;
	}
	logInfo(_T("文件配置加载完成"));
	closeReg();
	return true;
}

/*
*	说明：由注册表里Flowa文件配置里的文件名模式，获取对应日期的动态文件名
*	参数：regdatecfg 入参 文件路径配置里的日期文件名模式
*	参数：filename	出参 按照给定日期模式输出的文件名
*	作者：任康	2017/03/15
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
*	说明：字符串分割
*	参数：src	入参 要分割的字符串
*	参数：delim	入参 分隔符
*	参数：res	出参 按分隔符分割后存放的结果数组
*	参数：ressize 入参 需要分隔的次数
*	作者：任康	2017/03/15
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

