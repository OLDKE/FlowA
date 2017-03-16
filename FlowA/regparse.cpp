#include "regparse.h"

RegParse::RegParse()
{
	m_hreg = NULL;
}

RegParse::~RegParse()
{

}

bool RegParse::openReg(wchar_t *subkey)
{
	try
	{
		long ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, KEY_READ | KEY_WRITE, &m_hreg);
		if (ERROR_SUCCESS != ret)
		{
			logError(_T("RegOpenKeyEx"), ret, _T("regparse.cpp"));
			return false;
		}
	}
	catch (...)
	{
		logError(_T("OpenReg未知异常"));
		return false;
	}
	return true;
}

bool RegParse::readReg(wchar_t* key, wchar_t* value)
{
	unsigned long size;
	try
	{
		DWORD type = REG_SZ;
		long ret = RegQueryValueExW(
			m_hreg,
			key,
			0,
			&type,
			(LPBYTE)value,
			&size
			);
		if (ERROR_SUCCESS != ret)
		{
			logError(_T("RegQuery"), ret, _T("reparse.cpp"));
			return false;
		}
		
	}
	catch (...)
	{
		logError(_T("RegQuery未知异常"));
		return false;
	}
	return true;
}

bool RegParse::readReg(wchar_t* key, wchar_t* value, unsigned long* size)
{
	try
	{
		DWORD type = REG_SZ;
		long ret = RegQueryValueExW(
			m_hreg,
			key,
			0,
			&type,
			(LPBYTE)value,
			size
			);
		if (ERROR_SUCCESS != ret)
		{
			logError(_T("RegQuery"), ret, _T("reparse.cpp"));
			return false;
		}
		
	}
	catch (...)
	{
		logError(_T("RegQuery未知异常"));
		return false;
	}
	return true;
}


bool RegParse::setReg(wchar_t* key, wchar_t* value)
{
	try
	{
		long ret = RegSetValueEx(
			m_hreg,
			key,
			0,
			REG_SZ,
			(LPBYTE)value,
			((lstrlen(value))*sizeof(wchar_t))
			);
		if (ERROR_SUCCESS != ret)
		{
			logError(_T("设置注册表出错"), ret, _T("regparse.cpp"));
			return false;
		}
		
	}
	catch (...)
	{
		logError(_T("RegQuery未知异常"));
		return false;
	}
	return true;
}

bool RegParse::closeReg()
{
	try
	{
		long ret = RegCloseKey(m_hreg);
		if (ERROR_SUCCESS != ret)
		{
			logError(_T("关闭注册表失败"), ret, _T("regparse.cpp"));
			return false;
		}
		
	}
	catch (...)
	{
		logError(_T("CloseReg未知异常"));
		return false;
	}
	return true;
}