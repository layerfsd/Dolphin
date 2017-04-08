#pragma once


// EncConfigDlg �Ի���

class EncConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EncConfigDlg)

public:
	EncConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~EncConfigDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_ENC_DLG };
#endif

private:
	int m_VideoCodec;
	int m_VideoProfile;
	int m_VideoRCMethod;
	int m_VideoBitrate;
	int m_VideoFps;
	int m_VideoGop;
	int m_AudioCodec;
	int m_AudioProfile;
	int m_AudioRCMethod;
	int m_AudioBitrate;

public:
	void InitConfig(CodecConfig& codec);
	void GetConfig(CodecConfig& codec);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
