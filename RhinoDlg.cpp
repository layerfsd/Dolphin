
// RhinoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Rhino.h"
#include "RhinoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_NOTYFICATION_MESSAGE (WM_USER+1000)

#define WM_STARTRECORD (WM_USER+1001)
#define WM_PAUSERECORD (WM_USER+1002)
#define WM_STOPRECORD (WM_USER+1003)

#define WM_SHOW_MAIN_DLG (WM_USER+1004)
#define WM_SHOW_CONFIG_DLG (WM_USER+1005)
#define WM_SHOW_ABOUT_DLG (WM_USER+1006)


#define WM_SWITCH_CAMERA (WM_USER+1007)
#define WM_SWITCH_MIC (WM_USER+1008)

#define TIMER_RECORDER 1

LRESULT CALLBACK NotifyHookProc(int code, WPARAM wParam, LPARAM lParam);


// CRhinoDlg �Ի���



CRhinoDlg::CRhinoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RHINO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRhinoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRhinoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_CONFIG, &CRhinoDlg::OnClickBtnConfig)
	ON_BN_CLICKED(IDC_BTN_RECORD, &CRhinoDlg::OnClickBtnRecord)
	ON_BN_CLICKED(IDC_BTN_STOP, &CRhinoDlg::OnClickBtnStop)
	ON_MESSAGE(WM_NOTYFICATION_MESSAGE, OnNotifyMsg)
	ON_WM_HOTKEY()
	ON_COMMAND(WM_SHOW_CONFIG_DLG, &CRhinoDlg::OnShowConfigDlg)
	ON_COMMAND(WM_SHOW_MAIN_DLG, &CRhinoDlg::OnShowMainDlg)
	ON_COMMAND(WM_SHOW_CONFIG_DLG, &CRhinoDlg::OnShowConfigDlg)
	ON_COMMAND(WM_SHOW_ABOUT_DLG, &CRhinoDlg::OnShowAboutDlg)
	ON_COMMAND(WM_STARTRECORD, &CRhinoDlg::OnStartRecord)
	ON_COMMAND(WM_PAUSERECORD, &CRhinoDlg::OnPauseRecord)
	ON_COMMAND(WM_STOPRECORD, &CRhinoDlg::OnStopRecord)
END_MESSAGE_MAP()


// CRhinoDlg ��Ϣ�������

BOOL CRhinoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_configDlg.Create(IDD_CONFIG_DIALOG, this);
	m_renderDlg.Create(IDD_RENDER_DIALOG, this);
	m_aboutDlg.Create(IDD_ABOUT_DIALOG, this);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	BOOL ret;

	//Initialize NotifyIcon
	m_NotifyIcon.cbSize = sizeof(NOTIFYICONDATA);
	m_NotifyIcon.hWnd = this->m_hWnd;
	m_NotifyIcon.uID = IDR_MAINFRAME;
	m_NotifyIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	m_NotifyIcon.uCallbackMessage = WM_USER + 1000;
	m_NotifyIcon.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	lstrcpy(m_NotifyIcon.szTip, TEXT("Rhino Screen Recorder"));//ͼ����ʾΪ"���Գ���"
	Shell_NotifyIcon(NIM_ADD, &m_NotifyIcon);//�����������ͼ��

	//Initialize NotifyMenu
	m_NotifyMenu.CreatePopupMenu();
	m_NotifyMenu.AppendMenu(MF_STRING, WM_SHOW_MAIN_DLG, TEXT("������"));
	m_NotifyMenu.AppendMenu(MF_SEPARATOR);
	m_NotifyMenu.AppendMenu(MF_STRING, WM_STARTRECORD, TEXT("��ʼ¼��"));
	m_NotifyMenu.AppendMenu(MF_STRING, WM_STOPRECORD, TEXT("ֹͣ¼��"));
	m_NotifyMenu.AppendMenu(MF_SEPARATOR);
	m_NotifyMenu.AppendMenu(MF_STRING, WM_SHOW_CONFIG_DLG, TEXT("����"));
	m_NotifyMenu.AppendMenu(MF_STRING, WM_SHOW_ABOUT_DLG, TEXT("����"));
	m_NotifyMenu.AppendMenu(MF_SEPARATOR);
	m_NotifyMenu.AppendMenu(MF_STRING, WM_DESTROY, TEXT("�˳�"));

	//Register HotKey
	ret = RegisterHotKey(GetSafeHwnd(), WM_SHOW_MAIN_DLG, MOD_ALT | MOD_NOREPEAT, VK_F1);
	ret = RegisterHotKey(GetSafeHwnd(), WM_SHOW_CONFIG_DLG, MOD_ALT | MOD_NOREPEAT, VK_F2);
	ret = RegisterHotKey(GetSafeHwnd(), WM_SHOW_ABOUT_DLG, MOD_ALT | MOD_NOREPEAT, VK_F3);

	ret = RegisterHotKey(GetSafeHwnd(), WM_SWITCH_CAMERA, MOD_ALT | MOD_NOREPEAT, VK_F5);
	ret = RegisterHotKey(GetSafeHwnd(), WM_SWITCH_MIC, MOD_ALT | MOD_NOREPEAT, VK_F16);

	ret = RegisterHotKey(GetSafeHwnd(), WM_STARTRECORD, MOD_ALT | MOD_NOREPEAT, VK_F9);
	ret = RegisterHotKey(GetSafeHwnd(), WM_PAUSERECORD, MOD_ALT | MOD_NOREPEAT, VK_F10);
	ret = RegisterHotKey(GetSafeHwnd(), WM_STOPRECORD, MOD_ALT | MOD_NOREPEAT, VK_F11);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRhinoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRhinoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRhinoDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//this->ShowWindow(SW_MINIMIZE);
	CDialogEx::OnClose();
}


void CRhinoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	Shell_NotifyIcon(NIM_DELETE, &m_NotifyIcon);//ɾ��������ͼ��

	m_configDlg.DestroyWindow();
	m_renderDlg.DestroyWindow();
	m_aboutDlg.DestroyWindow();
}


void CRhinoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if (nIDEvent == TIMER_RECORDER)
    {
        time_t curTime = time(NULL);
        DWORD time = curTime - m_dwStartTime;
        DWORD hour = time / 60 / 60;
        DWORD minute = time / 60 % 60;
        DWORD second = time % 60;
        CStatic* pChild = (CStatic*)GetDlgItem(IDC_REC_TIME);
        CString str;
        str.Format(TEXT("%02d:%02d:%02d"), hour, minute, second);
        pChild->SetWindowText(str);
    }

	CDialogEx::OnTimer(nIDEvent);
}


void CRhinoDlg::OnClickBtnConfig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_configDlg.ShowWindow(SW_SHOW);
}


void CRhinoDlg::OnClickBtnRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    StartRecord();
}


void CRhinoDlg::OnClickBtnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    StopRecord();
}


LRESULT  CRhinoDlg::OnNotifyMsg(WPARAM wparam, LPARAM lparam)
//wParam���յ���ͼ���ID����lParam���յ���������Ϊ     
{
	if (wparam != IDR_MAINFRAME)
		return    1;
	switch (lparam)
	{
	case WM_RBUTTONUP://�Ҽ�����ʱ������ݲ˵�������ֻ��һ�����رա�     
	{
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);//�õ����λ��  
		this->SetForegroundWindow();

		//HHOOK hook = SetWindowsHookEx(WH_MSGFILTER, NotifyHookProc, NULL, GetCurrentThreadId());
		m_NotifyMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERNEGANIMATION, lpoint->x, lpoint->y, this);
		//UnhookWindowsHookEx(hook);

		delete    lpoint;
	}
	break;
	}
	return 0;
}

void CRhinoDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	switch (nHotKeyId)
	{
	case WM_SHOW_MAIN_DLG:
		this->ShowWindow(SW_SHOW);
		break;
	case WM_SHOW_CONFIG_DLG: {
		BOOL visibale = m_configDlg.IsWindowVisible();
		if (visibale == FALSE)
		{
			m_configDlg.ShowWindow(SW_SHOW);
		}
	}
		break;
	case WM_SHOW_ABOUT_DLG: {
		BOOL visibale = m_aboutDlg.IsWindowVisible();
		if (visibale == FALSE)
		{
			m_aboutDlg.ShowWindow(SW_SHOW);
		}
		else {
			m_aboutDlg.ShowWindow(SW_HIDE);
		}
	}
		break;
	case WM_SWITCH_CAMERA:{
		BOOL visibale = m_renderDlg.IsWindowVisible();
		if (visibale == FALSE)
		{
			m_renderDlg.ShowWindow(SW_SHOW);
		}
		else {
			m_renderDlg.ShowWindow(SW_HIDE);
		}
	}
		break;
	case WM_SWITCH_MIC:
		break;
	case WM_STARTRECORD:
		StartRecord();
		break;
	case WM_PAUSERECORD:
		PauseRecord();
		break;
	case WM_STOPRECORD:
		StopRecord();
		break;
	default:
		break;
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

LRESULT CALLBACK NotifyHookProc(int code, WPARAM wParam, LPARAM lParam)
{

	if (code==MSGF_MENU)
	{
		MSG* pMsg = (MSG*)lParam;
		if (pMsg->message == WM_MOUSEMOVE)
		{
			// �������꣬����굽��ĳ��λ����Ҫ���ٲ˵�ʱ����ӵ�в˵��Ĵ��ڷ���WM_CANCELMODE��Ϣ��
		}
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}


void CRhinoDlg::OnShowMainDlg()
{
	this->ShowWindow(SW_SHOW);
}


void CRhinoDlg::OnShowConfigDlg()
{
	m_configDlg.ShowWindow(SW_SHOW);
}


void CRhinoDlg::OnShowAboutDlg()
{
	m_aboutDlg.ShowWindow(SW_SHOW);
}


void CRhinoDlg::OnShowCameraDlg()
{
	m_renderDlg.ShowWindow(SW_SHOW);
}


void CRhinoDlg::OnStartRecord()
{
	StartRecord();
}


void CRhinoDlg::OnPauseRecord()
{
	PauseRecord();
}


void CRhinoDlg::OnStopRecord()
{
    StopRecord();
}


void CRhinoDlg::StartRecord()
{
    m_dwStartTime = time(NULL);
    SetTimer(TIMER_RECORDER, 1000, NULL);
}


void CRhinoDlg::PauseRecord()
{
}


void CRhinoDlg::StopRecord()
{
    KillTimer(TIMER_RECORDER);
}

