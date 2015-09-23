// CardDevDemoDlg.h : ͷ�ļ�
//

#pragma once

// CCardDevDemoDlg �Ի���
class CCardDevDemoDlg : public CDialog
{
// ����
public:
	CCardDevDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CARDDEVDEMO_DIALOG };

#ifdef WIN32_PLATFORM_WFSP
protected:  // �ؼ���Ƕ���Ա
	CCommandBar m_dlgCommandBar;
#endif // WIN32_PLATFORM_WFSP

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnActive();
	afx_msg void OnBnClickedBtnAuth();
	afx_msg void OnBnClickedRadio1();
	unsigned char m_key;
	afx_msg void OnBnClickedRadio2();
	CString m_strbuf;
	afx_msg void OnBnClickedBtnRead();
	afx_msg void OnBnClickedBtnWrite();
	afx_msg void OnBnClickedBtnCert();
};
