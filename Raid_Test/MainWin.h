#pragma once


// CMainWin 对话框

class CMainWin : public CDialogEx
{
	DECLARE_DYNAMIC(CMainWin)

public:
	CMainWin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainWin();

// 对话框数据
	enum { IDD = IDD_RAID_TEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int DemmeTips(void);
};
