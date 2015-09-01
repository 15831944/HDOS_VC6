// HealthCardReaderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HealthCardReader.h"
#include "HealthCardReaderDlg.h"
#include "DialogWritePublishInfo.h"
#include "DialogWritePersonInfo.h"
#include "DialogWriteOwnerInfo.h"
#include "DialogWriteAddrInfo.h"
#include "DialogWriteRelativeInfo.h"
#include "DialogWriteJobMarryInfo.h"
#include "DialogWriteLicenceInfo.h"
#include "DialogWriteClinicalInfo.h"
#include "DialogWriteSpecialInfo.h"
#include "DialogWriteAllergyRecord.h"
#include "DialogAddImmuneRecord.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHealthCardReaderDlg dialog

CHealthCardReaderDlg::CHealthCardReaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHealthCardReaderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHealthCardReaderDlg)
	m_sData = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHealthCardReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHealthCardReaderDlg)
	DDX_Control(pDX, IDC_COMBO_OUTPATIENT_INFO, m_comboOutpatientInfo);
	DDX_Control(pDX, IDC_COMBO_INHOSPITAL_INFO, m_comboInhospitalInfo);
	DDX_Control(pDX, IDC_COMBO_INHOSPITAL_RECORD2, m_comboOutpatient);
	DDX_Control(pDX, IDC_COMBO_INHOSPITAL_RECORD, m_comboInHospital);
	DDX_Control(pDX, IDC_COMBO_IMMUNE_RECORD, m_comboImmune);
	DDX_Control(pDX, IDC_COMBO_ALLERGY_RECORD, m_comboAllergy);
	DDX_Text(pDX, IDC_EDIT_DATA, m_sData);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHealthCardReaderDlg, CDialog)
	//{{AFX_MSG_MAP(CHealthCardReaderDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CONNECT_DEV, OnBtnConnectDev)
	ON_BN_CLICKED(IDC_BTN_CLOSE_DEV, OnBtnCloseDev)
	ON_BN_CLICKED(IDC_BTN_PSAM_ON, OnBtnPsamOn)
	ON_BN_CLICKED(IDC_BTN_VERIFY_PIN, OnBtnVerifyPin)
	ON_BN_CLICKED(IDC_BTN_HEALTH_ON, OnBtnHealthOn)
	ON_BN_CLICKED(IDC_BTN_READ_PUBLISHINFO, OnBtnReadPublishinfo)
	ON_BN_CLICKED(IDC_BTN_WRITE_PUBLISHINFO, OnBtnWritePublishinfo)
	ON_BN_CLICKED(IDC_BTN_READ_PERSONINFO, OnBtnReadPersoninfo)
	ON_BN_CLICKED(IDC_BTN_WRITE_PERSONINFO, OnBtnWritePersoninfo)
	ON_BN_CLICKED(IDC_BTN_READ_PIC, OnBtnReadPic)
	ON_BN_CLICKED(IDC_BTN_WRITE_PIC, OnBtnWritePic)
	ON_BN_CLICKED(IDC_BTN_READ_OWNERINFO, OnBtnReadOwnerinfo)
	ON_BN_CLICKED(IDC_BTN_WRITE_OWNERINFO, OnBtnWriteOwnerinfo)
	ON_BN_CLICKED(IDC_BTN_READ_ADDRINFO, OnBtnReadAddrinfo)
	ON_BN_CLICKED(IDC_BTN_WRITE_ADDRINFO, OnBtnWriteAddrinfo)
	ON_BN_CLICKED(IDC_BTN_READ_RELATIVEINFO, OnBtnReadRelativeinfo)
	ON_BN_CLICKED(IDC_BTN_WRITE_RELATIVEINFO, OnBtnWriteRelativeinfo)
	ON_BN_CLICKED(IDC_BTN_READ_JOBMARRYINFO, OnBtnReadJobmarryinfo)
	ON_BN_CLICKED(IDC_BTN_WRITE_JOBMARRYINFO, OnBtnWriteJobmarryinfo)
	ON_BN_CLICKED(IDC_BTN_READ_LICENCEINFO, OnBtnReadLicenceinfo)
	ON_BN_CLICKED(IDC_BTN_WRITE_LICENCEINFO, OnBtnWriteLicenceinfo)
	ON_BN_CLICKED(IDC_BTN_READ_CLINICALINFO, OnBtnReadClinicalinfo)
	ON_BN_CLICKED(IDC_BTN_WRITE_CLINICALINFO, OnBtnWriteClinicalinfo)
	ON_BN_CLICKED(IDC_BTN_READ_SPECIALINFO, OnBtnReadSpecialinfo)
	ON_BN_CLICKED(IDC_BTN_WRITE_SPECIALINFO, OnBtnWriteSpecialinfo)
	ON_BN_CLICKED(IDC_BTN_READ_ALLERGY_RECORD, OnBtnReadAllergyRecord)
	ON_BN_CLICKED(IDC_BTN_ADD_ALLERGY_RECORD, OnBtnAddAllergyRecord)
	ON_BN_CLICKED(IDC_BTN_READ_IMMUNE_RECORD, OnBtnReadImmuneRecord)
	ON_BN_CLICKED(IDC_BTN_ADD_IMMUNE_RECORD, OnBtnAddImmuneRecord)
	ON_BN_CLICKED(IDC_BTN_READ_INHOSPITAL_RECORD, OnBtnReadInhospitalRecord)
	ON_BN_CLICKED(IDC_BTN_WRITE_INHOSPITAL_RECORD, OnBtnWriteInhospitalRecord)
	ON_BN_CLICKED(IDC_BTN_CLEAR_INHOSPITAL_RECORD, OnBtnClearInhospitalRecord)
	ON_BN_CLICKED(IDC_BTN_READ_OUTPATIENT_RECORD, OnBtnReadOutpatientRecord)
	ON_BN_CLICKED(IDC_BTN_WRITE_OUTPATIENT_RECORD, OnBtnWriteOutpatientRecord)
	ON_BN_CLICKED(IDC_BTN_CLEAR_OUTPATIENT_RECORD, OnBtnClearOutpatientRecord)
	ON_BN_CLICKED(IDC_BTN_READ_INHOSPITALINFO, OnBtnReadInhospitalinfo)
	ON_BN_CLICKED(IDC_BTN_WRITE_INHOSPITALINFO, OnBtnWriteInhospitalinfo)
	ON_BN_CLICKED(IDC_BTN_READ_ALLINHOSPITALINFO, OnBtnReadAllinhospitalinfo)
	ON_BN_CLICKED(IDC_BTN_WRITE_ALLINHOSPITALINFO, OnBtnWriteAllinhospitalinfo)
	ON_BN_CLICKED(IDC_BTN_READ_OUTPATIENTINFO, OnBtnReadOutpatientinfo)
	ON_BN_CLICKED(IDC_BTN_READ_ALLOUTPATIENTINFO, OnBtnReadAlloutpatientinfo)
	ON_BN_CLICKED(IDC_BTN_WRITE_OUTPATIENTINFO, OnBtnWriteOutpatientinfo)
	ON_BN_CLICKED(IDC_BTN_WRITE_ALLOUTPATIENTINFO, OnBtnWriteAlloutpatientinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHealthCardReaderDlg message handlers

BOOL CHealthCardReaderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//this->SetDlgItemText(IDC_EDIT_PIN,"1234");
	m_comboAllergy.SetCurSel(0);
	m_comboImmune.SetCurSel(0);
	m_comboInHospital.SetCurSel(0);
	m_comboOutpatient.SetCurSel(0);
	m_comboInhospitalInfo.SetCurSel(0);
	m_comboOutpatientInfo.SetCurSel(0);
//	m_combobox.SetCurSel(0);
//	m_slot.SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHealthCardReaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHealthCardReaderDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHealthCardReaderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHealthCardReaderDlg::OnBtnConnectDev() 
{
	int i=iDOpenPort();
	if(i!=0)
	{
		this->MessageBox("���豸ʧ��!");
		return;
	}
	this->UpdateData();
	m_sData+="�����豸�ɹ�!\r\n";
	this->UpdateData(FALSE);

//�������ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}



	//sam���ϵ�
	memset(ATR,0x00,100);
	re=PowerOn(hDev,0x11,ATR);
	if(re!=0)
	{
		this->MessageBox("SAM���ϵ�ʧ��!");
		return;
	}
	this->UpdateData();
	m_sData+="sam���ϵ�ɹ�!\r\n";
	this->UpdateData(FALSE);

	//sam��У��
//	CString sPIN="123456";
//	//this->GetDlgItemText(IDC_EDIT_PIN,sPIN);
//	re=iVerifyPIN(hDev,sPIN.GetBuffer(0));
//	if(re!=0)
//	{
//		this->MessageBox("PSAM��У��ʧ��!");
//		return;
//	}
//	this->UpdateData();
//	m_sData+="PSAM��У��ɹ�!\r\n";
//	this->UpdateData(FALSE);

	////////////
	/*
typedef struct st_itemselect_
{
	WORD	wItemFlag;				  // ���������
	WORD	wID;					  // ��¼�ļ�ID
	VOID	*pValue;				  // ���ݵ�ַ 
	WORD	wValueLen;				  // ���ݳ���
	DWORD	*pdwErrCode;	
}ITEMSELECT, *P_ITEMSELECT;	
*/
//	ITEMSELECT p={0};
//	DWORD pdwErrCode;
//	char data[100]={0};
//	p.wItemFlag=3;
//	p.pValue=data;
//	p.wValueLen=4000;
//	//p.pdwErrCode=&pdwErrCode;
//	HANDLE hCard;
//	i=wsc_GetCardInfo(hCard,&p,1);
}

void CHealthCardReaderDlg::OnBtnCloseDev() 
{
	hDev=(HANDLE)iDClosePort();
	if(hDev!=0)
	{
		this->MessageBox("�ر��豸ʧ��!");
		return;
	}
	this->UpdateData();
	m_sData+="�ر��豸�ɹ�!\r\n";
	this->UpdateData(FALSE);
//	GetDlgItem(IDC_BTN_CLOSE_DEV)->ShowWindow(SW_HIDE); 
//	GetDlgItem(IDC_BTN_CONNECT_DEV)->ShowWindow(SW_SHOW); 
}

void CHealthCardReaderDlg::OnBtnPsamOn() 
{
	char ATR[100]={0};
	int re=PowerOn(hDev,0x11,ATR);
	if(re!=0)
	{
		this->MessageBox("SAM���ϵ�ʧ��!");
		return;
	}
	this->UpdateData();
	m_sData+=ATR;
	m_sData+="\r\n";
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnVerifyPin() 
{
	CString sPIN;
	this->GetDlgItemText(IDC_EDIT_PIN,sPIN);
	int re=iVerifyPIN(hDev,sPIN.GetBuffer(0));
	if(re!=0)
	{
		this->MessageBox("PSAM��У��ʧ��!");
		return;
	}
	this->UpdateData();
	m_sData+="PINУ��ɹ�\r\n";
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnHealthOn() 
{	
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	this->UpdateData();
	m_sData+=ATR;
	m_sData+="\r\n";
	this->UpdateData(FALSE);
}
//char KLB[100];
//char GFBB[100];
void CHealthCardReaderDlg::OnBtnReadPublishinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}

	char KLB[100]={0};
	//char *KLB;
	char GFBB[100]={0};
	char FKJGMC[100]={0};
	char FKJGDM[100]={0};
	char FKJGZS[500]={0};
	char FKSJ[100]={0};
	char KH[100]={0};
	char AQM[100]={0}; 
	char XPXLH[100]={0}; 
	char YYCSDM[100]={0};
	re=iR_DDF1EF05Info(hDev,KLB,GFBB, FKJGMC, FKJGDM, FKJGZS, FKSJ, KH, AQM, XPXLH, YYCSDM);
	if(re!=0)
	{
		this->MessageBox("��ȡ��������������Ϣʧ��!");
		return;
	}
	this->UpdateData();
	CString temp;
	temp.Format("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n",KLB,GFBB, FKJGMC, FKJGDM, FKJGZS, FKSJ, KH, AQM, XPXLH, YYCSDM);
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWritePublishinfo() 
{
	CDialogWritePublishInfo Dlg;
	Dlg.hDev=hDev;
	Dlg.pDlg=this;
	Dlg.DoModal();
}

void CHealthCardReaderDlg::OnBtnReadPersoninfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=0;
	//int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	char XM[50]={0};             //����
	char XB[50]={0};               //�Ա����
	char MZ[50]={0};               //�������
	char CSRQ[50]={0};             //�������ڣ�YYYYMMDD��ʽ
	char SFZH[50]={0};            //�������֤��
	re=iR_DDF1EF06Info(hDev,XM,XB,MZ,CSRQ,SFZH);
	if(re!=0)
	{
		this->MessageBox("���ֿ��˻�����Ϣʧ��!");
		return;
	}
	this->UpdateData();
	CString temp;
	temp.Format("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n",XM,XB,MZ,CSRQ,SFZH);
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWritePersoninfo() 
{
	CDialogWritePersonInfo Dlg;
	Dlg.hDev=hDev;
	Dlg.pDlg=this;
	Dlg.DoModal();
}

void CHealthCardReaderDlg::OnBtnReadPic() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	unsigned char picData[3075]={0};
	re=iR_DDF1EF07Info(hDev,picData);
	if(re!=0)
	{
		this->UpdateData();
		CString temp;
		temp.Format("��Ƭ��ȡʧ��,�������:%d",re);
		m_sData=temp+"\r\n";
		this->UpdateData(FALSE);
		return;
	}
	CString temp;
	temp.Format("%02x%02x",picData[0],picData[1]);
	long len=strtol(temp,NULL,16);

	CFile file;
	CFileException e;
	if(!file.Open("zp.jpg",CFile::typeBinary|CFile::modeCreate|CFile::modeWrite, &e))
	{
		this->MessageBox("���ļ�ʧ��!");
		return ;
	}
	file.Write(picData+2,len);
	file.Close();

	this->UpdateData();
	m_sData="��ȡ��Ƭ�ɹ�,��Ƭzp.jpgλ�ڵ�ǰĿ¼\r\n";
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWritePic() 
{
	char *filter="Pic Files (*.jpg)|*.jpg";
	CFileDialog fileOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |OFN_NOCHANGEDIR,filter,NULL);
	if(IDOK ==fileOpen.DoModal())
	{
		CString FilePath=fileOpen.GetPathName();
		CFile file(FilePath,CFile::modeRead|CFile::typeBinary);
		long FileLen=file.GetLength();
		if(FileLen>3000)
		{
			this->MessageBox("�ļ�̫��������ѡ��!");
			return;
		}
		unsigned char picData[3075]={0};
		int i=0x11223344;
		if(*((char *)&i)==0x44)
		{
			//��
			picData[0]=*((char *)(&FileLen)+1);
			picData[1]=*(char *)(&FileLen);
		}else
		{
			//˳
			picData[0]=*(char *)(&FileLen);
			picData[1]=*((char *)(&FileLen)+1);
		}
		file.Read(picData+2,FileLen);
		int re=iW_DDF1EF07Info(hDev,picData);
		if(re==0)
		{
			this->UpdateData();
			m_sData="д����Ƭ�ɹ�\r\n";
			this->UpdateData(FALSE);
		}
		//CString FileName=file.GetFileName();
	}
}

void CHealthCardReaderDlg::OnBtnReadOwnerinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	char KYXQ[21]={0};			//����Ч��
	char BRDH1[21]={0};         //���˵绰1
	char BRDH2[21]={0};           //���˵绰2
	char YLFYZFFS1[21]={0};		  //ҽ�Ʒ���֧����ʽ1
	char YLFYZFFS2[21]={0};		  //ҽ�Ʒ���֧����ʽ2
	char YLFYZFFS3[21]={0};	
	re=iR_DDF1EF08Info(hDev,KYXQ,BRDH1,BRDH2,YLFYZFFS1,YLFYZFFS2,YLFYZFFS3);
	if(re!=0)
	{
		this->MessageBox("��ȡ�ֿ�����Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n",KYXQ,BRDH1,BRDH2,YLFYZFFS1,YLFYZFFS2,YLFYZFFS3);
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWriteOwnerinfo() 
{
	CDialogWriteOwnerInfo Dlg;
	Dlg.hDev=hDev;
	Dlg.pDlg=this;
	Dlg.DoModal();
}

void CHealthCardReaderDlg::OnBtnReadAddrinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	char DZLB1[21]={0};		
	char DZ1[120]={0};       
	char DZLB2[21]={0};     
	char DZ2[120]={0};		  

	re=iR_DF01EF05Info(hDev,DZLB1,DZ1,DZLB2,DZ2);
	if(re!=0)
	{
		this->MessageBox("��ȡ��ַ��Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("%s\r\n%s\r\n%s\r\n%s\r\n",DZLB1,DZ1,DZLB2,DZ2);
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWriteAddrinfo() 
{
	CDialogWriteAddrInfo Dlg;
	Dlg.hDev=hDev;
	Dlg.pDlg=this;
	Dlg.DoModal();
}

void CHealthCardReaderDlg::OnBtnReadRelativeinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	char LXRXM1[40]={0};		
	char LXRGX1[2]={0};       
	char LXRDH1[30]={0};
	char LXRXM2[40]={0};		
	char LXRGX2[2]={0};       
	char LXRDH2[30]={0}; 
	char LXRXM3[40]={0};		
	char LXRGX3[2]={0};       
	char LXRDH3[30]={0}; 

	re=iR_DF01EF06Info(hDev,LXRXM1,LXRGX1,LXRDH1,LXRXM2,LXRGX2,LXRDH2,LXRXM3,LXRGX3,LXRDH3);
	if(re!=0)
	{
		this->MessageBox("��ȡ��ϵ����Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n",LXRXM1,LXRGX1,LXRDH1,LXRXM2,LXRGX2,LXRDH2,LXRXM3,LXRGX3,LXRDH3);
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWriteRelativeinfo() 
{
	CDialogWriteRelativeInfo Dlg;
	Dlg.hDev=hDev;
	Dlg.pDlg=this;
	Dlg.DoModal();
}

void CHealthCardReaderDlg::OnBtnReadJobmarryinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	char WHCD[10]={0};		
	char HYZK[10]={0};       
	char ZY[10]={0};

	re=iR_DF01EF07Info(hDev,WHCD,HYZK,ZY);
	if(re!=0)
	{
		this->MessageBox("��ȡְҵ������Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("%s\r\n%s\r\n%s\r\n",WHCD,HYZK,ZY);
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWriteJobmarryinfo() 
{
	CDialogWriteJobMarryInfo Dlg;
	Dlg.hDev=hDev;
	Dlg.pDlg=this;
	Dlg.DoModal();
}

void CHealthCardReaderDlg::OnBtnReadLicenceinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	char ZJLB[20]={0};		
	char ZJHM[20]={0};       
	char JKDAH[20]={0};
	char XNHZH[20]={0};

	re=iR_DF01EF08Info(hDev,ZJLB,ZJHM,JKDAH,XNHZH);
	if(re!=0)
	{
		this->MessageBox("��ȡְҵ������Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("%s\r\n%s\r\n%s\r\n%s\r\n",ZJLB,ZJHM,JKDAH,XNHZH);
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWriteLicenceinfo() 
{
	CDialogWriteLicenceInfo Dlg;
	Dlg.hDev=hDev;
	Dlg.pDlg=this;
	Dlg.DoModal();
}

void CHealthCardReaderDlg::OnBtnReadClinicalinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	char ABOXX[10]={0};		
	char RHXX[10]={0};       
	char XCBZ[10]={0};
	char XZBBZ[10]={0};
	char XNXGBBZ[10]={0};         //����Ѫ�ܲ���־
	char DXBBZ[10]={0};           //��ﲡ��־
	char NXWLBZ[10]={0};          //��Ѫ���ұ�־
	char TNBBZ[10]={0};           //���򲡱�־
	char QGYBZ[10]={0};           //����۱�־
	char TXBZ[10]={0};          //͸����־
	char QGYZBZ[10]={0};          //������ֲ��־
	char QGQSBZ[10]={0};        //����ȱʧ��־
	char KZXYZBZ[10]={0};         //��װж��֫��־
	char XZQBQBZ[10]={0};        //����������־
	char QTYXJSMC[50]={0};

	re=iR_DF02EF05Info(hDev,ABOXX,RHXX,XCBZ,XZBBZ,XNXGBBZ,DXBBZ,NXWLBZ,TNBBZ,QGYBZ,TXBZ,QGYZBZ,QGQSBZ,KZXYZBZ,XZQBQBZ,QTYXJSMC);
	if(re!=0)
	{
		this->MessageBox("��ȡ�ٴ�������Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n",ABOXX,RHXX,XCBZ,XZBBZ,XNXGBBZ,DXBBZ,NXWLBZ,TNBBZ,QGYBZ,TXBZ,QGYZBZ,QGQSBZ,KZXYZBZ,XZQBQBZ,QTYXJSMC);
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWriteClinicalinfo() 
{
	CDialogWriteClinicalInfo Dlg;
	Dlg.hDev=hDev;
	Dlg.pDlg=this;
	Dlg.DoModal();
}

void CHealthCardReaderDlg::OnBtnReadSpecialinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	char JSBBZ[10]={0};		
	re=iR_DF02EF06Info(hDev,JSBBZ);
	if(re!=0)
	{
		this->MessageBox("��ȡ������Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("%s\r\n",JSBBZ);
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWriteSpecialinfo() 
{
	CDialogWriteSpecialInfo Dlg;
	Dlg.hDev=hDev;
	Dlg.pDlg=this;
	Dlg.DoModal();
}

void CHealthCardReaderDlg::OnBtnReadAllergyRecord() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboAllergy.GetCurSel();
	char GMWZMC[30]={0};	
	char GMFY[120]={0};
	re=iR_DF02EF07Info(hDev,i+1,GMWZMC,GMFY);
	if(re!=0)
	{
		this->MessageBox("��ȡ��������������Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("%s\r\n%s\r\n",GMWZMC,GMFY);
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnAddAllergyRecord() 
{
	CDialogWriteAllergyRecord Dlg;
	Dlg.hDev=hDev;
	Dlg.pDlg=this;
	Dlg.DoModal();
}

void CHealthCardReaderDlg::OnBtnReadImmuneRecord() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboImmune.GetCurSel();
	char MYJZMC[30]={0};	
	char MYJZSJ[10]={0};
	re=iR_DF02EF08Info(hDev,i+1,MYJZMC,MYJZSJ);
	if(re!=0)
	{
		this->MessageBox("��ȡ���߻�����Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("%s\r\n%s\r\n",MYJZMC,MYJZSJ);
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnAddImmuneRecord() 
{
	CDialogAddImmuneRecord Dlg;
	Dlg.hDev=hDev;
	Dlg.pDlg=this;
	Dlg.DoModal();
}

void CHealthCardReaderDlg::OnBtnReadInhospitalRecord() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboInHospital.GetCurSel();
	char ZYJLBS1[30]={0};	
	char ZYJLBS2[10]={0};
	char ZYJLBS3[10]={0};
	re=iR_DF03EF05Info(hDev,ZYJLBS1,ZYJLBS2,ZYJLBS3);
	if(re!=0)
	{
		this->MessageBox("��ȡסԺ��Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("%s\r\n%s\r\n%s\r\n",ZYJLBS1,ZYJLBS2,ZYJLBS3);
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWriteInhospitalRecord() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboInHospital.GetCurSel();
	re=iW_DF03EF05Info(hDev,i+1);
	if(re!=0)
	{
		this->MessageBox("дסԺ��Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("дסԺ��Ϣ�ɹ�");
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnClearInhospitalRecord() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboInHospital.GetCurSel();
	re=iErase_DF03EF05Info(hDev,i+1);
	if(re!=0)
	{
		this->MessageBox("����סԺ��Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("����סԺ��Ϣ�ɹ�");
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnReadOutpatientRecord() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboOutpatient.GetCurSel();
	char MZJLBS1[30]={0};	
	char MZJLBS2[10]={0};
	char MZJLBS3[10]={0};
	char MZJLBS4[10]={0};
	char MZJLBS5[10]={0};
	re=iR_DF03EF06Info(hDev,MZJLBS1,MZJLBS2,MZJLBS3,MZJLBS4,MZJLBS5);
	if(re!=0)
	{
		this->MessageBox("��ȡ��������ʧ��!");
		return;
	}
	CString temp;
	temp.Format("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n",MZJLBS1,MZJLBS2,MZJLBS3,MZJLBS4,MZJLBS5);
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWriteOutpatientRecord() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboOutpatient.GetCurSel();
	re=iW_DF03EF06Info(hDev,i+1);
	if(re!=0)
	{
		this->MessageBox("д��������ʧ��!");
		return;
	}
	CString temp;
	temp.Format("д���������ɹ�");
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnClearOutpatientRecord() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboOutpatient.GetCurSel();
	re=iErase_DF03EF06Info(hDev,i+1);
	if(re!=0)
	{
		this->MessageBox("������������ʧ��!");
		return;
	}
	CString temp;
	temp.Format("�������������ɹ�");
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnReadInhospitalinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboInhospitalInfo.GetCurSel();
	char szData[100]={0};	
	re=iR_DF03EEInfo(hDev,i+1,szData,0,70,AN_style);
	if(re!=0)
	{
		this->MessageBox("��ȡסԺ��Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("%s\r\n",szData);
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWriteInhospitalinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboInhospitalInfo.GetCurSel();
	char szData[100]={0};
	CString sData;
	this->GetDlgItemText(IDC_EDIT_INHOSPITAL_DATA,sData);
	memcpy(szData,sData.GetBuffer(0),sData.GetLength());
	re=iW_DF03EEInfo(hDev,i+1,szData,0,70,AN_style);
	if(re!=0)
	{
		this->MessageBox("дסԺ��Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("дסԺ��Ϣ�ɹ�");
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnReadAllinhospitalinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboInhospitalInfo.GetCurSel();
	char szData[3000]={0};
	re=iR_DF03EE_ALLInfo(hDev,i+1,szData);
	if(re!=0)
	{
		this->MessageBox("������סԺ��Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("%s\r\n",szData);
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWriteAllinhospitalinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboInhospitalInfo.GetCurSel();
	char szData[3000]={0};
	CString sData;
	this->GetDlgItemText(IDC_EDIT_INHOSPITAL_DATA,sData);
	memcpy(szData,sData.GetBuffer(0),sData.GetLength());
	re=iW_DF03EE_ALLInfo(hDev,i+1,szData);
	if(re!=0)
	{
		this->MessageBox("д����סԺ��Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("д����סԺ��Ϣ�ɹ�");
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnReadOutpatientinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboOutpatientInfo.GetCurSel();
	char szData[100]={0};	
	re=iR_DF03EDInfo(hDev,i+1,szData,0,70,AN_style);
	if(re!=0)
	{
		this->MessageBox("��ȡ������Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("%s\r\n",szData);
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnReadAlloutpatientinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboOutpatientInfo.GetCurSel();
	char szData[3000]={0};
	re=iR_DF03ED_ALLInfo(hDev,i+1,szData);
	if(re!=0)
	{
		this->MessageBox("������������Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("%s\r\n",szData);
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWriteOutpatientinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboOutpatientInfo.GetCurSel();
	char szData[100]={0};
	CString sData;
	this->GetDlgItemText(IDC_EDIT_OUTPATIENT_DATA,sData);
	memcpy(szData,sData.GetBuffer(0),sData.GetLength());
	re=iW_DF03EDInfo(hDev,i+1,szData,0,70,AN_style);
	if(re!=0)
	{
		this->MessageBox("д������Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("д������Ϣ�ɹ�");
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}

void CHealthCardReaderDlg::OnBtnWriteAlloutpatientinfo() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	int i=m_comboOutpatientInfo.GetCurSel();
	char szData[3000]={0};
	CString sData;
	this->GetDlgItemText(IDC_EDIT_OUTPATIENT_DATA,sData);
	memcpy(szData,sData.GetBuffer(0),sData.GetLength());
	re=iW_DF03ED_ALLInfo(hDev,i+1,szData);
	if(re!=0)
	{
		this->MessageBox("д����������Ϣʧ��!");
		return;
	}
	CString temp;
	temp.Format("д����������Ϣ�ɹ�");
	this->UpdateData();
	m_sData=temp;
	this->UpdateData(FALSE);
}
