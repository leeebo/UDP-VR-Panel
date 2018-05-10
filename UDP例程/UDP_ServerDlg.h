// UDP_ServerDlg.h : 头文件  
//  
  
#pragma once  
#include "afxcmn.h"  
#include "afxwin.h"  
#include <WinSock2.h>  
  
// CUDP_ServerDlg 对话框  
class CUDP_ServerDlg : public CDialog  
{  
// 构造  
public:  
    CUDP_ServerDlg(CWnd* pParent = NULL);   // 标准构造函数  
  
// 对话框数据  
    enum { IDD = IDD_UDP_SERVER_DIALOG };  
  
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
    afx_msg void OnBnClickedButtonCreateServer();  
public:  
    afx_msg void OnBnClickedButtonCloseServer();  
public:  
    // 端口号控件变量  
    CEdit m_editPortNO;  
public:  
    // IP地址数组  
    char m_gcIP;  
public:  
    CString tempStr;  
public:  
    afx_msg void OnClose();  
public:  
    CString m_strTempString;  
public:  
    // 服务器端口号  
    unsigned short m_nPortNO;  
public:  
    // 服务器端socket  
    SOCKET m_sockServer;  
public:  
    // 若已经创建服务器则为true,否则为false  
    bool m_bServerCreated;  
public:  
    struct sockaddr_in m_clientAddr;  
public:  
    // 接收数据的edit控件  
    CEdit m_editReceive;  
public:  
    // 接收数据控件的控件变量,str  
    CString m_strReceEdit;  
public:  
    afx_msg void OnBnClickedButtonSend();  
public:  
    // 发送edit控件变量,str  
    CString m_strSendData;  
public:  
    // 若为true则终止线程  
    bool m_bTerminateThread;  
};  