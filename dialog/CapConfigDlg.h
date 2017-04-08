#pragma once


// CapConfigDlg �Ի���

class CapConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CapConfigDlg)

public:
	CapConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CapConfigDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_CAP_DLG };
#endif

private:
	virtual BOOL OnInitDialog();
	int m_VideoCapture;
	int m_VideoFormat;
	BOOL m_bCaptureSpeaker;
	BOOL m_bCaptureMic;

public:
	void InitConfig(CaptureConfig& capture);
	void GetConfig(CaptureConfig& capture);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
