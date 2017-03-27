#include "logging.h"
#include "stdafx.h"
#include "typedefine.h"

Logging::Logging()
{
	USES_CONVERSION;
	// ��ȡ�����ļ�ȫ·��(�����ļ���)
	GetCurrentDirectory(sizeof(m_szConfigFile) - 1, m_szConfigFile);
	StrCatW(m_szConfigFile, A2T("\\logconfig.ini"));

	// ��־�ȼ�
	m_iLogLevel = GetPrivateProfileInt(A2T("LOG"), A2T("LogLevel"), 3, m_szConfigFile);

	// ��־�ļ����Ŀ¼
	GetPrivateProfileString(A2T("LOG"), A2T("LogDir"), A2T(""), m_szLogDir, sizeof(m_szLogDir), m_szConfigFile);
	wnsprintf(m_szLogFile, sizeof(m_szLogFile) - 1, A2T("%s\\run.log"), m_szLogDir);
	TRACE(A2T("[%s]"), m_szLogFile);
}

Logging::~Logging()
{
}

void Logging::log(int iLogLevel, wchar_t* pszContent, wchar_t* model)
{
	USES_CONVERSION;
	FILE  *fp = NULL;
	wchar_t  szLogContent[CHUNKSIZE + 1] = { 0 };
	wchar_t  szTimeStr[128] = { 0 };


	if (pszContent == NULL)
	{
		return;
	}

	wchar_t message[CHUNKSIZE+1] = { 0x00 };
	StrCpyW(message, pszContent);
	// ������־�ȼ�
	if (iLogLevel > m_iLogLevel)
	{
		return;
	}


	fp = fopen(T2A(m_szLogFile), "at+");      // ���ļ�, ÿ��д���ʱ���ں���׷��
	if (fp == NULL)
	{
		return;
	}


	// д����־ʱ��
	now(szTimeStr);
	fputs(T2A(szTimeStr), fp);


	// д����־����
	// ��ԭ�����������־�ȼ���ʶ
	wnsprintf(szLogContent, sizeof(szLogContent) - 1, A2T("[%s][%s]%s\n\n"), model, logLevel(iLogLevel), message);
	fputs(T2A(szLogContent), fp);

	fflush(fp);     // ˢ���ļ�
	fclose(fp);     // �ر��ļ�
	fp = NULL;      // ���ļ�ָ����Ϊ��


	return;

}


wchar_t* Logging::logLevel(int iLogLevel)
{
	USES_CONVERSION;
	switch (iLogLevel)
	{
	case LOG_FATAL:
	{
		return A2T("FATAL");
	}
	case LOG_ERROR:
	{
		return A2T("ERROR");
	}
	case LOG_WARN:
	{
		return A2T("WARN");
	}
	case LOG_INFO:
	{
		return A2T("INFO");
	}
	case LOG_TRACE:
	{
		return _T("TRACE");
	}
	case LOG_DEBUG:
	{
		return _T("DEBUG");
	}
	case LOG_ALL:
	{
		return _T("ALL");
	}
	default:
	{
		return _T("OTHER");
	}
	}
}

void Logging::now(wchar_t* pszTimeStr)
{
	SYSTEMTIME  tSysTime = { 0 };

	USES_CONVERSION;
	GetLocalTime(&tSysTime);
	wsprintf(pszTimeStr, A2T("=============================================[%04d/%02d/%02d %02d:%02d:%02d.%03d]"),
		tSysTime.wYear, tSysTime.wMonth, tSysTime.wDay,
		tSysTime.wHour, tSysTime.wMinute, tSysTime.wSecond,
		tSysTime.wMilliseconds);
	return;
}

