// ConfigDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../Rhino.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"


// ConfigDlg �Ի���

IMPLEMENT_DYNAMIC(ConfigDlg, CDialogEx)

ConfigDlg::ConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONFIG_DIALOG, pParent)
{

}

ConfigDlg::~ConfigDlg()
{
}

void ConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SET_TAB, m_mainTab);
}


BEGIN_MESSAGE_MAP(ConfigDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SAVE, &ConfigDlg::OnSave)
	ON_NOTIFY(TCN_SELCHANGE, IDC_SET_TAB, &ConfigDlg::OnTabChange)
END_MESSAGE_MAP()


// ConfigDlg ��Ϣ�������


BOOL ConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	LoadConfig();

	CTabCtrl* hTab = (CTabCtrl*)GetDlgItem(IDC_SET_TAB);
	hTab->InsertItem(0, TEXT("��������"));
	hTab->InsertItem(1, TEXT("¼������"));
	hTab->InsertItem(2, TEXT("�ɼ�����"));
	hTab->InsertItem(3, TEXT("ϵͳ����"));
	hTab->InsertItem(4, TEXT("����"));

	CRect rect;
	hTab->GetClientRect(&rect);
 	rect.top += 30;
	rect.bottom += 5;
	rect.left += 12;
	rect.right += 12;

	m_encConfigDlg.Create(IDD_CONFIG_ENC_DLG, this);
	m_encConfigDlg.InitConfig(m_codecConfig);
	m_encConfigDlg.MoveWindow(&rect);
	m_recConfigDlg.Create(IDD_CONFIG_REC_DLG, this);
	m_recConfigDlg.InitConfig(m_recordConfig);
	m_recConfigDlg.MoveWindow(&rect);
	m_capConfigDlg.Create(IDD_CONFIG_CAP_DLG, this);
	m_capConfigDlg.InitConfig(m_captureConfig);
	m_capConfigDlg.MoveWindow(&rect);
	m_sysConfigDlg.Create(IDD_CONFIG_SYS_DLG, this);
	m_sysConfigDlg.InitConfig(m_softConfig);
	m_sysConfigDlg.MoveWindow(&rect);

	m_encConfigDlg.ShowWindow(SW_SHOW);

	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void ConfigDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	SaveConfig();

	CDialogEx::OnOK();
}


void ConfigDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}


void ConfigDlg::OnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SaveConfig();
}


void ConfigDlg::SaveConfig()
{
	m_encConfigDlg.GetConfig(m_codecConfig);
	m_recConfigDlg.GetConfig(m_recordConfig);
	m_capConfigDlg.GetConfig(m_captureConfig);
	m_sysConfigDlg.GetConfig(m_softConfig);
}


void ConfigDlg::LoadConfig()
{

}


void ConfigDlg::OnTabChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CTabCtrl* hTab = (CTabCtrl*)GetDlgItem(IDC_SET_TAB);
	int sel = hTab->GetCurSel();
	switch (sel)
	{
	case 0:
		m_encConfigDlg.ShowWindow(SW_SHOW);
		m_recConfigDlg.ShowWindow(SW_HIDE);
		m_capConfigDlg.ShowWindow(SW_HIDE);
		m_sysConfigDlg.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_encConfigDlg.ShowWindow(SW_HIDE);
		m_recConfigDlg.ShowWindow(SW_SHOW);
		m_capConfigDlg.ShowWindow(SW_HIDE);
		m_sysConfigDlg.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_encConfigDlg.ShowWindow(SW_HIDE);
		m_recConfigDlg.ShowWindow(SW_HIDE);
		m_capConfigDlg.ShowWindow(SW_SHOW);
		m_sysConfigDlg.ShowWindow(SW_HIDE);
		break;
	case 3:
		m_encConfigDlg.ShowWindow(SW_HIDE);
		m_recConfigDlg.ShowWindow(SW_HIDE);
		m_capConfigDlg.ShowWindow(SW_HIDE);
		m_sysConfigDlg.ShowWindow(SW_SHOW);
		break;
	case 4:
		m_encConfigDlg.ShowWindow(SW_HIDE);
		m_recConfigDlg.ShowWindow(SW_HIDE);
		m_capConfigDlg.ShowWindow(SW_HIDE);
		m_sysConfigDlg.ShowWindow(SW_HIDE);
		break;
	}
}
