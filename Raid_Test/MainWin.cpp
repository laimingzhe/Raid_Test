// MainWin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Raid_Test.h"
#include "MainWin.h"
#include "afxdialogex.h"


// CMainWin �Ի���

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


// CMainWin ��Ϣ�������


int CMainWin::DemmeTips(void)
{

	return 0;
}