void Logging::logDebug(wchar_t* pszContent, wchar_t *model)
{
	USES_CONVERSION;
	FILE  *fp = NULL;
	wchar_t  szLogContent[CHUNKSIZE + 1] = { 0 };
	wchar_t  szTimeStr[128] = { 0 };
	
	if (NULL == model)
		model = A2T("logging.cpp");

	if (pszContent == NULL)
	{
		return;
	}

	wchar_t message[CHUNKSIZE+1] = { 0x00 };
	StrCpyW(message, pszContent);
	// ������־�ȼ�
	if (LOG_DEBUG > m_iLogLevel)
	{
		return;
	}


	fp = fopen(T2A(m_szLogFile), "at+");      // ���ļ�, ÿ��д���ʱ���ں���׷��
	if (fp == NULL)
	{
		return;
	}


	// д����־ʱ��
	now(szTimeStr);
	fputs(T2A(szTimeStr), fp);


	// д����־����
	// ��ԭ�����������־�ȼ���ʶ
	wnsprintf(szLogContent, sizeof(szLogContent) - 1, A2T("[%s][%s]%s\n"), model, logLevel(LOG_DEBUG), message);
	fputs(T2A(szLogContent), fp);

	fflush(fp);     // ˢ���ļ�
	fclose(fp);     // �ر��ļ�
	fp = NULL;      // ���ļ�ָ����Ϊ��


	return;

}

void Logging::logInfo(wchar_t* pszContent, wchar_t *model)
{
	USES_CONVERSION;
	FILE  *fp = NULL;
	wchar_t  szLogContent[CHUNKSIZE+1] = { 0 };
	wchar_t  szTimeStr[128] = { 0 };

	if (NULL == model)
		model = A2T("logging.cpp");

	if (pszContent == NULL)
	{
		return;
	}

	wchar_t message[CHUNKSIZE+1];
	StrCpyW(message, pszContent);
	// ������־�ȼ�
	if (LOG_INFO > m_iLogLevel)
	{
		return;
	}


	fp = fopen(T2A(m_szLogFile), "at+");      // ���ļ�, ÿ��д���ʱ���ں���׷��
	if (fp == NULL)
	{
		return;
	}


	// д����־ʱ��
	now(szTimeStr);
	fputs(T2A(szTimeStr), fp);


	// д����־����
	// ��ԭ�����������־�ȼ���ʶ
	wnsprintf(szLogContent, sizeof(szLogContent) - 1, A2T("[%s][%s]=============================================\n%s\n"), model, logLevel(LOG_INFO), message);
	fputs(T2A(szLogContent), fp);

	fflush(fp);     // ˢ���ļ�
	fclose(fp);     // �ر��ļ�
	fp = NULL;      // ���ļ�ָ����Ϊ��
	return;

}

void Logging::logError(wchar_t* pszContent, wchar_t *model)
{
	USES_CONVERSION;
	FILE  *fp = NULL;
	wchar_t  szLogContent[CHUNKSIZE + 1] = { 0 };
	wchar_t  szTimeStr[128] = { 0 };

	if (NULL == model)
		model = A2T("logging.cpp");

	if (pszContent == NULL)
	{
		return;
	}

	wchar_t message[CHUNKSIZE+1] = { 0x00 };
	StrCpyW(message, pszContent);
	// ������־�ȼ�
	if (LOG_ERROR > m_iLogLevel)
	{
		return;
	}


	fp = fopen(T2A(m_szLogFile), "at+");      // ���ļ�, ÿ��д���ʱ���ں���׷��
	if (fp == NULL)
	{
		return;
	}


	// д����־ʱ��
	now(szTimeStr);
	fputs(T2A(szTimeStr), fp);


	// д����־����
	// ��ԭ�����������־�ȼ���ʶ
	wnsprintf(szLogContent, sizeof(szLogContent) - 1, A2T("[%s][%s]%s\n"), model, logLevel(LOG_ERROR), message);
	fputs(T2A(szLogContent), fp);

	fflush(fp);     // ˢ���ļ�
	fclose(fp);     // �ر��ļ�
	fp = NULL;      // ���ļ�ָ����Ϊ��
	return;

}

void Logging::logError(wchar_t *msg, long errcode, wchar_t* model)
{
	LPVOID lpMsgBuf;
	wchar_t szBuf[128];

	FormatMessageW(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
		);
	wsprintf(
		szBuf,
		_T("%s ������Ϣ (������[%d]): %s"),
		msg,
		errcode,
		lpMsgBuf
		);
	logError(szBuf, model);
	LocalFree(lpMsgBuf);
}
