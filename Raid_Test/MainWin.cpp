// MainWin.cpp : 实现文件
//

#include "stdafx.h"
#include "Raid_Test.h"
#include "MainWin.h"
#include "afxdialogex.h"


// CMainWin 对话框

IMPLEMENT_DYNAMIC(CMainWin, CDialogEx)

CMainWin::CMainWin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainWin::IDD, pParent)
{

}

CMainWin::~CMainWin()
{
}

void CMainWin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainWin, CDialogEx)
END_MESSAGE_MAP()


// CMainWin 消息处理程序


int CMainWin::DemmeTips(void)
{

	return 0;
}
