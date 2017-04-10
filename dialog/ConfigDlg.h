
// RhinoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "../Config.h"
#include "EncConfigDlg.h"
#include "CapConfigDlg.h"
#include "RecConfigDlg.h"
#include "SysConfigDlg.h"
#include "AboutDlg.h"

// ConfigDlg �Ի���

class ConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConfigDlg)

public:
	ConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ConfigDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_DIALOG };
#endif

private:
	CTabCtrl m_mainTab;
	EncConfigDlg m_encConfigDlg;
	CapConfigDlg m_capConfigDlg;
	RecConfigDlg m_recConfigDlg;
    SysConfigDlg m_sysConfigDlg;
    AboutDlg m_aboutDlg;

	CodecConfig    m_codecConfig;
	RecordConfig   m_recordConfig;
	CaptureConfig  m_captureConfig;
	SoftwareConfig m_softConfig;

	void SaveConfig();
	void LoadConfig();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    void ShowAboutTab();

	afx_msg void OnSave();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnTabChange(NMHDR *pNMHDR, LRESULT *pResult);
};