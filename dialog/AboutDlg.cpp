// dialog\AboutDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../Rhino.h"
#include "AboutDlg.h"
#include "afxdialogex.h"
#include "AboutDlg.h"


// AboutDlg �Ի���

IMPLEMENT_DYNAMIC(AboutDlg, CDialogEx)

AboutDlg::AboutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ABOUT_DIALOG, pParent)
{

}

AboutDlg::~AboutDlg()
{
}

void AboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutDlg, CDialogEx)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// AboutDlg ��Ϣ�������


BOOL AboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void AboutDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	SendMessage(WM_CLOSE);
}


void AboutDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	SendMessage(WM_CLOSE);
}
