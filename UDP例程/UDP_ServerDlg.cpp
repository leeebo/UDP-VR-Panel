// UDP_ServerDlg.cpp : 实现文件  
//  
  
#include "stdafx.h"  
#include "UDP_Server.h"  
#include "UDP_ServerDlg.h"  
  
  
  
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
  
  
// CUDP_ServerDlg 对话框  
  
  
  
  
CUDP_ServerDlg::CUDP_ServerDlg(CWnd* pParent /*=NULL*/)  
    : CDialog(CUDP_ServerDlg::IDD, pParent)  
    , m_gcIP(0)  
    , tempStr(_T(""))  
    , m_strTempString(_T(""))  
    , m_nPortNO(0)  
    , m_bServerCreated(false)  
    , m_strReceEdit(_T(""))  
    , m_strSendData(_T(""))  
    , m_bTerminateThread(false)  
{  
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);  
}  
  
void CUDP_ServerDlg::DoDataExchange(CDataExchange* pDX)  
{  
    CDialog::DoDataExchange(pDX);  
    DDX_Control(pDX, IDC_EDIT_SERVER_PORT, m_editPortNO);  
    DDX_Control(pDX, IDC_EDIT_RECEIVE, m_editReceive);  
    DDX_Text(pDX, IDC_EDIT_RECEIVE, m_strReceEdit);  
    DDX_Text(pDX, IDC_EDIT_SEND, m_strSendData);  
}  
  
BEGIN_MESSAGE_MAP(CUDP_ServerDlg, CDialog)  
    ON_WM_SYSCOMMAND()  
    ON_WM_PAINT()  
    ON_WM_QUERYDRAGICON()  
    //}}AFX_MSG_MAP  
    ON_BN_CLICKED(IDC_BUTTON_CREATE_SERVER, &CUDP_ServerDlg::OnBnClickedButtonCreateServer)  
    ON_WM_CLOSE()  
    ON_BN_CLICKED(IDC_BUTTON_SEND, &CUDP_ServerDlg::OnBnClickedButtonSend)  
END_MESSAGE_MAP()  
  
  
// CUDP_ServerDlg 消息处理程序  
  
BOOL CUDP_ServerDlg::OnInitDialog()  
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
    SetIcon(m_hIcon, TRUE);         // 设置大图标  
    SetIcon(m_hIcon, FALSE);        // 设置小图标  
  
    // TODO: 在此添加额外的初始化代码  
    //WSAStartup()  
    WSADATA wsaData;  
    PHOSTENT hostinfo;  
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)  
    {  
        MessageBox("WSAStartup ERROR!");  
    }  
  
    //设置服务器IP地址  
    char gcTemp[255];  
    char * IP;  
    if (0 == gethostname(gcTemp, 255))  
    {  
        hostinfo = gethostbyname(gcTemp);  
        //tempStr.Format("%s", gcTemp);  
        //MessageBox(tempStr);  
        IP = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);  
        tempStr.Format(IP);  
        //MessageBox(IP);  
        SetDlgItemText(IDC_STATIC_SERVER_ADDRESS, tempStr);  
        //m_addServerAddress.SetAddress();  
    }  
      
    //设置服务器默认端口号为100  
    SetDlgItemText(IDC_EDIT_SERVER_PORT, "100");  
    m_bServerCreated = false;  
    m_bTerminateThread = false;  
    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE  
}  
  
void CUDP_ServerDlg::OnSysCommand(UINT nID, LPARAM lParam)  
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
  
