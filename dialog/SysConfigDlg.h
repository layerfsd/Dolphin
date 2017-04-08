#pragma once


// SysConfigDlg �Ի���

class SysConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SysConfigDlg)

public:
	SysConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SysConfigDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_SYS_DLG };
#endif

public:
	void InitConfig(SoftwareConfig& soft);
	void GetConfig(SoftwareConfig& soft);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL m_bCloseCmd;
	BOOL m_bMinimizeCmd;
};
