
// RhinoDlg.h : ͷ�ļ�
//

#pragma once

#include "dialog/ConfigDlg.h"
#include "dialog/RenderDlg.h"
#include "dialog/AboutDlg.h"

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
	AboutDlg m_aboutDlg;

    DWORD m_dwStartTime;

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
	afx_msg void OnClickBtnConfig();
	afx_msg void OnClickBtnRecord();
	afx_msg void OnClickBtnStop();

	LRESULT OnNotifyMsg(WPARAM wparam, LPARAM lparam);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
protected:
	void OnShowMainDlg();
	void OnShowConfigDlg();
	void OnShowAboutDlg();
	void OnShowCameraDlg();
	void OnStartRecord();
	void OnPauseRecord();
	void OnStopRecord();
};
