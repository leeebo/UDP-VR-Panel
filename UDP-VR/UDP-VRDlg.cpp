
// UDP-VRDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDP-VR.h"
#include "UDP-VRDlg.h"
#include "DLG_DIY.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString cs_protocol[9]={"TrainingL0180","TrainingR0180","TrainingLR0180","Left0180","Right0180","LR0180","stop","stopall","exit"};

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUDPVRDlg 对话框




CUDPVRDlg::CUDPVRDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDPVRDlg::IDD, pParent)
	, m_nServerPortNo(3004)  
	, m_bServerSet(false)  
	, m_strSendData(_T(""))  
	, m_bTerminateThread(false) 
	, Radio_tcp_udp(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUDPVRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_addrServer);
	DDX_Control(pDX, IDC_EDIT1, m_editReceive);
	DDX_Radio(pDX, IDC_RADIO1, Radio_tcp_udp);
}

BEGIN_MESSAGE_MAP(CUDPVRDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CUDPVRDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUDPVRDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1_TL, &CUDPVRDlg::OnBnClickedButton1Tl)
	ON_BN_CLICKED(IDC_BUTTON2_TR, &CUDPVRDlg::OnBnClickedButton2Tr)
	ON_BN_CLICKED(IDC_BUTTON4_TLR, &CUDPVRDlg::OnBnClickedButton4Tlr)
	ON_BN_CLICKED(IDC_BUTTON5_CL, &CUDPVRDlg::OnBnClickedButton5Cl)
	ON_BN_CLICKED(IDC_BUTTON6_CR, &CUDPVRDlg::OnBnClickedButton6Cr)
	ON_BN_CLICKED(IDC_BUTTON7_CLR, &CUDPVRDlg::OnBnClickedButton7Clr)
	ON_BN_CLICKED(IDC_BUTTON8_ST, &CUDPVRDlg::OnBnClickedButton8St)
	ON_BN_CLICKED(IDC_BUTTON9_EX, &CUDPVRDlg::OnBnClickedButton9Ex)
	ON_BN_CLICKED(IDC_BUTTON5, &CUDPVRDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CUDPVRDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CUDPVRDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON1, &CUDPVRDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON1_send, &CUDPVRDlg::OnBnClickedButton1send)
END_MESSAGE_MAP()


// CUDPVRDlg 消息处理程序

BOOL CUDPVRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	m_bServerSet = false;  
	m_bTerminateThread = false;  
	//WSAStartup()  
	WSADATA wsaData;  
//	PHOSTENT hostinfo;  
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)  
	{  
		MessageBox("WSAStartup ERROR!");  
	}  

	//设置客户端IP地址及端口  
	//读取本机ip地址  
	CString tempStr="127.0.0.1";
	//char gcTemp[255];  
	//char * IP;  
	//if (0 == gethostname(gcTemp, 255))  
	//{  
	//	hostinfo = gethostbyname(gcTemp);  
	//	//tempStr.Format("%s", gcTemp);  
	//	//MessageBox(tempStr);  
	//	IP = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);  
	//	tempStr.Format(IP);  
	//	//MessageBox(IP);  
	//	SetDlgItemText(IDC_STATIC_CLIENT_ADDRESS, tempStr);  
	//	//m_addServerAddress.SetAddress();  
	//}  
	SetDlgItemText(IDC_IPADDRESS1, tempStr);
	SetDlgItemText(IDC_EDIT3_lcport, _T("3005"));
	SetDlgItemText(IDC_EDIT4_dport, _T("3004"));
	SetDlgItemText(IDC_EDIT6,_T("0"));
	SetDlgItemText(IDC_EDIT5_rev_total,_T("0"));
	m_editReceive.SetWindowText(_T("等待接收")); 
	Sendlenth_total=0;
	clear_num=false;
	clear_edit=false;
	Recvlenth_total=0;
	strSend="";
	//create client socket  
	//socket  

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUDPVRDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUDPVRDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUDPVRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT ClientRecvThread(LPVOID lpParm )  
{  
	CUDPVRDlg *dlg = (CUDPVRDlg*)lpParm;
	char gcInBuffer[1027];  
	int lenth; 
	int size = sizeof(sockaddr_in);  
	CString tempStr;  
	while(!dlg->m_bTerminateThread)  
	{  
		if ((lenth = recvfrom(dlg->m_sockClient, gcInBuffer, 1024, 0, (struct sockaddr *)&(dlg->m_serverAddr), &size) )>0)  
		{  
			dlg->Recvlenth_total=dlg->Recvlenth_total+lenth;
			//strReceive+= dlg->m_strServerIPPort+": ";  
/*			gcInBuffer[lenth] = '\r';  
			gcInBuffer[lenth+1] = '\n';  
			gcInBuffer[lenth+2] = '\0'; */ 
			gcInBuffer[lenth] = '\0';
			dlg->strReceive += gcInBuffer;  
			tempStr.Format("%u",dlg->Recvlenth_total);
			dlg->SetDlgItemText(IDC_EDIT5_rev_total,tempStr);
			dlg->m_editReceive.SetWindowText(dlg->strReceive);   
			
		}  
	} 
	return 0;  
}  

void CUDPVRDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK()
	//disable portno  
	//m_editPortNO.EnableWindow(FALSE);  
	//SetDlgItemText(IDC_BUTTON_CREATE_SERVER, "Close");  
	//m_bServerCreated = true;  
	if (m_bServerSet)//判断是否第一次按下按钮  
	{  
		m_bTerminateThread = true; 
		m_bServerSet=false;
		closesocket(m_sockClient);  
		Sleep(500);
		SetDlgItemText(IDOK, "Create");  
		CWnd * cwnd = GetDlgItem(IDC_BUTTON1_send); 
		cwnd->EnableWindow(FALSE); 
		return;  
	}   
	else  
	{  
		m_bServerSet = true;  
		// TODO: 在此添加控件通知处理程序代    
		//重置服务器ip地址以及端口号  
		CString tempStr; 
		//读取服务器端地址  
		BYTE addr[4];  
		m_addrServer.GetAddress(addr[0], addr[1], addr[2], addr[3]);  
		//读取服务器端口号  
		GetDlgItemText(IDC_EDIT4_dport, tempStr);  
		m_nServerPortNo = atoi(tempStr.GetBuffer());  
		tempStr.Format("%d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);  
		m_strServerIPPort.Format("%d.%d.%d.%d:%d", addr[0], addr[1], addr[2], addr[3], m_nServerPortNo);  
		//MessageBox(tempStr); 
		m_serverAddr.sin_family = AF_INET;  
		m_serverAddr.sin_port =htons(m_nServerPortNo);  
		m_serverAddr.sin_addr.s_addr= inet_addr(tempStr);

		m_localAddr.sin_family = AF_INET;  
		m_localAddr.sin_addr.s_addr = inet_addr(tempStr);

		GetDlgItemText(IDC_EDIT3_lcport, tempStr); 
		m_nlocalPortNo = atoi(tempStr.GetBuffer());   
		m_localAddr.sin_port = htons(m_nlocalPortNo);  
		
		SetDlgItemText(IDOK, "Close");  
		//enable send 按钮  
		CWnd * cwnd = GetDlgItem(IDC_BUTTON1_send);  
		cwnd->EnableWindow(TRUE);  

		if ((m_sockClient = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)  
		{  
			MessageBox("ERROR: Create Client Socket Error!");  
			exit(-1);  
		}  
		if ((bind(m_sockClient, (LPSOCKADDR)&m_localAddr, sizeof(m_localAddr)))==SOCKET_ERROR)  
		{  
			MessageBox("ERROR: Bind Socket Error!");  
			exit(-1);  
		}  
		//开启接收数据线程  
		m_bTerminateThread = false;  
		AfxBeginThread(ClientRecvThread, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);  
	}  
}


int CUDPVRDlg::m_sendto(CString sendbuff)
{
	CString strtemp;
	INT num=sendto(m_sockClient, sendbuff, strlen(sendbuff), 0, (struct sockaddr*)&m_serverAddr, sizeof(sockaddr));
	if (num>0)
	{
		strSend+=sendbuff;
		Sendlenth_total+=num;
		strtemp.Format("%d",Sendlenth_total);
		SetDlgItemText(IDC_EDIT6,strtemp);
		SetDlgItemText(IDC_EDIT2,strSend);
	}
	return num;
}

void CUDPVRDlg::OnBnClickedCancel()
{
	m_bTerminateThread = true; 
	Sleep(200);
	WSACleanup();  
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CUDPVRDlg::OnBnClickedButton1Tl()
{
	m_sendto(cs_protocol[0]);
		// TODO: 在此添加控件通知处理程序代码
}


void CUDPVRDlg::OnBnClickedButton2Tr()
{
	m_sendto(cs_protocol[1]);// TODO: 在此添加控件通知处理程序代码
}


void CUDPVRDlg::OnBnClickedButton4Tlr()
{
	m_sendto(cs_protocol[2]);// TODO: 在此添加控件通知处理程序代码
}


void CUDPVRDlg::OnBnClickedButton5Cl()
{
	m_sendto(cs_protocol[3]);// TODO: 在此添加控件通知处理程序代码
}


void CUDPVRDlg::OnBnClickedButton6Cr()
{
	m_sendto(cs_protocol[4]);// TODO: 在此添加控件通知处理程序代码
}


void CUDPVRDlg::OnBnClickedButton7Clr()
{
	m_sendto(cs_protocol[5]);// TODO: 在此添加控件通知处理程序代码
}


void CUDPVRDlg::OnBnClickedButton8St()
{
	m_sendto(cs_protocol[6]);// TODO: 在此添加控件通知处理程序代码
}


void CUDPVRDlg::OnBnClickedButton9Ex()
{
	m_sendto(cs_protocol[7]);// TODO: 在此添加控件通知处理程序代码
}


void CUDPVRDlg::OnBnClickedButton5()
{
	m_sendto(cs_protocol[8]);// TODO: 在此添加控件通知处理程序代码
}


void CUDPVRDlg::OnBnClickedButton6()
{
	strReceive=_T("");
	strSend=_T("");
	SetDlgItemText(IDC_EDIT1,_T(""));
	SetDlgItemText(IDC_EDIT2,_T(""));
	// TODO: 在此添加控件通知处理程序代码
}


void CUDPVRDlg::OnBnClickedButton7()
{
	Recvlenth_total=0;
	Sendlenth_total=0;
	SetDlgItemText(IDC_EDIT6,_T("0"));
	SetDlgItemText(IDC_EDIT5_rev_total,_T("0"));
	// TODO: 在此添加控件通知处理程序代码
}


void CUDPVRDlg::OnBnClickedButton1()
{
	DLG_DIY diy;
	diy.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}


void CUDPVRDlg::OnBnClickedButton1send()
{
	CString strSend;
	GetDlgItemText(IDC_EDIT2,strSend);
	m_sendto(strSend);
	// TODO: 在此添加控件通知处理程序代码
}
