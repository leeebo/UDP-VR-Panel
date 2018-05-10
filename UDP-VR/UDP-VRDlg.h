
// UDP-VRDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include <WinSock2.h> 


// CUDPVRDlg 对话框
class CUDPVRDlg : public CDialogEx
{
// 构造
public:
	CUDPVRDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UDPVR_DIALOG };

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
	afx_msg void OnBnClickedOk();
	int m_sendto(CString sendbuff);
	CIPAddressCtrl m_addrServer;
	struct sockaddr_in m_serverAddr; 
	unsigned short m_nServerPortNo; 

	struct sockaddr_in m_localAddr; 
	unsigned short m_nlocalPortNo;

	CString m_strServerIPPort;  
	bool m_bServerSet;  
	bool m_bTerminateThread;  
	SOCKET m_sockClient; 
	CString m_strSendData;  
	afx_msg void OnBnClickedCancel();
	CEdit m_editReceive;
	afx_msg void OnBnClickedButton1Tl();
	afx_msg void OnBnClickedButton2Tr();
	afx_msg void OnBnClickedButton4Tlr();
	afx_msg void OnBnClickedButton5Cl();
	afx_msg void OnBnClickedButton6Cr();
	afx_msg void OnBnClickedButton7Clr();
	afx_msg void OnBnClickedButton8St();
	afx_msg void OnBnClickedButton9Ex();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	bool clear_num;
	bool clear_edit;
	CString strReceive;
	UINT Recvlenth_total;
	UINT Sendlenth_total;
	CString strSend;
	int Radio_tcp_udp;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton1send();
};
