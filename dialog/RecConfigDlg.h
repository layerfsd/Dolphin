#pragma once


// RecConfigDlg �Ի���

class RecConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RecConfigDlg)

public:
	RecConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RecConfigDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_REC_DLG };
#endif

private:
	int m_RecordFmt;
	int m_RecordDiv;
	CString m_RecordPath;
	CString m_RecordName;

public:
	void InitConfig(RecordConfig& rec);
	void GetConfig(RecordConfig& rec);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
