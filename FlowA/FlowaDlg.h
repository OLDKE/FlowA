// FlowaDlg.h : ͷ�ļ�
//

#pragma once
#include "config.h"
#include "adapter.h"
// CFlowaDlg �Ի���
class CFlowaDlg : public CDialog, public Config, public Adapter
{
// ����
public:
	CFlowaDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CFlowaDlg();
	CTrayIcon m_trayIcon;
// �Ի�������
	enum { IDD = IDD_FLOWA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcPaint();
	afx_msg void OnOpen();
	afx_msg void OnCancel();
	afx_msg void OnExit();
	afx_msg void OnDestroy();
public:
	bool initFlowa();
	/*
	˵��������atm��־�ĺ���
	����ֵ�� true �ɹ��� false ʧ��
	*/
	bool logAnalysis();
	/*
	˵������������������Կ�ĺ���
	����ֵ�� true �ɹ��� false ʧ��
	*/
	bool keyAnalysis();
private:
	//����������������ָ��
	ReadAdapter* m_readAdapter;
	FormatAdapter* m_formatAdapter;
	ContentAdapter* m_contentAdapter;
	StoringAdapter* m_storingAdapter;
private:
	BOOL WINAPI EnablePrivileges()
	{
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
			return(FALSE);
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid);
		tkp.PrivilegeCount = 1;
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
		if (GetLastError() != ERROR_SUCCESS)
			return FALSE;
		return TRUE;
	}
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
