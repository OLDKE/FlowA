// FlowaDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Flowa.h"
#include "FlowaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CFlowaDlg �Ի���


CFlowaDlg::CFlowaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFlowaDlg::IDD, pParent),m_trayIcon(IDR_TRAYICON)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CFlowaDlg::~CFlowaDlg()
{
	//�ͷŻ�ȡ��������
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


// CFlowaDlg ��Ϣ�������

BOOL CFlowaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	EnablePrivileges();
	if (!initFlowa())
		return false;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFlowaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFlowaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int CFlowaDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_trayIcon.SetNotificationWnd(this, WM_USER + 0);
	m_trayIcon.SetIcon(m_hIcon, _T("���������豸���ݲɼ��ͻ���"));
	return 0;
}

void CFlowaDlg::OnNcPaint()
{
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnNcPaint()
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

//Flowa�������ö�ʱ�ص�
void CFlowaDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	//�����ļ�
	case 1:
	{
		logAnalysis();
	}break;
	//������Կ
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
	
	//����ע������õ��е��ļ�
	for (int i = 0; i < m_fileCount; ++i)
	{
		try
		{
			wchar_t context[CHUNKSIZE + 1]; //���������ȡ�����ļ�����
			ZeroMemory(context, sizeof(context));
			msg.Format(_T("ҵ������[%s]"), m_flowaFile[i].businessType);
			logInfo(msg.GetBuffer());
			//��ȡ��־
			if (!m_readAdapter->read(&m_flowaFile[i], context))
				continue;
			wchar_t fcontext[CHUNKSIZE + 1]; //������Ÿ�ʽ���������
			ZeroMemory(fcontext, sizeof(fcontext));
			//��ʽ������
			if (!m_formatAdapter->format(&m_flowaFile[i], context, fcontext))
				continue;
			wchar_t ccontext[CHUNKSIZE + 1]; //������Ÿ�ʽ���������
			ZeroMemory(ccontext, sizeof(ccontext));
			//�����ȡ������
			if (!m_contentAdapter->format(&m_flowaFile[i], fcontext, ccontext))
				continue;
			//�洢��ȡ������
			if (!m_storingAdapter->storing(&m_flowaFile[i], ccontext))
				continue;
		}
		catch (...)
		{
			msg.Format(_T("����δ֪�쳣����������"));
			logInfo(msg.GetBuffer());
			msg.ReleaseBuffer();
		}
		
	}
	msg.Format(_T("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<ANALYSIS END AT TIME[%s]>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"), time.Format(_T("%Y/%m/%d %H:%M:%S")));
	logInfo(msg.GetBuffer());
	return true;
}
//�˶�ʱ�ص���������ʱ�����ܱ����������Կ,������Կ����Ӧ�����ʹ�ü���
bool CFlowaDlg::keyAnalysis()
{
	
	return true;
}