#pragma once


// RenderDlg �Ի���

class RenderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RenderDlg)

public:
	RenderDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RenderDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RENDER_DIALOG };
#endif

private:
	CMenu m_ContextMenu;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
};
