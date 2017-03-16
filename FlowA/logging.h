#ifndef __LOGGING_H__
#define __LOGGING_H__
/****************************************************
*	˵����һ��������¼��־���Զ����࣬������Ҫ�����޸�(������������)
*	���ߣ��ο�
*	ʱ�䣺2017/03/13
*****************************************************/
// �궨��
#define LOG_FATAL       0     // ���ش���
#define LOG_ERROR       1     // һ�����
#define LOG_WARN        2     // ����
#define LOG_INFO        3     // һ����Ϣ
#define LOG_TRACE       4     // ������Ϣ
#define LOG_DEBUG       5     // ������Ϣ
#define LOG_ALL         6     // ������Ϣ

#include <cstdio>
using namespace std;

class Logging{
public:
	Logging();
	~Logging();
public:
	void log(int iLogLevel, wchar_t* pszContent, wchar_t* model);
	void logDebug(wchar_t* pszContent, wchar_t* model=NULL);
	void logInfo(wchar_t* pszContent, wchar_t* model=NULL);
	void logError(wchar_t* pszContent, wchar_t* model=NULL);
	void logError(wchar_t *msg, long errcode, wchar_t* model = NULL);
	void now(wchar_t *pszTimeStr);
	wchar_t* logLevel(int iLogLevel);
public:
	wchar_t m_szConfigFile[128];
	wchar_t m_szLogContent[1024];
	wchar_t m_szLogDir[128];
	wchar_t m_szLogFile[255];
	int m_iLoopFlag;
	int m_iLogLevel;
};
#endif