// dialog\RenderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../Rhino.h"
#include "afxdialogex.h"
#include "RenderDlg.h"

#define WM_TOPMOST (WM_USER+200)


// RenderDlg �Ի���

IMPLEMENT_DYNAMIC(RenderDlg, CDialogEx)

RenderDlg::RenderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RENDER_DIALOG, pParent)
	, m_bMoving(FALSE)
{

}

RenderDlg::~RenderDlg()
{
}

void RenderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RenderDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
    ON_COMMAND(WM_CLOSE, &RenderDlg::OnClose)
    ON_COMMAND(WM_TOPMOST, &RenderDlg::OnTopWindow)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
    ON_WM_SHOWWINDOW()
	ON_MESSAGE(WM_SET_RENDER_SIZE, &RenderDlg::OnSetRenderSize)
END_MESSAGE_MAP()


// RenderDlg ��Ϣ�������


BOOL RenderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ContextMenu.CreatePopupMenu();
    m_ContextMenu.AppendMenu(MF_STRING, WM_CLOSE, TEXT("����"));
    m_ContextMenu.AppendMenu(MF_STRING, WM_TOPMOST, TEXT("ȡ��������ǰ"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void RenderDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ShowWindow(SW_HIDE);

	CDialogEx::OnClose();
}


void RenderDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	m_ContextMenu.DestroyMenu();

	// TODO: �ڴ˴������Ϣ����������
}


void RenderDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	LPPOINT lpoint = new tagPOINT;
	::GetCursorPos(lpoint);//�õ����λ��

	m_ContextMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERNEGANIMATION, lpoint->x, lpoint->y, this);

	CDialogEx::OnRButtonUp(nFlags, point);
}


void RenderDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bMoving = FALSE;

	CDialogEx::OnMButtonUp(nFlags, point);
}


void RenderDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bMoving = TRUE;
	m_StartPos = point;

	CDialogEx::OnMButtonDown(nFlags, point);
}


void RenderDlg::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bMoving = FALSE;

	CDialogEx::OnMouseLeave();
}


void RenderDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_bMoving)
	{

		RECT rect;
		GetWindowRect(&rect);

		LONG xoffset = point.x - m_StartPos.x;
		LONG yoffset = point.y - m_StartPos.y;
		rect.left += xoffset;
		rect.right += xoffset;
		rect.top += yoffset;
		rect.bottom += yoffset;
		this->MoveWindow(&rect, 0);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


afx_msg void RenderDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialogEx::OnShowWindow(bShow, nStatus);

    // TODO: �ڴ˴������Ϣ����������
    if (bShow)
    {
        m_capture->Start();
    }
    else
    {
        m_capture->Stop();
    }
}


void RenderDlg::OnTopWindow()
{
    LONG exStyle = GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE);
    if (exStyle&WS_EX_TOPMOST)
    {
        m_ContextMenu.ModifyMenu(WM_TOPMOST, MF_BYCOMMAND|MF_STRING, WM_TOPMOST,TEXT("����������ǰ"));
        SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    }
    else
    {
        m_ContextMenu.ModifyMenu(WM_TOPMOST, MF_BYCOMMAND|MF_STRING, WM_TOPMOST, TEXT("ȡ��������ǰ"));
        SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    }
}


LRESULT RenderDlg::OnSetRenderSize(WPARAM wParam, LPARAM lParam)
{
	RECT* prcSrc = (RECT*)lParam;
	RECT rcWin;
	GetWindowRect(&rcWin);
	rcWin = LetterBoxRect(*prcSrc, rcWin);
	//MoveWindow(rcWin.left, rcWin.top, rcWin.right - rcWin.left, rcWin.bottom - rcWin.top, FALSE);
	MoveWindow(&rcWin, FALSE);

	return NULL;
}


void RenderDlg::SetVideoSource(Capture* capture)
{
    m_capture = capture;
}