
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
    , m_RecordStatus(0)
    , m_dwStartTime(0)
    , m_dwPauseTime(0)
    , m_dwPauseDuration(0)
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
	ON_BN_CLICKED(IDC_BTN_CONFIG, &CRhinoDlg::OnShowConfigDlg)
    ON_BN_CLICKED(IDC_BTN_RECORD, &CRhinoDlg::OnStartRecord)
    ON_BN_CLICKED(IDC_BTN_PAUSE, &CRhinoDlg::OnPauseRecord)
	ON_BN_CLICKED(IDC_BTN_STOP, &CRhinoDlg::OnStopRecord)
	ON_MESSAGE(WM_NOTYFICATION_MESSAGE, OnNotifyMsg)
	ON_WM_HOTKEY()
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

    config = new Config(TEXT("config.dat"));
    m_configDlg.Create(IDD_CONFIG_DIALOG, this);
    m_configDlg.SetConfig(config);
	m_renderDlg.Create(IDD_RENDER_DIALOG, this);

	BOOL ret;

	//Initialize NotifyIcon
	m_NotifyIcon.cbSize = sizeof(NOTIFYICONDATA);
	m_NotifyIcon.hWnd = this->m_hWnd;
	m_NotifyIcon.uID = IDR_MAINFRAME;
	m_NotifyIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	m_NotifyIcon.uCallbackMessage = WM_USER + 1000;
	m_NotifyIcon.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	lstrcpy(m_NotifyIcon.szTip, TEXT("Rhino Screen Recorder"));//ͼ����ʾΪ"���Գ���"
	ret = Shell_NotifyIcon(NIM_ADD, &m_NotifyIcon);//�����������ͼ��

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

    Render::Init(m_renderDlg.GetSafeHwnd());
 	Capture::Init();
	screenCapture = Capture::GetScreenCature(0);
    speakerCapture = Capture::GetSpeakerCature(0);
    cameraCapture = Capture::GetVideoCature(0);
    micCapture = Capture::GetAudioCature(0);

	codec = new Codec();
    render = Render::GetRender();
    screenCapture->AddSink(codec);
    speakerCapture->AddSink(codec);
    cameraCapture->AddSink(render);

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

    if (!config)
    {
        CDialogEx::OnClose();
        return;
    }

    SoftwareConfig softwareConfig;
    config->GetSoftwareConfig(softwareConfig);
    if (softwareConfig.bExitBtn)
    {
        CDialogEx::OnClose();
    }
    else
    {
        this->ShowWindow(SW_HIDE);
    }
}


void CRhinoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	Capture::Uninit();
    Render::Uninit();

	Shell_NotifyIcon(NIM_DELETE, &m_NotifyIcon);//ɾ��������ͼ��

	m_configDlg.DestroyWindow();
	m_renderDlg.DestroyWindow();

    if (codec)
    {
        delete codec;
    }
    if (config)
    {
        delete config;
    }
}


void CRhinoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if (nIDEvent == TIMER_RECORDER)
	{
		CString debugstr;
		VideoCaptureStatistics statistics;
		screenCapture->GetStatistics(&statistics);
		debugstr.Format(TEXT("width:%d, height:%d, fps:%f, total:%d\n"), statistics.width, statistics.height, statistics.fps, statistics.totalCnt);
		OutputDebugString(debugstr);

        CStatic* pChild = (CStatic*)GetDlgItem(IDC_REC_TIME);
        if (m_RecordStatus == 2)
        {
            time_t curTime = time(NULL);
            DWORD time = curTime - m_dwStartTime - m_dwPauseDuration;
            DWORD hour = time / 60 / 60;
            DWORD minute = time / 60 % 60;
            DWORD second = time % 60;
            CString timestr;
			timestr.Format(TEXT("%02d:%02d:%02d(%1.0f)"), hour, minute, second, statistics.fps);
            pChild->SetWindowText(timestr);
        }else if (m_RecordStatus == 1)
        {
            if (pChild->IsWindowVisible())
            {
                pChild->ShowWindow(SW_HIDE);
            }
            else
            {
                pChild->ShowWindow(SW_SHOW);
            }
        }
    }

	CDialogEx::OnTimer(nIDEvent);
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
        m_configDlg.ShowAboutTab();
	}
		break;
	case WM_SWITCH_CAMERA:{
		BOOL visibale = m_renderDlg.IsWindowVisible();
		if (visibale == FALSE)
		{
            m_renderDlg.ShowWindow(SW_SHOW);
            cameraCapture->Start();
		}
		else {
			cameraCapture->Stop();
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
    m_configDlg.ShowAboutTab();
}


void CRhinoDlg::OnShowCameraDlg()
{
	m_renderDlg.ShowWindow(SW_SHOW);
    cameraCapture->Start();
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
    if (m_RecordStatus == 2)
    {
        return;
    }

    CWnd* pChild = NULL;

    pChild = GetDlgItem(IDC_BTN_RECORD);
    pChild->ShowWindow(SW_HIDE);
    pChild = GetDlgItem(IDC_BTN_PAUSE);
    pChild->ShowWindow(SW_SHOW);
    pChild = GetDlgItem(IDC_BTN_STOP);
    pChild->EnableWindow(TRUE);
    pChild = GetDlgItem(IDC_REC_TIME);
    pChild->ShowWindow(SW_SHOW);

    if (m_RecordStatus == 0)
    {
        m_dwStartTime = time(NULL);
        m_dwPauseTime = 0;
        m_dwPauseDuration = 0;
        SetTimer(TIMER_RECORDER, 1000, NULL);
    } 
    else if(m_RecordStatus == 1)
    {
        time_t curTime = time(NULL);
        m_dwPauseDuration += curTime - m_dwPauseTime;
        SetTimer(TIMER_RECORDER, 1000, NULL);
    }

    m_RecordStatus = 2;

    m_NotifyIcon.uFlags = NIF_TIP;
    lstrcpy(m_NotifyIcon.szTip, TEXT("Rhino Screen Recorder\n����¼��"));//
    Shell_NotifyIcon(NIM_MODIFY, &m_NotifyIcon);//�����������ͼ��

    CodecConfig codecConfig;
    config->GetCodecConfig(codecConfig);

	VideoCaptureAttribute v_cap_attribute = { 0 };
	screenCapture->GetConfig(&v_cap_attribute);
	v_cap_attribute.fps = codecConfig.videoFps;
	screenCapture->SetConfig(&v_cap_attribute);
	screenCapture->Start();
    
    speakerCapture->Start();

	screenCapture->GetConfig(&v_cap_attribute);
    AudioCaptureAttribute a_cap_attribute = {0};
    micCapture->GetConfig(&a_cap_attribute);

	VideoCodecAttribute v_attribute = { 0 };
	v_attribute.width = v_cap_attribute.width;
	v_attribute.height = v_cap_attribute.height;
	v_attribute.fps = codecConfig.videoFps;
	v_attribute.profile = codecConfig.videoProfile;
	v_attribute.bitrate = codecConfig.videoBitrate;
	codec->SetVideoCodecAttribute(&v_attribute);

    AudioCodecAttribute a_attribute = { 0 };
    a_attribute.samplerate = a_cap_attribute.samplerate;
    a_attribute.channel = a_cap_attribute.channel;
    a_attribute.bitwide = a_cap_attribute.bitwide;
    a_attribute.profile = codecConfig.audioProfile;
    a_attribute.bitrate = codecConfig.audioBitrate;
    codec->SetAudioCodecAttribute(&a_attribute);

	codec->Start();
}


void CRhinoDlg::PauseRecord()
{
    CWnd* pChild = NULL;

    if (m_RecordStatus == 2)
    {
        m_RecordStatus = 1;
        pChild = GetDlgItem(IDC_BTN_RECORD);
        pChild->ShowWindow(SW_SHOW);
        pChild = GetDlgItem(IDC_BTN_PAUSE);
        pChild->ShowWindow(SW_HIDE);

        m_NotifyIcon.uFlags = NIF_TIP;
        lstrcpy(m_NotifyIcon.szTip, TEXT("Rhino Screen Recorder\n¼����ͣ"));//ͼ����ʾΪ"���Գ���"
        Shell_NotifyIcon(NIM_MODIFY, &m_NotifyIcon);//�����������ͼ��

        m_dwPauseTime = time(NULL);
        SetTimer(TIMER_RECORDER, 500, NULL);
    }
}


void CRhinoDlg::StopRecord()
{
    if (m_RecordStatus!=0)
    {
        m_RecordStatus = 0;
        m_dwPauseDuration = 0;

        speakerCapture->Stop();
		screenCapture->Stop();
		codec->Stop();

        KillTimer(TIMER_RECORDER);

        CWnd* pChild = NULL;

        pChild = GetDlgItem(IDC_BTN_RECORD);
        pChild->ShowWindow(SW_SHOW);
        pChild = GetDlgItem(IDC_BTN_PAUSE);
        pChild->ShowWindow(SW_HIDE);
        pChild = GetDlgItem(IDC_BTN_STOP);
        pChild->EnableWindow(FALSE);
        pChild = GetDlgItem(IDC_REC_TIME);
        pChild->ShowWindow(SW_SHOW);
        pChild->SetWindowText(TEXT("00:00:00"));

        m_NotifyIcon.uFlags = NIF_TIP;
        lstrcpy(m_NotifyIcon.szTip, TEXT("Rhino Screen Recorder"));//ͼ����ʾΪ"���Գ���"
        Shell_NotifyIcon(NIM_MODIFY, &m_NotifyIcon);//�����������ͼ��
    }
}

