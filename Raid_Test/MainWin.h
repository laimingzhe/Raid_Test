#pragma once


// CMainWin �Ի���

class CMainWin : public CDialogEx
{
	DECLARE_DYNAMIC(CMainWin)

public:
	CMainWin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainWin();

// �Ի�������
	enum { IDD = IDD_RAID_TEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int DemmeTips(void);
};
