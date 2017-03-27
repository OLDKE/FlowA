#include "ncrreadadapter.h"
#include "typedefine.h"
#include "normalreader.h"
#include "regexparse.h"
#include "config.h"
#include "serialnum.h" 

NCRReadAdapter::NCRReadAdapter()
{
	m_reader = new NormalReader();
}

NCRReadAdapter::~NCRReadAdapter()
{
	delete m_reader;
}

bool NCRReadAdapter::read(FlowaFile* file, wchar_t* context)
{
	m_reader->read(file, context);
	//�����ļ��������жϣ��Ӷ�������Ӧ�Ĵ���
	if (StrCmpW(file->businessType, BTYPE_SNR) == 0)
		this->getContextBlock(file, context, NULL);
	return (lstrlenW(context) > 0);
}

bool NCRReadAdapter::getContextBlock(FlowaFile* file, wchar_t* context, wchar_t* pattern)
{
	//�����ֺ��ļ��е�һ����Ϣ���зָ�
	Config cf;
	SerialNum SN;
	wchar_t** m_config;
	wchar_t** serialnumber;
	wchar_t** refusenumber;
	wchar_t* div;
	m_config = new wchar_t*[6];
	serialnumber = new wchar_t*[100];
	refusenumber = new wchar_t*[100];
	for (int i = 0; i < 6; i++)
	{
		m_config[i] = new wchar_t[1024];
		serialnumber[i] = new wchar_t[30];
		refusenumber[i] = new wchar_t[30];
	}


	cf.split(context, _T("|"), m_config, 6);
	USES_CONVERSION;
	char temp[CHUNKSIZE];
	ZeroMemory(temp, sizeof(temp));

	//ȡ����
	{
		div = A2T("(\\d+)(?!\\|)");
		RegexPaser regex(div);
		if (regex.search(T2A(m_config[0]), temp))
			StrCpyW(SN.Card, A2T(temp));
	}

	//ȡ��ˮ��
	{
		div = A2T("(\\d+)(?!\\|)");
		RegexPaser regex(div);
		if (regex.search(T2A(m_config[1]), temp))
			StrCpyW(SN.SNcode, A2T(temp));
	}

	//ȡ����,ȡʱ��
	{
		CString sTime = m_config[2];
		TCHAR * charTime = (TCHAR*)(LPCTSTR)sTime;
		CString sFormat = _T("%d-%d-%d %d:%d:%d");
		TCHAR * charFormat = (TCHAR*)(LPCTSTR)sFormat;
		int nYear, nMonth, nDate, nHour, nMin, nSec;
		_stscanf(charTime, charFormat, &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);
		CTime t(nYear, nMonth, nDate, nHour, nMin, nSec);
		CString s = t.Format(_T("%Y%m%d%H%M%S"));
		StrCpyW(SN.Date, s.Left(8));
		StrCpyW(SN.Time, s.Right(6));
	}

	//ȡ��������,//ȡ���׽��
	{
		CString tran = m_config[3];
		tran.Trim();
		int kg = tran.Find(' ');
		StrCpyW(SN.TranType, tran.Left(kg));
		StrCpyW(SN.TranResult, tran.Mid(kg + 1));
	}

	//ȡ���ֺ�
	{
		CString tran = m_config[4];
		int kg = tran.Find('-');
		StrCpyW(m_config[4], tran.Mid(kg+2));
		cf.split(m_config[4], _T(","), serialnumber, 100);
		SN.Num = serialnumber;
	}
	//ȡ�ܾ����ֺ�
	{
		CString tran = m_config[5];
		int kg = tran.Find('-');
		StrCpyW(m_config[5], tran.Mid(kg+2));
		cf.split(m_config[5], _T(","), refusenumber, 100);
		SN.RefuseNum = refusenumber; 
	}
	return true;
}
