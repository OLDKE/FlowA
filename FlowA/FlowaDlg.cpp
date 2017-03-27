// FlowaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Flowa.h"
#include "FlowaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CFlowaDlg 对话框


CFlowaDlg::CFlowaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFlowaDlg::IDD, pParent),m_trayIcon(IDR_TRAYICON)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CFlowaDlg::~CFlowaDlg()
{
	//释放获取的适配器
	delete m_readAdapter;
	delete m_formatAdapter;
	delete m_contentAdapter;
	delete m_storingAdapter;
}

void CFlowaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFlowaDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCPAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_OPEN, CFlowaDlg::OnOpen)
	ON_COMMAND(IDM_CANCEL, CFlowaDlg::OnCancel)
	ON_COMMAND(IDM_EXIT, CFlowaDlg::OnExit)
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CFlowaDlg 消息处理程序

BOOL CFlowaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	EnablePrivileges();
	if (!initFlowa())
		return false;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFlowaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFlowaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFlowaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int CFlowaDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_trayIcon.SetNotificationWnd(this, WM_USER + 0);
	m_trayIcon.SetIcon(m_hIcon, _T("金融自助设备数据采集客户端"));
	return 0;
}

void CFlowaDlg::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnNcPaint()
	static int i = 2; 
	if(i > 0) 
	{ 
		i --; 
		ShowWindow(SW_HIDE); 
	} 
	else 
		CDialog::OnNcPaint(); 
}

void CFlowaDlg::OnOpen()
{
	//ShowWindow(SW_NORMAL);
}

void CFlowaDlg::OnCancel()
{
	ShowWindow(SW_HIDE);
}

void CFlowaDlg::OnExit()
{
	m_trayIcon.DeleteIcon();
	KillTimer(1);
	KillTimer(2);
	OnOK();
}

void CFlowaDlg::OnDestroy()
{
	CDialog::OnDestroy();
}

bool CFlowaDlg::initFlowa()
{
	if (!loadConfig())
		return false;

	m_readAdapter = getReadAdapter(m_atmc);
	m_formatAdapter = getFormatAdapter(m_atmc);
	m_contentAdapter = getContentAdapter(m_atmc);
	m_storingAdapter = getStoringAdapter(m_atmc);

	SetTimer(1, m_timer, NULL);
	SetTimer(2, m_timer, NULL);
	return true;
}

//Flowa根据配置定时回调
void CFlowaDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	//分析文件
	case 1:
	{
		logAnalysis();
	}break;
	//分析密钥
	case 2:
	{
		keyAnalysis();
	}break;
	default:
	{
	}
		break;
	}
	__super::OnTimer(nIDEvent);
}

bool CFlowaDlg::logAnalysis()
{
	CString msg;
	CTime time = CTime::GetCurrentTime();
	msg.Format(_T("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<ANALYSIS BEGIN AT TIME[%s]>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"), time.Format(_T("%Y/%m/%d %H:%M:%S")));
	logInfo(msg.GetBuffer());
	msg.ReleaseBuffer();
	
	//分析注册表配置当中的文件
	for (int i = 0; i < m_fileCount; ++i)
	{
		try
		{
			wchar_t context[CHUNKSIZE + 1]; //用来保存读取到的文件内容
			ZeroMemory(context, sizeof(context));
			msg.Format(_T("业务类型[%s]"), m_flowaFile[i].businessType);
			logInfo(msg.GetBuffer());
			//读取日志
			if (!m_readAdapter->read(&m_flowaFile[i], context))
				continue;
			wchar_t fcontext[CHUNKSIZE + 1]; //用来存放格式化后的数据
			ZeroMemory(fcontext, sizeof(fcontext));
			//格式化内容
			if (!m_formatAdapter->format(&m_flowaFile[i], context, fcontext))
				continue;
			wchar_t ccontext[CHUNKSIZE + 1]; //用来存放格式化后的数据
			ZeroMemory(ccontext, sizeof(ccontext));
			//处理读取的内容
			if (!m_contentAdapter->format(&m_flowaFile[i], fcontext, ccontext))
				continue;
			//存储读取的内容
			if (!m_storingAdapter->storing(&m_flowaFile[i], ccontext))
				continue;
		}
		catch (...)
		{
			msg.Format(_T("捕获到未知异常，不做处理"));
			logInfo(msg.GetBuffer());
			msg.ReleaseBuffer();
		}
		
	}
	msg.Format(_T("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<ANALYSIS END AT TIME[%s]>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"), time.Format(_T("%Y/%m/%d %H:%M:%S")));
	logInfo(msg.GetBuffer());
	return true;
}
//此定时回调，用来定时检测加密报文所需的密钥,并对密钥做相应处理后使用加密
bool CFlowaDlg::keyAnalysis()
{
	
	return true;
}