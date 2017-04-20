// F:\Workspace\MediaStudio\Dolphin\dialog\CapConfigDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../Config.h"
#include "../Dolphin.h"
#include "CapConfigDlg.h"
#include "afxdialogex.h"


// CapConfigDlg �Ի���

IMPLEMENT_DYNAMIC(CapConfigDlg, CDialogEx)

CapConfigDlg::CapConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONFIG_CAP_DLG, pParent)
	, m_VideoCapture(0)
	, m_VideoFormat(0)
	, m_bCaptureSpeaker(TRUE)
	, m_bCaptureMic(TRUE)
{

}

CapConfigDlg::~CapConfigDlg()
{
}

void CapConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_VIDEO_CAP, m_VideoCapture);
	DDX_CBIndex(pDX, IDC_VIDEO_FMT, m_VideoFormat);
	DDX_Check(pDX, IDC_CAP_SPEAKER, m_bCaptureSpeaker);
	DDX_Check(pDX, IDC_CAP_MIC, m_bCaptureMic);
}


BEGIN_MESSAGE_MAP(CapConfigDlg, CDialogEx)
END_MESSAGE_MAP()


// CapConfigDlg ��Ϣ�������


BOOL CapConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CapConfigDlg::InitConfig(CaptureConfig& capture)
{
	m_VideoCapture = capture.videoCapIdx;
	m_VideoFormat = capture.videoFmtIdx;
	m_bCaptureSpeaker = capture.bCapSpeaker;
	m_bCaptureMic = capture.bCapMic;

	this->UpdateData(FALSE);
}


void CapConfigDlg::GetConfig(CaptureConfig& capture)
{
	this->UpdateData(TRUE);

	capture.videoCapIdx = m_VideoCapture;
	capture.videoFmtIdx = m_VideoFormat;
	capture.bCapSpeaker = m_bCaptureSpeaker;
	capture.bCapMic = m_bCaptureMic;
}