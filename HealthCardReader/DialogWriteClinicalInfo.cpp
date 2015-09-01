// DialogWriteClinicalInfo.cpp : implementation file
//

#include "stdafx.h"
#include "HealthCardReader.h"
#include "DialogWriteClinicalInfo.h"
#include "HealthCardReaderDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteClinicalInfo dialog


CDialogWriteClinicalInfo::CDialogWriteClinicalInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogWriteClinicalInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogWriteClinicalInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogWriteClinicalInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogWriteClinicalInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogWriteClinicalInfo, CDialog)
	//{{AFX_MSG_MAP(CDialogWriteClinicalInfo)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteClinicalInfo message handlers

void CDialogWriteClinicalInfo::OnOK() 
{	
	CDialog::OnOK();
}

void CDialogWriteClinicalInfo::OnBtnWrite() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	CHealthCardReaderDlg *dlg=(CHealthCardReaderDlg*)pDlg;
	CString ABOXX;           //ABOѪ�ʹ���
	CString RHXX;            //RHѪ�ʹ���
	CString XCBZ;            //������־
	CString XZBBZ;           //���ಡ��־
	CString XNXGBBZ;         //����Ѫ�ܲ���־
	CString DXBBZ;          //��ﲡ��־
	CString NXWLBZ;          //��Ѫ���ұ�־
	CString TNBBZ;          //���򲡱�־
	CString QGYBZ;           //����۱�־
	CString TXBZ;            //͸����־
	CString QGYZBZ;          //������ֲ��־
	CString QGQSBZ;          //����ȱʧ��־
	CString KZXYZBZ;         //��װж��֫��־
	CString XZQBQBZ;         //����������־
	CString QTYXJSMC;         //����ҽѧ��ʾ����                                                                                  
	this->GetDlgItemText(IDC_EDIT_ABOXX,ABOXX);
	this->GetDlgItemText(IDC_EDIT_RHXX,RHXX);
	this->GetDlgItemText(IDC_EDIT_XCBZ,XCBZ);
	this->GetDlgItemText(IDC_EDIT_XZBBZ,XZBBZ);
	this->GetDlgItemText(IDC_EDIT_XNXGBBZ,XNXGBBZ);
	this->GetDlgItemText(IDC_EDIT_DXBBZ,DXBBZ);
	this->GetDlgItemText(IDC_EDIT_NXWLBZ,NXWLBZ);
	this->GetDlgItemText(IDC_EDIT_TNBBZ,TNBBZ);
	this->GetDlgItemText(IDC_EDIT_QGYBZ,QGYBZ);
	this->GetDlgItemText(IDC_EDIT_TXBZ,TXBZ);
	this->GetDlgItemText(IDC_EDIT_QGYZBZ,QGYZBZ);
	this->GetDlgItemText(IDC_EDIT_QGQSBZ,QGQSBZ);
	this->GetDlgItemText(IDC_EDIT_KZXYZBZ,KZXYZBZ);
	this->GetDlgItemText(IDC_EDIT_XZQBQBZ,XZQBQBZ);
	this->GetDlgItemText(IDC_EDIT_QTYXJSMC,QTYXJSMC);
	re=iW_DF02EF05Info(hDev,ABOXX.GetBuffer(0),RHXX.GetBuffer(0),XCBZ.GetBuffer(0)
		,XZBBZ.GetBuffer(0),XNXGBBZ.GetBuffer(0),DXBBZ.GetBuffer(0)
		,NXWLBZ.GetBuffer(0),TNBBZ.GetBuffer(0),QGYBZ.GetBuffer(0)
		,TXBZ.GetBuffer(0),QGYZBZ.GetBuffer(0),QGQSBZ.GetBuffer(0)
		,KZXYZBZ.GetBuffer(0),XZQBQBZ.GetBuffer(0),QTYXJSMC.GetBuffer(0));
	if(re!=0)
	{
		CString temp;
		temp.Format("д��ʧ��,�������:%d\r\n",re);
		dlg->UpdateData();
		dlg->m_sData=temp;
		dlg->UpdateData(FALSE);
		CDialog::OnOK();
		return;
	}
	dlg->UpdateData();
	dlg->m_sData="д��ɹ�\r\n";
	dlg->UpdateData(FALSE);
	CDialog::OnOK();
}
