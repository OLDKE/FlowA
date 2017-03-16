#ifndef __LOGGING_H__
#define __LOGGING_H__
/****************************************************
*	说明：一个用来记录日志的自定义类，根据需要自行修改(最讨厌造轮子)
*	作者：任康
*	时间：2017/03/13
*****************************************************/
// 宏定义
#define LOG_FATAL       0     // 严重错误
#define LOG_ERROR       1     // 一般错误
#define LOG_WARN        2     // 警告
#define LOG_INFO        3     // 一般信息
#define LOG_TRACE       4     // 跟踪信息
#define LOG_DEBUG       5     // 调试信息
#define LOG_ALL         6     // 所有信息

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