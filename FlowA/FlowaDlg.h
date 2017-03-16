// FlowaDlg.h : 头文件
//

#pragma once
#include "config.h"
#include "adapter.h"
// CFlowaDlg 对话框
class CFlowaDlg : public CDialog, public Config, public Adapter
{
// 构造
public:
	CFlowaDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CFlowaDlg();
	CTrayIcon m_trayIcon;
// 对话框数据
	enum { IDD = IDD_FLOWA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	说明：分析atm日志的函数
	返回值： true 成功， false 失败
	*/
	bool logAnalysis();
	/*
	说明：分析加密所需密钥的函数
	返回值： true 成功， false 失败
	*/
	bool keyAnalysis();
private:
	//用来保存适配器的指针
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