void CUDP_ServerDlg::OnPaint()  
{  
    if (IsIconic())  
    {  
        CPaintDC dc(this); // 用于绘制的设备上下文  
  
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);  
  
        // 使图标在工作矩形中居中  
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
  
//当用户拖动最小化窗口时系统调用此函数取得光标显示。  
//  
HCURSOR CUDP_ServerDlg::OnQueryDragIcon()  
{  
    return static_cast<HCURSOR>(m_hIcon);  
}  
  
UINT ServerRecvThread(LPVOID lpParm )  
{  
    CUDP_ServerDlg *dlg = (CUDP_ServerDlg*)lpParm;  
    char gcInBuffer[1027];  
    int lenth;  
    int size = sizeof(sockaddr_in);  
    CString strReceive, tempStr;  
     char*gcClientIP;   
     bool bSendEnable = false;  
    while(!dlg->m_bTerminateThread)  
    {  
        if ((lenth = recvfrom(dlg->m_sockServer, gcInBuffer, 1024, 0, (struct sockaddr *)&dlg->m_clientAddr, &size) )>0)  
        {  
            if (!bSendEnable)  
            {  
                CWnd *cwnd = dlg->GetDlgItem(IDC_BUTTON_SEND);  
                cwnd->EnableWindow(TRUE);  
                bSendEnable = true;  
            }  
  
            gcClientIP = inet_ntoa((dlg->m_clientAddr).sin_addr);  
            tempStr.Format("%s", gcClientIP);  
            dlg->SetDlgItemText(IDC_STATIC_CLINET_ADDRESS, tempStr);  
            tempStr.Format("%hu", dlg->m_clientAddr.sin_port);  
            dlg->SetDlgItemText(IDC_STATIC_CLIENT_PORTNO, tempStr);  
            tempStr.Format("%s:%hu: ", gcClientIP, dlg->m_clientAddr.sin_port);  
            strReceive += tempStr;  
            gcInBuffer[lenth] = '\r';  
            gcInBuffer[lenth+1] = '\n';  
            gcInBuffer[lenth+2] = '\0';  
            strReceive += gcInBuffer;  
            dlg->m_editReceive.SetWindowText(strReceive);              
        }  
    }  
    return 0;  
}  
  
void CUDP_ServerDlg::OnBnClickedButtonCreateServer()  
{  
    // TODO: 在此添加控件通知处理程序代码  
    if (m_bServerCreated)  
    {  
        //终止线程  
        m_bTerminateThread = true;  
      
        m_bServerCreated = false;  
        m_editPortNO.EnableWindow(TRUE);  
        SetDlgItemText(IDC_BUTTON_CREATE_SERVER, "Create");  
        //disable send 按钮  
        CWnd * cwnd = GetDlgItem(IDC_BUTTON_SEND);  
        cwnd->EnableWindow(FALSE);  
  
    }   
    else//创建服务器端  
    {  
        //读取服务器地址以及端口号  
        GetDlgItemText(IDC_EDIT_SERVER_PORT, m_strTempString);  
        m_nPortNO = atoi(m_strTempString.GetBuffer());  
        //MessageBox(m_strTempString);  
  
        //socket  
        if ((m_sockServer = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)  
        {  
            MessageBox("ERROR: Create Server Socket Error!");  
            exit(-1);  
        }  
        //bind  
        struct sockaddr_in serAddr;  
        serAddr.sin_family = AF_INET;  
        serAddr.sin_port = htons(m_nPortNO);  
        (serAddr.sin_addr).s_addr = htonl(INADDR_ANY);  
        if ((bind(m_sockServer, (LPSOCKADDR)&serAddr, sizeof(serAddr)))==SOCKET_ERROR)  
        {  
            MessageBox("ERROR: Bind Socket Error!");  
            exit(-1);  
        }  
        //disable portno  
        m_editPortNO.EnableWindow(FALSE);  
        SetDlgItemText(IDC_BUTTON_CREATE_SERVER, "Close");  
        m_bServerCreated = true;  
  
        //创建线程等待  
        m_bTerminateThread = false;  
        AfxBeginThread(ServerRecvThread, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);  
    }  
      
  
}  
  
  
void CUDP_ServerDlg::OnClose()  
{  
    // TODO: 在此添加消息处理程序代码和/或调用默认值  
    m_bTerminateThread = true;  
    closesocket(m_sockServer);  
    WSACleanup();  
    //Disable close按钮,enable create按钮  
    CWnd * cwnd = (GetDlgItem(IDC_BUTTON_CREATE_SERVER));  
    cwnd->EnableWindow(TRUE);  
    CDialog::OnClose();  
}  
  
void CUDP_ServerDlg::OnBnClickedButtonSend()  
{  
    // TODO: 在此添加控件通知处理程序代码  
    UpdateData(TRUE);  
    //MessageBox(m_strSendData);  
    sendto(m_sockServer, m_strSendData, strlen(m_strSendData), 0, (struct sockaddr*)&m_clientAddr, sizeof(sockaddr));  
}  