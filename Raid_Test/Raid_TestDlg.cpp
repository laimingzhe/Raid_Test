
// Raid_TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Raid_Test.h"
#include "Raid_TestDlg.h"
#include "afxdialogex.h"
#include <MMSystem.h>
#include <Windows.h>
#include "WavePlayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <vfw.h>
#pragma comment(lib,"vfw32.lib")
#pragma   comment(lib,   "winmm.lib")
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
int iTime = 600,iDjs = 15,iTime_fen,iTime_miao;
CString cs_djs,cs_sj,cs_sm,cs_fen,cs_miao;
CString wav_st(_T("st.wav"));
CString wav_dm(_T(".//audio//dm.wav"));
CString wav_dd(_T(".//audio//遁地.mp3"));
CWavePlayer* wp_st;
CWavePlayer* wp_dm;
CWavePlayer* wp_dd;

#define DelayST 0

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


// CRaid_TestDlg 对话框




CRaid_TestDlg::CRaid_TestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRaid_TestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRaid_TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CRaid_TestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CRaid_TestDlg 消息处理程序


BOOL CRaid_TestDlg::OnInitDialog()
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
	
	SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);  
	SetWindowPos(&this->wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
	//PlaySound(LPCWSTR("IDR_WAVE1"),NULL,SND_FILENAME | SND_ASYNC);
	
	wp_dd = new CWavePlayer(wav_dd);
	wp_dm = new CWavePlayer(wav_dm);
	wp_dd->SetVolume(1000);
	wp_dm->SetVolume(1000);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRaid_TestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRaid_TestDlg::OnPaint()
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
HCURSOR CRaid_TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString cs_num,cs_dz,cs_dd;
int psflag = 0,psflag1 = 0,psflag_dm = 0;
DWORD time_begin = 0,time_end = 0;
void CRaid_TestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
		case 1:
			SYSTEMTIME sys; 
			GetLocalTime( &sys ); 
			if (psflag1 == 0)
			{
				time_begin = sys.wSecond;  ;
				psflag1 = 1;
			}else{
				time_end = sys.wSecond;
				if (time_end - time_begin == 1 || time_end - time_begin == -59)
				{
					psflag1 = 0;
					iTime--;
					cs_sj.Format(_T("%d"),iTime);
					iTime_fen =  iTime / 60;
					iTime_miao = iTime % 60;
					cs_fen.Format(_T("%d"),iTime_fen);
					cs_miao.Format(_T("%d"),iTime_miao);
					if (iTime <=1600)
					{
						//10:00
						//cs_sj.Format(_T("%d"),iTime);
						SetDlgItemTextW(IDC_STATIC3,cs_fen);
						SetDlgItemTextW(IDC_STATIC4,cs_miao);
					}
					if ((iTime <= 430+2 && iTime >= 425) || (iTime <= 350+2 && iTime >=345) || (iTime <= 270+2 && iTime >=265) || (iTime <= 190+2 && iTime >=185) || (iTime <= 110+2 && iTime >=105))
					{
						cs_dd  = "遁地准备！";
						SetDlgItemTextW(IDC_STATIC_DZ,cs_dd);
						if (psflag_dm == 0)
						{
							//PlaySound(LPCTSTR("dm.mp3"),NULL,0);
							wp_dd->Play();
							psflag_dm = 1;
						}
						if (iTime == 425 || iTime == 345 || iTime == 265 || iTime == 185 || iTime == 105)
						{
							psflag_dm = 0;
						}
					}else{
						cs_dd = " ";
						SetDlgItemTextW(IDC_STATIC_DZ,cs_dd);
					}
					if ((iTime <= 390+2 && iTime >=385) || (iTime <= 310+2 && iTime >=305) || (iTime <= 230+2 && iTime >=225) || (iTime <= 150+2 && iTime >=145) || (iTime <= 70+2 && iTime >=65))
					{
						//6.25
						//5.05
						//3.45
						//2.25
						//1.05
						//德姆大招时间
						cs_dz  = "德姆大招马上释放！";
						SetDlgItemTextW(IDC_STATIC_DZ,cs_dz);
						if (psflag_dm == 0)
						{
							//PlaySound(LPCTSTR("dm.mp3"),NULL,0);
							wp_dm->Play();
							psflag_dm = 1;
						}
						if (iTime == 385 || iTime == 305 || iTime == 225 || iTime == 145 || iTime == 65)
						{
							psflag_dm = 0;
						}
					}else{
						if (psflag_dm == 0)
						{
							cs_dz = " ";
							SetDlgItemTextW(IDC_STATIC_DZ,cs_dz);
						}
					}
					if ((iTime <= 580+DelayST && iTime >= 570) || (iTime <= 370+DelayST && iTime >= 360) || (iTime <= 160+DelayST && iTime >= 150))
					{
						//箭头
						//9:30
						//6:00
						//2.30
						cs_sm = "箭头 ";
						cs_djs.Format(_T("%d"),iDjs);
						iDjs--;

						if (iTime <= 580+DelayST && iTime >= 570)
						{
							cs_num = "1号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								//PlaySound(LPCTSTR("st.mp3"),NULL,0);
								CString cstmp1(".//audio//1箭头.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}else if (iTime <= 370+DelayST && iTime >= 360)
						{
							cs_num = "2号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//2箭头.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}else if (iTime <= 160+DelayST && iTime >= 150)
						{
							cs_num = "3号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//3箭头.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}


						if (iTime == 570 || iTime == 360 || iTime == 150)
						{
							iDjs = 10+DelayST;
							SetDlgItemTextW(IDC_STATIC1,LPTSTR(" "));
							SetDlgItemTextW(IDC_STATIC2,LPTSTR(" "));
							psflag = 0;

						}else{
							SetDlgItemTextW(IDC_STATIC1,cs_sm);
							SetDlgItemTextW(IDC_STATIC2,cs_djs);
						}

					}
					if ((iTime <= 550+DelayST && iTime >= 540) || (iTime <= 340+DelayST && iTime >= 330) || (iTime <= 130+DelayST && iTime >= 120))
					{
						//圆圈
						//9.00
						//5.30
						//2.00
						cs_sm = "圆圈 ";
						cs_djs.Format(_T("%d"),iDjs);
						iDjs--;

						if (iTime <= 550+DelayST && iTime >= 540)
						{
							cs_num = "2号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//2圆圈.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}else if (iTime <= 340+DelayST && iTime >= 330)
						{
							cs_num = "3号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//3圆圈.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}else if (iTime <= 130+DelayST && iTime >= 120)
						{
							cs_num = "1号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//1圆圈.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}

						if (iTime == 540 || iTime == 330 || iTime == 120)
						{
							iDjs = 10+DelayST;
							SetDlgItemTextW(IDC_STATIC1,LPTSTR(" "));
							SetDlgItemTextW(IDC_STATIC2,LPTSTR(" "));
							psflag = 0;
						}else{
							SetDlgItemTextW(IDC_STATIC1,cs_sm);
							SetDlgItemTextW(IDC_STATIC2,cs_djs);
						}

					}
					if ((iTime <= 520+DelayST && iTime >= 510) || (iTime <= 310+DelayST && iTime >= 300) || (iTime <= 100+DelayST && iTime >= 90))
					{
						//爱心
						//8.30
						//5.00
						//1.30
						cs_sm = "爱心 ";
						cs_djs.Format(_T("%d"),iDjs);
						iDjs--;

						if (iTime <= 520+DelayST && iTime >= 510)
						{
							cs_num = "3号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//3爱心.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}else if (iTime <= 310+DelayST && iTime >= 300)
						{
							cs_num = "1号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//1爱心.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}else if (iTime <= 100+DelayST && iTime >= 90)
						{
							cs_num = "2号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//2爱心.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}

						if (iTime == 510 || iTime == 300 || iTime == 90)
						{
							iDjs = 10+DelayST;
							SetDlgItemTextW(IDC_STATIC1,LPTSTR(" "));
							SetDlgItemTextW(IDC_STATIC2,LPTSTR(" "));
							psflag = 0;
						}else{
							SetDlgItemTextW(IDC_STATIC1,cs_sm);
							SetDlgItemTextW(IDC_STATIC2,cs_djs);
						}

					}
					if ((iTime <= 490+DelayST && iTime >= 480) || (iTime <= 280+DelayST && iTime >= 270) || (iTime <= 70+DelayST && iTime >= 60))
					{
						//方块
						//8.00
						//4.30
						//1.00
						cs_sm = "方块 ：";
						cs_djs.Format(_T("%d"),iDjs);
						iDjs--;

						if (iTime <= 490+DelayST && iTime >= 480)
						{
							cs_num = "1号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//1方块.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}else if (iTime <= 280+DelayST && iTime >= 270)
						{
							cs_num = "2号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//2方块.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}else if (iTime <= 70+DelayST && iTime >= 60)
						{
							cs_num = "3号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//3方块.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}

						if (iTime == 480 || iTime == 270 || iTime == 60)
						{
							iDjs = 10+DelayST;
							SetDlgItemTextW(IDC_STATIC1,LPTSTR(" "));
							SetDlgItemTextW(IDC_STATIC2,LPTSTR(" "));
							psflag = 0;
						}else{
							SetDlgItemTextW(IDC_STATIC1,cs_sm);
							SetDlgItemTextW(IDC_STATIC2,cs_djs);
						}

					}
					if ((iTime <= 460+DelayST && iTime >= 450) || (iTime <= 250+DelayST && iTime >= 240) || (iTime <= 40+DelayST && iTime >= 30))
					{
						//五角星
						//7.30
						//4.00
						//0.30
						cs_sm = "五角星 ：";
						cs_djs.Format(_T("%d"),iDjs);
						iDjs--;

						if (iTime <= 460+DelayST && iTime >= 450)
						{
							cs_num = "2号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//2星星.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}else if (iTime <= 250+DelayST && iTime >= 240)
						{
							cs_num = "3号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//3星星.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}else if (iTime <= 40+DelayST && iTime >= 30)
						{
							cs_num = "1号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//1星星.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}

						if (iTime == 450 || iTime == 240 || iTime == 30)
						{
							iDjs = 10+DelayST;
							SetDlgItemTextW(IDC_STATIC1,LPTSTR(" "));
							SetDlgItemTextW(IDC_STATIC2,LPTSTR(" "));
							psflag = 0;
						}else{
							SetDlgItemTextW(IDC_STATIC1,cs_sm);
							SetDlgItemTextW(IDC_STATIC2,cs_djs);
						}

					}
					if ((iTime <= 430+DelayST && iTime >= 420)  || (iTime <= 220+DelayST && iTime >= 210))
					{
						//螺旋
						//7.00
						//3.30
						cs_sm = "螺旋 ：";
						cs_djs.Format(_T("%d"),iDjs);
						iDjs--;

						if (iTime <= 430+DelayST && iTime >= 420)
						{
							cs_num = "3号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//3旋涡.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}else if (iTime <= 220+DelayST && iTime >= 210)
						{
							cs_num = "1号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//1旋涡.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}

						if (iTime == 420 || iTime == 210)
						{
							iDjs = 10+DelayST;
							SetDlgItemTextW(IDC_STATIC1,LPTSTR(" "));
							SetDlgItemTextW(IDC_STATIC2,LPTSTR(" "));
							psflag = 0;
						}else{
							SetDlgItemTextW(IDC_STATIC1,cs_sm);
							SetDlgItemTextW(IDC_STATIC2,cs_djs);
						}

					}
					if ((iTime <= 400+DelayST && iTime >= 390)  || (iTime <= 190+DelayST && iTime >= 180))
					{
						//三角
						//6.30
						//3.00
						cs_sm = "三角 ：";
						cs_djs.Format(_T("%d"),iDjs);
						iDjs--;

						if (iTime <= 400+DelayST && iTime >= 390)
						{
							cs_num = "1号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//1三角.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}else if (iTime <= 190+DelayST && iTime >= 180)
						{
							cs_num = "2号:";
							cs_sm = cs_sm + cs_num;
							if (psflag == 0)
							{
								CString cstmp1(".//audio//2三角.mp3");
								CWavePlayer* wp_st_tmp1 = new CWavePlayer(cstmp1);
								wp_st_tmp1->Play();
								psflag = 1;
							}
						}

						if (iTime == 390 || iTime == 180)
						{
							iDjs = 10+DelayST;
							SetDlgItemTextW(IDC_STATIC1,LPTSTR(" "));
							SetDlgItemTextW(IDC_STATIC2,LPTSTR(" "));
							psflag = 0;
						}else{
							SetDlgItemTextW(IDC_STATIC1,cs_sm);
							SetDlgItemTextW(IDC_STATIC2,cs_djs);
						}
					}
				}
			}
			
			break;
		default:
			break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CRaid_TestDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)  
	{  
		switch (pMsg->wParam)  
		{  
		case VK_F5:  
			SetTimer(1,200,NULL);
			iTime = 600;
			iDjs = 10+DelayST;
			break;  
		case VK_F6:
			KillTimer(1);
			iTime = 600;
			iDjs = 10+DelayST;
			SetDlgItemTextW(IDC_STATIC1,LPTSTR(" "));
			SetDlgItemTextW(IDC_STATIC2,LPTSTR(" "));
			SetDlgItemTextW(IDC_STATIC3,LPTSTR(" "));
			SetDlgItemTextW(IDC_STATIC4,LPTSTR(" "));
			psflag1 = 0;
			time_begin = 0;
			time_end = 0;
			psflag = 0;
			break;  
		default:  
			break;  
		}  
	}  
	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CRaid_TestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd == GetDlgItem(IDC_STATIC_DZ))
	{
		pDC->SetTextColor(RGB(255, 0, 0)); 
	}
	
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}