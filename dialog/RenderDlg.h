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
	BOOL m_bMoving;
	CPoint m_StartPos;

	CMenu m_ContextMenu;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg LRESULT OnSetRenderSize(WPARAM wParam, LPARAM lParam);
};
