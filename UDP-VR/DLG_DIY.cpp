// DLG_DIY.cpp : 实现文件
//

#include "stdafx.h"
#include "UDP-VR.h"
#include "DLG_DIY.h"
#include "afxdialogex.h"

extern CString cs_protocol[9];
// DLG_DIY 对话框

IMPLEMENT_DYNAMIC(DLG_DIY, CDialogEx)

DLG_DIY::DLG_DIY(CWnd* pParent /*=NULL*/)
	: CDialogEx(DLG_DIY::IDD, pParent)
	, a1(_T(""))
	, a2(_T(""))
	, a3(_T(""))
	, a4(_T(""))
	, a5(_T(""))
	, a6(_T(""))
	, a7(_T(""))
	, a8(_T(""))
	, a9(_T(""))
{

}

DLG_DIY::~DLG_DIY()
{
}

void DLG_DIY::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, a1);
	DDX_Text(pDX, IDC_EDIT2, a2);
	DDX_Text(pDX, IDC_EDIT3, a3);
	DDX_Text(pDX, IDC_EDIT4, a4);
	DDX_Text(pDX, IDC_EDIT5, a5);
	DDX_Text(pDX, IDC_EDIT6, a6);
	DDX_Text(pDX, IDC_EDIT7, a7);
	DDX_Text(pDX, IDC_EDIT8, a8);
	DDX_Text(pDX, IDC_EDIT9, a9);
}


BEGIN_MESSAGE_MAP(DLG_DIY, CDialogEx)
	ON_BN_CLICKED(IDOK, &DLG_DIY::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DLG_DIY::OnBnClickedCancel)
END_MESSAGE_MAP()


// DLG_DIY 消息处理程序


void DLG_DIY::OnBnClickedOk()
{
	UpdateData(TRUE);
	cs_protocol[0]=a1;
	cs_protocol[1]=a2;
	cs_protocol[2]=a3;
	cs_protocol[3]=a4;
	cs_protocol[4]=a5;
	cs_protocol[5]=a6;
	cs_protocol[6]=a7;
	cs_protocol[7]=a8;
	cs_protocol[8]=a9;
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


BOOL DLG_DIY::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	a1=cs_protocol[0];
	a2=cs_protocol[1];
	a3=cs_protocol[2];
	a4=cs_protocol[3];
	a5=cs_protocol[4];
	a6=cs_protocol[5];
	a7=cs_protocol[6];
	a8=cs_protocol[7];
	a9=cs_protocol[8];
	UpdateData(FALSE);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void DLG_DIY::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
