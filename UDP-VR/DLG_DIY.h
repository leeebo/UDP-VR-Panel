#pragma once


// DLG_DIY 对话框

class DLG_DIY : public CDialogEx
{
	DECLARE_DYNAMIC(DLG_DIY)

public:
	DLG_DIY(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DLG_DIY();

// 对话框数据
	enum { IDD = IDD_diy };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString a1;
	CString a2;
	CString a3;
	CString a4;
	CString a5;
	CString a6;
	CString a7;
	CString a8;
	CString a9;
	afx_msg void OnBnClickedCancel();
};
