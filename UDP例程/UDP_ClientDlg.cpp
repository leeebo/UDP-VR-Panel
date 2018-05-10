// UDP_ClientDlg.cpp : 实现文件  
//  
  
#include "stdafx.h"  
#include "UDP_Client.h"  
#include "UDP_ClientDlg.h"  
  
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
  
  
// CUDP_ClientDlg 对话框  
  
  
  
  
CUDP_ClientDlg::CUDP_ClientDlg(CWnd* pParent /*=NULL*/)  
    : CDialog(CUDP_ClientDlg::IDD, pParent)  
    , tempStr(_T(""))  
    , m_nServerPortNo(0)  
    , m_bServerSet(false)  
    , m_strSendData(_T(""))  
    , m_bTerminateThread(false)  
{  
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);  
}  
  
void CUDP_ClientDlg::DoDataExchange(CDataExchange* pDX)  
{  
    CDialog::DoDataExchange(pDX);  
    DDX_Control(pDX, IDC_IPADDRESS_SERVER, m_addrServer);  
    DDX_Control(pDX, IDC_EDIT_RECEIVE, m_editReceive);  
    DDX_Text(pDX, IDC_EDIT4, m_strSendData);  
}  
  
BEGIN_MESSAGE_MAP(CUDP_ClientDlg, CDialog)  
    ON_WM_SYSCOMMAND()  
    ON_WM_PAINT()  
    ON_WM_QUERYDRAGICON()  
    //}}AFX_MSG_MAP  
    ON_BN_CLICKED(IDC_BUTTON_RESET_SERVER, &CUDP_ClientDlg::OnBnClickedButtonResetServer)  
    ON_BN_CLICKED(IDC_BUTTON_SEND, &CUDP_ClientDlg::OnBnClickedButtonSend)  
    ON_WM_CLOSE()  
END_MESSAGE_MAP()  
  
  
// CUDP_ClientDlg 消息处理程序  
  
BOOL CUDP_ClientDlg::OnInitDialog()  
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
    m_bServerSet = false;  
    m_bTerminateThread = false;  
    //WSAStartup()  
    WSADATA wsaData;  
    PHOSTENT hostinfo;  
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)  
    {  
        MessageBox("WSAStartup ERROR!");  
    }  
  
    //设置客户端IP地址及端口  
    //读取本机ip地址  
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
        SetDlgItemText(IDC_STATIC_CLIENT_ADDRESS, tempStr);  
        //m_addServerAddress.SetAddress();  
    }  
  
    //create client socket  
    //socket  
    if ((m_sockClient = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)  
    {  
        MessageBox("ERROR: Create Client Socket Error!");  
        exit(-1);  
    }  
  
    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE  
}  
  
void CUDP_ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)  
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
  
void CUDP_ClientDlg::OnPaint()  
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
HCURSOR CUDP_ClientDlg::OnQueryDragIcon()  
{  
    return static_cast<HCURSOR>(m_hIcon);  
}  
  
UINT ClientRecvThread(LPVOID lpParm )  
{  
    CUDP_ClientDlg *dlg = (CUDP_ClientDlg*)lpParm;  
    char gcInBuffer[1027];  
    int lenth;  
    int size = sizeof(sockaddr_in);  
    CString strReceive, tempStr;  
    while(!dlg->m_bTerminateThread)  
    {  
        if ((lenth = recvfrom(dlg->m_sockClient, gcInBuffer, 1024, 0, (struct sockaddr *)&dlg->m_serverAddr, &size) )>0)  
        {  
            strReceive+= dlg->m_strServerIPPort+": ";  
            gcInBuffer[lenth] = '\r';  
            gcInBuffer[lenth+1] = '\n';  
            gcInBuffer[lenth+2] = '\0';  
            strReceive += gcInBuffer;  
            dlg->m_editReceive.SetWindowText(strReceive);              
        }  
    }  
    return 0;  
}  
  
void CUDP_ClientDlg::OnBnClickedButtonResetServer()  
{  
    // TODO: 在此添加控件通知处理程序代    
    //重置服务器ip地址以及端口号  
    m_serverAddr.sin_family = AF_INET;  
    //读取服务器端地址  
    BYTE addr[4];  
    m_addrServer.GetAddress(addr[0], addr[1], addr[2], addr[3]);  
    //读取服务器端口号  
    GetDlgItemText(IDC_EDIT_SERVER_PORTNO, tempStr);  
    m_nServerPortNo = atoi(tempStr.GetBuffer());  
    tempStr.Format("%d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);  
    m_strServerIPPort.Format("%d.%d.%d.%d:%d", addr[0], addr[1], addr[2], addr[3], m_nServerPortNo);  
    //MessageBox(tempStr);  
    m_serverAddr.sin_port = htons(m_nServerPortNo);  
    m_serverAddr.sin_addr.s_addr= inet_addr(tempStr);  
  
    if (m_bServerSet)//判断是否第一次按下按钮  
    {  
        return;  
    }   
    else  
    {  
        m_bServerSet = true;  
        //enable send 按钮  
        CWnd * cwnd = GetDlgItem(IDC_BUTTON_SEND);  
        cwnd->EnableWindow(TRUE);  
  
        //开启接收数据线程  
        m_bTerminateThread = false;  
        AfxBeginThread(ClientRecvThread, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);  
    }  
}  
  
void CUDP_ClientDlg::OnBnClickedButtonSend()  
{  
    // TODO: 在此添加控件通知处理程序代码  
    UpdateData(TRUE);  
    sendto(m_sockClient, m_strSendData, strlen(m_strSendData), 0,  (struct sockaddr*)&m_serverAddr, sizeof(sockaddr));  
}  
  
void CUDP_ClientDlg::OnClose()  
{  
    // TODO: 在此添加消息处理程序代码和/或调用默认值  
    m_bTerminateThread = true;  
    closesocket(m_sockClient);  
    WSACleanup();  
    CDialog::OnClose();  
}  
