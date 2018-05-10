// UDP_ClientDlg.h : 头文件  
//  
  
#pragma once  
#include <WinSock2.h>  
#include "afxcmn.h"  
#include "afxwin.h"  
  
// CUDP_ClientDlg 对话框  
class CUDP_ClientDlg : public CDialog  
{  
// 构造  
public:  
    CUDP_ClientDlg(CWnd* pParent = NULL);   // 标准构造函数  
  
// 对话框数据  
    enum { IDD = IDD_UDP_CLIENT_DIALOG };  
  
    protected:  
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持  
  
  
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
    afx_msg void OnBnClickedButtonResetServer();  
public:  
    afx_msg void OnBnClickedButtonSend();  
public:  
    CString tempStr;  
public:  
    // 客户端socket  
    SOCKET m_sockClient;  
public:  
    struct sockaddr_in m_serverAddr;  
public:  
    afx_msg void OnClose();  
public:  
    // 服务器端地址控件  
    CIPAddressCtrl m_addrServer;  
public:  
    unsigned short m_nServerPortNo;  
public:  
    // 若服务器ip及端口已设定则为true,否则为false  
    bool m_bServerSet;  
public:  
    CString m_strServerIPPort;  
public:  
    CEdit m_editReceive;  
public:  
    // 控件变量,str  
    CString m_strSendData;  
public:  
    // 若为true则终止线程  
    bool m_bTerminateThread;  
};  