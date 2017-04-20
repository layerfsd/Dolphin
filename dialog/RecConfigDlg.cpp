// F:\Workspace\MediaStudio\Dolphin\dialog\RecConfigDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../Config.h"
#include "../Dolphin.h"
#include "RecConfigDlg.h"
#include "afxdialogex.h"


// RecConfigDlg �Ի���

IMPLEMENT_DYNAMIC(RecConfigDlg, CDialogEx)

RecConfigDlg::RecConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONFIG_REC_DLG, pParent)
	, m_RecordFmt(0)
	, m_RecordDiv(0)
	, m_RecordPath(_T(""))
	, m_RecordName(_T(""))
{

}

RecConfigDlg::~RecConfigDlg()
{
}

void RecConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_RECORD_FMT, m_RecordFmt);
	DDX_Text(pDX, IDC_RECORD_DIV, m_RecordDiv);
	DDX_Text(pDX, IDC_RECORD_DIR, m_RecordPath);
	DDX_Text(pDX, IDC_RECORD_FILE, m_RecordName);
}


BEGIN_MESSAGE_MAP(RecConfigDlg, CDialogEx)
END_MESSAGE_MAP()


// RecConfigDlg ��Ϣ�������


BOOL RecConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void RecConfigDlg::InitConfig(RecordConfig& rec)
{
	m_RecordFmt = rec.recordFmt;
	m_RecordDiv = rec.recordDiv;
	m_RecordPath = rec.recordDir;
	m_RecordName = rec.recordName;

	this->UpdateData(FALSE);
}


void RecConfigDlg::GetConfig(RecordConfig& rec)
{
	this->UpdateData(TRUE);

	rec.recordFmt = m_RecordFmt;
	rec.recordDiv = m_RecordDiv;
	wcscpy(rec.recordDir, m_RecordPath);
	wcscpy(rec.recordName, m_RecordName);
}