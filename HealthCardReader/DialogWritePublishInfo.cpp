// DialogWritePublishInfo.cpp : implementation file
//

#include "stdafx.h"
#include "HealthCardReader.h"
#include "DialogWritePublishInfo.h"
#include "HealthCardReaderDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogWritePublishInfo dialog


CDialogWritePublishInfo::CDialogWritePublishInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogWritePublishInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogWritePublishInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogWritePublishInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogWritePublishInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogWritePublishInfo, CDialog)
	//{{AFX_MSG_MAP(CDialogWritePublishInfo)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogWritePublishInfo message handlers

void CDialogWritePublishInfo::OnBtnWrite() 
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
	CString KLB;          //��������                                                                                        
	CString  GFBB;            //�淶�汾                                                                                          
	CString  FKJGMC;          //������������                                                                                      
	CString  FKJGDM;          //������������ 
	CString  FKJGZS;			//��������֤��
	CString  FKSJ;          //����ʱ�䣬YYYYMMDD��ʽ                                                                            
	CString  KH;            //���ţ���������֤�Ż���֤������һ��
	CString  AQM;             //��ȫ��                                                                                            
	CString  XPXLH;           //оƬ���к�
	CString  YYCSDM;          //Ӧ�ó��д���
	this->GetDlgItemText(IDC_EDIT_KLB,KLB);
	this->GetDlgItemText(IDC_EDIT_GFBB,GFBB);
	this->GetDlgItemText(IDC_EDIT_FKJGMC,FKJGMC);
	this->GetDlgItemText(IDC_EDIT_FKJGDM,FKJGDM);
	this->GetDlgItemText(IDC_EDIT_FKJGZS,FKJGZS);
	this->GetDlgItemText(IDC_EDIT_FKSJ,FKSJ);
	this->GetDlgItemText(IDC_EDIT_KH,KH);
	this->GetDlgItemText(IDC_EDIT_AQM,AQM);
	this->GetDlgItemText(IDC_EDIT_XPXLH,XPXLH);
	this->GetDlgItemText(IDC_EDIT_YYCSDM,YYCSDM);
	re=iW_DDF1EF05Info(hDev,KLB.GetBuffer(0),GFBB.GetBuffer(0),FKJGMC.GetBuffer(0),FKJGDM.GetBuffer(0),FKJGZS.GetBuffer(0),FKSJ.GetBuffer(0),KH.GetBuffer(0),AQM.GetBuffer(0),XPXLH.GetBuffer(0),YYCSDM.GetBuffer(0));
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

void CDialogWritePublishInfo::OnOK() 
{
	CDialog::OnOK();
}
