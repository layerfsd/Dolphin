
// RhinoDlg.h : ͷ�ļ�
//

#pragma once

#include "dialog/ConfigDlg.h"
#include "dialog/RenderDlg.h"

// CRhinoDlg �Ի���

class CRhinoDlg : public CDialogEx
{
// ����
public:
	CRhinoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RHINO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	HICON m_hIcon;
	CMenu m_NotifyMenu;
	NOTIFYICONDATA m_NotifyIcon;

	ConfigDlg m_configDlg;
	RenderDlg m_renderDlg;

    BYTE m_RecordStatus;

    DWORD m_dwStartTime;
    DWORD m_dwPauseTime;
    DWORD m_dwPauseDuration;

    Config * config = NULL;
	Codec* codec = NULL;
    Capture *screenCapture = NULL;
    Capture *speakerCapture = NULL;
    Capture *cameraCapture = NULL;
    Capture *micCapture = NULL;

	void StartRecord();
	void PauseRecord();
	void StopRecord();


// ʵ��
protected:

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	LRESULT OnNotifyMsg(WPARAM wparam, LPARAM lparam);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
protected:
    afx_msg void OnShowMainDlg();
    afx_msg void OnShowConfigDlg();
    afx_msg void OnShowAboutDlg();
    afx_msg void OnShowCameraDlg();
    afx_msg void OnStartRecord();
    afx_msg void OnPauseRecord();
    afx_msg void OnStopRecord();
};
