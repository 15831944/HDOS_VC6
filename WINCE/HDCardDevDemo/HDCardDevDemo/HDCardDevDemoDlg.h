// HDCardDevDemoDlg.h : ͷ�ļ�
//

#pragma once

// CHDCardDevDemoDlg �Ի���
class CHDCardDevDemoDlg : public CDialog
{
// ����
public:
	CHDCardDevDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HDCARDDEVDEMO_DIALOG };


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
	afx_msg void OnBnClickedBtnRead();
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnWrite();
	afx_msg void OnBnClickedBtnActive();
	afx_msg void OnBnClickedBtnAuth();
	afx_msg void OnBnClickedBtnCert();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	CString m_strbuf;
	unsigned char m_key;
};
