// InterfaceDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InterfaceDemo.h"
#include "InterfaceDemoDlg.h"
#include "InputDialog.h"
#include "dialogInput2.h"
#include "PSAMDialog.h"

#include "MHC_CardInterface.h"

#include "WINBASE.H"

#include <fstream>
using namespace std;


#define MAX_BIN_SIZE 0x1000

HANDLE g_hReader = 0; // 0 USB


char g_USER_ART[40] = {0};
char g_CSYY[7] = {0};

HANDLE g_handle = 0;

typedef struct st_itemselect_
{
	WORD	wItemFlag;				  // ���������
//	WORD	wID;					  // ��¼�ļ�ID
	VOID	*pValue;				  // ���ݵ�ַ 
	WORD	wValueLen;				  // ���ݳ���
	//DWORD	*pdwErrCode;	
}ITEMSELECT, *P_ITEMSELECT;	

/*
#define NO_style			0x00

#define AN_style			0x01
#define CN_style			0x0F
#define B_style				0xFF
*/

//char * DATA_TYPE_TEXT[4] =  {"NO_style", "AN_style", "CN_style", "B_style"};
//
//int DATA_TYPE_VALUE[4] = {
//							NO_style,
//							AN_style,
//							CN_style,
//							B_style
	//						};


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
// CInterfaceDemoDlg dialog

CInterfaceDemoDlg::CInterfaceDemoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CInterfaceDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInterfaceDemoDlg)
	m_out = _T("");
	m_PIN = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInterfaceDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterfaceDemoDlg)
	DDX_Control(pDX, IDC_COMBO_MYID, m_cbo_myid);
	DDX_Control(pDX, IDC_COMBO_GMID, m_cbo_gmid);
	DDX_Control(pDX, IDC_COMBO_ZYID, m_cbo_zyid);
	DDX_Control(pDX, IDC_COMBO_ZYBZID, m_cbo_zybzid);
	DDX_Control(pDX, IDC_COMBO_MZBZID, m_cbo_mzbzid);
	DDX_Control(pDX, IDC_COMBO_MZID, m_cbo_mzid);
	DDX_Control(pDX, IDC_LIST, m_cListBox);
	DDX_Text(pDX, IDC_EDIT_OUT, m_out);
	DDX_Text(pDX, IDC_EDITPIN, m_PIN);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInterfaceDemoDlg, CDialog)
//{{AFX_MSG_MAP(CInterfaceDemoDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON_FK_READ, OnButtonFkRead)
	ON_BN_CLICKED(IDC_BUTTON_CB_READ2, OnButtonCbRead2)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_GM_READ, OnButtonGmRead)
	ON_BN_CLICKED(IDC_BUTTON_MY_READ, OnButtonMyRead)
	ON_BN_CLICKED(IDC_BUTTON_ZZJLBS_READ, OnButtonZzjlbsRead)
	ON_BN_CLICKED(IDC_BUTTON_MZJLBS_READ, OnButtonMzjlbsRead)
	ON_BN_CLICKED(IDC_BUTTON_ZYXX, OnButtonZyxx)
	ON_BN_CLICKED(IDC_BUTTON_MZXX_READ, OnButtonMzxxRead)
	ON_BN_CLICKED(IDC_BUTTON_DIZHI_READ, OnButtonDizhiRead)
	ON_BN_CLICKED(IDC_BUTTON_LXR_READ, OnButtonLxrRead)
	ON_BN_CLICKED(IDC_BUTTON_ZYHY_READ, OnButtonZyhyRead)
	ON_BN_CLICKED(IDC_BUTTON_ZJJLXX_READ, OnButtonZjjlxxRead)
	ON_BN_CLICKED(IDC_BUTTON_LCJBSJ_READ, OnButtonLcjbsjRead)
	ON_BN_CLICKED(IDC_BUTTON_TSXX_READ, OnButtonTsxxRead)
	ON_BN_CLICKED(IDC_BUTTON_CKRJBXX_WRITE, OnButtonCkrjbxxWrite)
	ON_BN_CLICKED(IDC_BUTTON_FK_WRITE, OnButtonFkWrite)
	ON_BN_CLICKED(IDC_BUTTON_GM_WRITE, OnButtonGmWrite)
	ON_BN_CLICKED(IDC_BUTTON_MYJBSJ_WRITE, OnButtonMyjbsjWrite)
	ON_BN_CLICKED(IDC_BUTTON_ZYJL_WRITE, OnButtonZyjlWrite)
	ON_BN_CLICKED(IDC_BUTTON_ZZJLYX_ERASE, OnButtonZzjlyxErase)
	ON_BN_CLICKED(IDC_BUTTON_MZJLBS_WRITE, OnButtonMzjlbsWrite)
	ON_BN_CLICKED(IDC_BUTTON_MZJLBS_ERASE, OnButtonMzjlbsErase)
	ON_BN_CLICKED(IDC_BUTTON_ZYXX_WRITE, OnButtonZyxxWrite)
	ON_BN_CLICKED(IDC_BUTTON_MZXX_WRITE, OnButtonMzxxWrite)
	ON_BN_CLICKED(IDC_BUTTON_DZXX_WRITE, OnButtonDzxxWrite)
	ON_BN_CLICKED(IDC_BUTTON_LXRXX_WRITE, OnButtonLxrxxWrite)
	ON_BN_CLICKED(IDC_BUTTON1_ZYHYXX_WRITE, OnButton1ZyhyxxWrite)
	ON_BN_CLICKED(IDC_BUTTON_ZJJLXX_WRITE, OnButtonZjjlxxWrite)
	ON_BN_CLICKED(IDC_BUTTON_LCJBSJ_WRITE, OnButtonLcjbsjWrite)
	ON_BN_CLICKED(IDC_BUTTON_TSXXSJ_WRITE, OnButtonTsxxsjWrite)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_ZP_READ, OnButtonZpRead)
	ON_BN_CLICKED(IDC_BUTTON_WSB_READ, OnButtonWsbRead)
	ON_BN_CLICKED(IDC_BUTTON_WSB_WRITE, OnButtonWsbWrite)
	ON_BN_CLICKED(IDC_BUTTON_ZP_WRITE, OnButtonZpWrite)
	ON_BN_CLICKED(IDC_BUTTON_WSB_OPEN, OnButtonWsbOpen)
	ON_BN_CLICKED(IDC_BUTTON_WSB_CLOSE, OnButtonWsbClose)
	ON_BN_CLICKED(IDC_BUTTON_DIZHI_READ2, OnButtonDizhiRead2)
	ON_BN_CLICKED(IDC_BUTTON_DZXX_WRITE2, OnButtonDzxxWrite2)
	ON_BN_CLICKED(IDC_BUTTON_errmsg, OnBUTTONerrmsg)
	ON_BN_CLICKED(IDC_BUTTON_MZ_SIGN, OnButtonMzSign)
	ON_BN_CLICKED(IDC_BUTTON_ZY_SIGN, OnButtonZySign)
	ON_BN_CLICKED(IDC_BUTTON_PSAM, OnButtonPsam)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_RESETPSAM, OnButtonResetpsam)
	ON_BN_CLICKED(IDC_BUTTON_RESET3, OnButtonReset3)
	ON_BN_CLICKED(IDC_READALL, OnReadall)
	ON_BN_CLICKED(IDC_WRITEALL, OnWriteall)
	ON_BN_CLICKED(IDC_READEDLL, OnReadedll)
	ON_BN_CLICKED(IDC_WRITEEDLL, OnWriteedll)
	ON_BN_CLICKED(IDC_BTN_TESTZKR, OnBtnTestzkr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterfaceDemoDlg message handlers

BOOL CInterfaceDemoDlg::OnInitDialog()
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

	//gdi init ��ӿ��޹�
//	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);

	////
	int i = 0;
	char tmp[5];
	m_cbo_zyid.ResetContent();
	m_cbo_zybzid.ResetContent();
	m_cbo_gmid.ResetContent();
	for (i= 1; i <= 3 ; i++)
	{
		itoa(i , tmp , 10);
		m_cbo_zyid.AddString(tmp);
		m_cbo_zybzid.AddString(tmp);
		m_cbo_gmid.AddString(tmp);
	}
	m_cbo_zybzid.SetCurSel(0);
	m_cbo_zyid.SetCurSel(0);
	m_cbo_gmid.SetCurSel(0);

	for (i = 1; i <= 10; i++)
	{	
		itoa(i , tmp , 10);
		m_cbo_myid.AddString(tmp);
	}
	m_cbo_myid.SetCurSel(0);
	
	m_cbo_mzid.ResetContent();
	m_cbo_mzbzid.ResetContent();
	for (i= 1; i <= 5 ; i++)
	{
		itoa(i , tmp , 10);
		m_cbo_mzid.AddString(tmp);
		m_cbo_mzbzid.AddString(tmp);
	}
	m_cbo_mzbzid.SetCurSel(0);
	m_cbo_mzid.SetCurSel(0);
	
	m_PIN.Format("%s" ,"123456");
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInterfaceDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CInterfaceDemoDlg::OnPaint() 
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
HCURSOR CInterfaceDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CInterfaceDemoDlg::OnButtonFkRead() 
{
	
	
	char chsKLB[1+1] = {0};             //��������                                                                                        
	char chsGFBB[4+1] = {0};            //�淶�汾                                                                                          
	char chsFKJGMC[30+1] = {0};          //������������                                                                                      
	char chsFKJGDM[22+1] = {0};           //������������ 
	char chsFKJGZS[360+1] = {0}; 			//��������֤��
	char chsFKSJ[8+1] = {0};             //����ʱ�䣬YYYYMMDD��ʽ                                                                            
	char chsKYXQ[8+1] = {0};             //����Ч�ڣ�YYYYMMDD��ʽ
	char chsKH[18+1] = {0};               //���ţ���������֤�Ż���֤������һ��
	char chsAQM[3+1] = {0};              //��ȫ��                                                                                            
	char chsXPXLH[10+1] = {0};             //оƬ���к�
	char chsYYCSDM[6+1]	= {0};			//Ӧ�ó��д���
	
	int nRet = 0;

	nRet = iR_DDF1EF05Info((HANDLE)g_handle ,
		chsKLB,
		chsGFBB,
		chsFKJGMC,
		chsFKJGDM,
		chsFKJGZS,
		chsFKSJ,
		chsKH,
		chsAQM,
		chsXPXLH,
		chsYYCSDM);

	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(chsKLB);
		m_cListBox.AddString(chsGFBB);
		m_cListBox.AddString(chsFKJGMC);
		m_cListBox.AddString(chsFKJGDM);
		m_cListBox.AddString(chsFKJGZS);
		m_cListBox.AddString(chsFKSJ);

		m_cListBox.AddString(chsKH);
		m_cListBox.AddString(chsAQM);
		m_cListBox.AddString(chsXPXLH);
		m_cListBox.AddString(chsYYCSDM);
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;	
}

void CInterfaceDemoDlg::OnButtonCbRead2() 
{

	int nRet = 0;

	char chsXM[30+1] = {0};              //����
	char chsXB[2+1] = {0};               //�Ա����
	char chsMZ[2+1] = {0};               //�������
	char chsCSRQ[8+1] = {0};             //�������ڣ�YYYYMMDD��ʽ
	char chsSFZH[18+1] = {0};             //�������֤��
	char chsBRDH1[20+1] = {0};            //���˵绰1
	char chsBRDH2[20+1] = {0};            //���˵绰2
	char chsYLFYZFFS1[2+1 + 5] = {0}; 		  //ҽ�Ʒ���֧����ʽ1
	char chsYLFYZFFS2[2+1+ 5] = {0}; 		  //ҽ�Ʒ���֧����ʽ2
	char chsYLFYZFFS3[2+1+ 5] = {0}; 		  //ҽ�Ʒ���֧����ʽ3



	nRet = iR_DDF1EF06Info((HANDLE)g_handle,
			chsXM,              //����
			chsXB,              //�Ա����
			chsMZ,              //�������
			chsCSRQ,            //�������ڣ�YYYYMMDD��ʽ
			chsSFZH            //�������֤��

		);

	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(chsXM);
		m_cListBox.AddString(chsXB);
		m_cListBox.AddString(chsMZ);
		m_cListBox.AddString(chsCSRQ);
		m_cListBox.AddString(chsSFZH);
		m_cListBox.AddString(chsBRDH1);
		m_cListBox.AddString(chsBRDH2);
		m_cListBox.AddString(chsYLFYZFFS1);
		m_cListBox.AddString(chsYLFYZFFS2);
		m_cListBox.AddString(chsYLFYZFFS3);
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}

	return;
}


void CInterfaceDemoDlg::OnButtonResetpsam() 
{
//	MHC_CARDINTERFACE_API int __stdcall PowerOn(HANDLE hDev,int slot, char * ATR) ; //slot 1  User; slot 0x11 SAM1
	int nRet = 0;
	char ATR[60] = {0};
	int resLen;

	nRet = PowerOn((HANDLE)g_handle , SLOT_PSAM , ATR);
	if (nRet != 0)
	{
		MessageBox("PSAM���ϵ�ʧ��");
		return;
	}
/*	
	char info[300]={0};
	iChange_Pin(0,"1234","123456");
	iReader_SAM_Public(0,info);
	iReader_SAM_Terminal(0,info);
	iReader_SAM_PublicApp(0,info);
	iReader_SAM_OrgCertificate(0,info);
	iReader_SAM_Certificate(0,info);
*/
	m_cListBox.ResetContent();
	m_cListBox.AddString(ATR);

}


void CInterfaceDemoDlg::OnButtonReset3() 
{
//	 DWORD  i =  SendAPDU ((HANDLE)g_handle,SLOT_PSAM,cmd,ATR,&rlen);
	/*
	int nRet = 0;
	char ATR[60] = {0};
	char pin[10]={0} ;
	unsigned char cmd[20]={0};
	memcpy(cmd,"\x00\x20\x00\x00\x03",5);
	GetDlgItemText(IDC_EDITPIN,m_PIN);
	strcpy(pin , m_PIN);
	int len = strlen(pin);
	cmd[4]=len/2;
	int rlen =0;
	for(int i=0;i<(len/2);i++)
	{
		cmd[5+i]=(pin[2*i]-0x30)*0x10+(pin[2*i+1]-0x30);
	}
	nRet = SendAPDU ((HANDLE)g_handle,SLOT_PSAM,cmd,len/2+5,(unsigned char*)ATR,&rlen);
	if (nRet != 0 || (ATR[0] != 0x90 && ATR[1] != 0x00))
	{
	//	m_cListBox.AddString(ATR);
		MessageBox("PSAM����֤PINʧ��");
		return;
	}
	else
	{
		m_cListBox.AddString("PSAM����֤PIN�ɹ�");

	}*/

	int nRet = 0;
	char ATR[60] = {0};
	char pin[10]={0} ;
	unsigned char cmd[20]={0};
	GetDlgItemText(IDC_EDITPIN,m_PIN);
	strcpy(pin , m_PIN);
	nRet = iVerifyPIN(0,pin);
	if (nRet != 0 )
	{
	//	m_cListBox.AddString(ATR);
		MessageBox("PSAM����֤PINʧ��");
		return;
	}
	else
	{
		m_cListBox.AddString("PSAM����֤PIN�ɹ�");

	}

}


void CInterfaceDemoDlg::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	int nRet = 0;
	char ATR[60] = {0};
	
	nRet = iDOpenPort();
	if (nRet ==0 )
	{
		g_handle  = (HANDLE)nRet;
		m_cListBox.ResetContent();
		m_cListBox.AddString("���������ӳɹ�");
	}
	else
	{
		MessageBox("�򿪶�����ʧ��");
		return;
	}
	
	return;

	
}

void CInterfaceDemoDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	int nRet = 0;
	nRet = iDClosePort();
	CString s = "";
	s.Format("%02x", nRet);
	m_cListBox.ResetContent();
	m_cListBox.AddString(s);
}

void CInterfaceDemoDlg::OnButtonGmRead() 
{
	int nRet = 0;

	char chsGMWZ[20 + 1] = {0};
	char chsGMFY[100 + 1] = {0};
	
	int id = m_cbo_gmid.GetCurSel() + 1;

	nRet = iR_DF02EF07Info((HANDLE)g_handle , id, chsGMWZ, chsGMFY);	

	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(chsGMWZ);
		m_cListBox.AddString(chsGMFY);
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	return;
}

void CInterfaceDemoDlg::OnButtonMyRead() 
{
	int nRet = 0;
	
	char chsMYJZMC[20 + 1] = {0};
	char chsMYJZSJ[8 + 1] = {0};
	int id = m_cbo_myid.GetCurSel() + 1;

	nRet = iR_DF02EF08Info((HANDLE)g_handle ,id, chsMYJZMC, chsMYJZSJ);	
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(chsMYJZMC);
		m_cListBox.AddString(chsMYJZSJ);
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	return;
	
}

void CInterfaceDemoDlg::OnButtonZzjlbsRead() 
{
	// TODO: Add your control notification handler code here

	char chsZYJLBS1[2+1] = {0};
	char chsZYJLBS2[2+1] = {0};
	char chsZYJLBS3[2+1] = {0};

	int nRet = 0;
	
	
	nRet = iR_DF03EF05Info((HANDLE)g_handle , chsZYJLBS1, chsZYJLBS2, chsZYJLBS3);	
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(chsZYJLBS1);
		m_cListBox.AddString(chsZYJLBS2);
		m_cListBox.AddString(chsZYJLBS3);
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	return;
}

void CInterfaceDemoDlg::OnButtonMzjlbsRead() 
{
	char chsMZJLBS1[2+1] = {0};
	char chsMZJLBS2[2+1] = {0};
	char chsMZJLBS3[2+1] = {0};
	char chsMZJLBS4[2+1] = {0};
	char chsMZJLBS5[2+1] = {0};
	
	int nRet = 0;
	
	
	nRet = iR_DF03EF06Info( (HANDLE)g_handle ,chsMZJLBS1, chsMZJLBS2, chsMZJLBS3, chsMZJLBS4, chsMZJLBS5);	
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(chsMZJLBS1);
		m_cListBox.AddString(chsMZJLBS2);
		m_cListBox.AddString(chsMZJLBS3);
		m_cListBox.AddString(chsMZJLBS4);
		m_cListBox.AddString(chsMZJLBS5);
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	return;
	
}

void CInterfaceDemoDlg::OnButtonZyxx() 
{
	// TODO: Add your control notification handler code here

	char chsDATA[0x1000] = {0};	

	int nPos = 0;
	int nLen = 0;
	int style = 0;
	int nRet = 0;
	
	int id = m_cbo_zyid.GetCurSel() + 1;

	nRet = 	iR_DF03EEInfo((HANDLE)g_handle ,
							id,
							chsDATA,								  
							nPos,
							1639,
							AN_style
							);
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(chsDATA);
		m_out = chsDATA;
		UpdateData(FALSE);

	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	return;
}

void CInterfaceDemoDlg::OnButtonMzxxRead() 
{
	char chsDATA[0x1000] = {0};	

	int nPos = 0;
	int nLen = 0;
	int style = 0;
	int nRet = 0;

	int id = m_cbo_mzid.GetCurSel() + 1;

	
	nRet = 	iR_DF03EDInfo((HANDLE)g_handle ,
		id,
		chsDATA,
		nPos,
		3013,
		AN_style
		);
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(chsDATA);
		m_out = chsDATA;
		UpdateData(FALSE);
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	return;
}

void CInterfaceDemoDlg::OnButtonDizhiRead() 
{
	int nRet = 0;

	char chsDZLB1[2+1] = {0};				//��ַ���1
	char chsDZ1[100+1] = {0}; 				//��ַ1
	char chsDZLB2[2+1] = {0};               //��ַ���1
	char chsDZ2[100+1] = {0}; 				//��ַ1


	nRet = 	iR_DF01EF05Info((HANDLE)g_handle ,
							chsDZLB1,
							chsDZ1,
							chsDZLB2,
							chsDZ2
							);
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(chsDZLB1);
		m_cListBox.AddString(chsDZ1);
		m_cListBox.AddString(chsDZLB2);
		m_cListBox.AddString(chsDZ2);
		
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	return;
	
}

void CInterfaceDemoDlg::OnButtonLxrRead() 
{

	int nRet = 0;
		
	
	char LXRXM1[30+1] = {0};			
	char LXRGX1[2+1] = {0}; 			
	char LXRDH1[20+1] = {0};  
	char LXRXM2[30+1] = {0};			
	char LXRGX2[2+1] = {0}; 			
	char LXRDH2[20+1] = {0};    
	char LXRXM3[30+1] = {0};			
	char LXRGX3[2+1] = {0}; 			
	char LXRDH3[20+1] = {0};    	
	
	
	nRet = 	iR_DF01EF06Info((HANDLE)g_handle ,
							LXRXM1,
							LXRGX1,
							LXRDH1,
							LXRXM2,
							LXRGX2,
							LXRDH2,
							LXRXM3,
							LXRGX3,
							LXRDH3
							);
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(LXRXM1);
		m_cListBox.AddString(LXRGX1);
		m_cListBox.AddString(LXRDH1);
		m_cListBox.AddString(LXRXM2);
		m_cListBox.AddString(LXRGX2);
		m_cListBox.AddString(LXRDH2);
		m_cListBox.AddString(LXRXM3);
		m_cListBox.AddString(LXRGX3);
		m_cListBox.AddString(LXRDH3);

		
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	return;
}

void CInterfaceDemoDlg::OnButtonZyhyRead() 
{

	int nRet = 0;
	
	
	char WHCD[2+1] = {0};	//�Ļ��̶ȴ���		
	char HYZK[2+1] = {0}; 	//����״������		
	char ZY[3+1] = {0};    //ְҵ����
	
	
	
	nRet = 	iR_DF01EF07Info((HANDLE)g_handle ,
		WHCD,
		HYZK,
		ZY
		);
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(WHCD);
		m_cListBox.AddString(HYZK);
		m_cListBox.AddString(ZY);
		
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	return;
	
}

void CInterfaceDemoDlg::OnButtonZjjlxxRead() 
{

	char chsZJLB[2+1] = {0};            //֤�������룬�������֤�ź�֤��������һ�����
	char chsZJHM[18+1] = {0};            //֤������
	char chsJKDAH[17+1] = {0};           //����������
	char chsXNHZH[18+1] = {0};           //��ũ��֤��


	int nRet = 0;
	
	
	nRet = 	iR_DF01EF08Info((HANDLE)g_handle ,
		chsZJLB,
		chsZJHM,
		chsJKDAH,
		chsXNHZH
		);
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(chsZJLB);
		m_cListBox.AddString(chsZJHM);
		m_cListBox.AddString(chsJKDAH);
		m_cListBox.AddString(chsXNHZH);
		
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	return;
	
}

void CInterfaceDemoDlg::OnButtonLcjbsjRead() 
{

	char chsABOXX[2+1] = {0};           //ABOѪ�ʹ���
	char chsRHXX[2+1] = {0};            //RHѪ�ʹ���
	char chsXCBZ[2+1] = {0};            //������־
	char chsXZBBZ[2+1] = {0};           //���ಡ��־
	char chsXNXGBBZ[2+1] = {0};         //����Ѫ�ܲ���־
	char chsDXBBZ[2+1] = {0};           //��ﲡ��־
	char chsNXWLBZ[2+1] = {0};          //��Ѫ���ұ�־
	char chsTNBBZ[2+1] = {0};           //���򲡱�־
	char chsQGYBZ[2+1] = {0};           //����۱�־
	char chsTXBZ[2+1] = {0};            //͸����־
	char chsQGYZBZ[2+1] = {0};          //������ֲ��־
	char chsQGQSBZ[2+1] = {0};          //����ȱʧ��־
	char chsKZXYZBZ[2+1] = {0};         //��װж��֫��־
	char chsXZQBQBZ[2+1] = {0};        //����������־
	char chsQTYXJSMC[40+1] = {0};        //����ҽѧ��ʾ����

	
	
	int nRet = 0;
	
	
	nRet = 	iR_DF02EF05Info((HANDLE)g_handle ,
							chsABOXX,   
							chsRHXX,    
							chsXCBZ,    
							chsXZBBZ,   
							chsXNXGBBZ, 
							chsDXBBZ,   
							chsNXWLBZ,  
							chsTNBBZ,   
							chsQGYBZ,   
							chsTXBZ,    
							chsQGYZBZ,  
							chsQGQSBZ,  
							chsKZXYZBZ, 
							chsXZQBQBZ, 
							chsQTYXJSMC

		);
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();

		m_cListBox.AddString(chsABOXX);   
		m_cListBox.AddString(chsRHXX);    
		m_cListBox.AddString(chsXCBZ);    
		m_cListBox.AddString(chsXZBBZ);   
		m_cListBox.AddString(chsXNXGBBZ); 
		m_cListBox.AddString(chsDXBBZ);   
		m_cListBox.AddString(chsNXWLBZ);  
		m_cListBox.AddString(chsTNBBZ);   
		m_cListBox.AddString(chsQGYBZ);   
		m_cListBox.AddString(chsTXBZ);    
		m_cListBox.AddString(chsQGYZBZ);  
		m_cListBox.AddString(chsQGQSBZ);  
		m_cListBox.AddString(chsKZXYZBZ); 
		m_cListBox.AddString(chsXZQBQBZ); 
		m_cListBox.AddString(chsQTYXJSMC);

		
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	return;
	
}

void CInterfaceDemoDlg::OnButtonTsxxRead() 
{

	char chsJSBBZ[2+1] = {0};           //���񲡱�־
	
	int nRet = 0;
	
	
	nRet = 	iR_DF02EF06Info((HANDLE)g_handle ,
		chsJSBBZ
		);
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(chsJSBBZ);   
	
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	return;	
}


void CInterfaceDemoDlg::OnButtonCkrjbxxWrite() 
{

	int nRet = 0;

	CWnd *pWnd = GetTopWindow(); 

	InputDialog dlg = new InputDialog(pWnd );
	
	dlg.Setview(FILE_DDF1EF06);
	dlg.DoModal();
	
	if (dlg._CancelPressed)
		return;

	char XM[30+6]={"��������"};              //����
	char XB[1+6]={"1"};              //�Ա����
	char MZ[1+6]={"01"};              //�������
	char CSRQ[4+6]={"20120101"};            //�������ڣ�YYYYMMDD��ʽ
	char SFZH[18+6]={"123456789123456789"};            //�������֤��

	
	
	strcpy(XM  , dlg.m_edit1);
	strcpy(XB  , dlg.m_edit2);
	strcpy(MZ  , dlg.m_edit3);
	strcpy(CSRQ  , dlg.m_edit4);
	strcpy(SFZH  , dlg.m_edit5);

	
	nRet =  iW_DDF1EF06Info((HANDLE)g_handle ,
							  XM,              //����
							  XB,              //�Ա����
							  MZ,              //�������
							  CSRQ,            //�������ڣ�YYYYMMDD��ʽ
							  SFZH            //�������֤��
							  );
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
}

void CInterfaceDemoDlg::OnButtonFkWrite() 
{
		int nRet = 0;
	CWnd *pWnd = GetTopWindow(); 

	InputDialog dlg = new InputDialog(pWnd );
	
	dlg.Setview(FILE_DDF1EF05);
	dlg.DoModal();
	
	if (dlg._CancelPressed)
		return;

	char KLB[1+6]={"1"};             //��������                                                                                        
	char GFBB[4+6]={"1.00"};            //�淶�汾                                                                                          
	char FKJGMC[30+6] = {"���Ի�������"};          //������������                                                                                      
	char FKJGDM[22+6]={"1234567890112345678901"};          //������������ 
	char FKJGZS[500]={0};			//��������֤��
	char FKSJ[4+6]={"20120801"};            //����ʱ�䣬YYYYMMDD��ʽ                                                                            
	char KH[18+6]={"123456789123456789"};              //���ţ���������֤�Ż���֤������һ��
	char AQM[3+6]={"123"};             //��ȫ��                                                                                            
	char XPXLH[10+6]={"1234567890"};           //оƬ���к�
	char YYCSDM[3+6]={"123123"};				//Ӧ�ó��д���

	
	
	strcpy(KLB  , dlg.m_edit1);
	strcpy(GFBB  , dlg.m_edit2);
	strcpy(FKJGMC  , dlg.m_edit3);
	strcpy(FKJGDM  , dlg.m_edit4);
	strcpy(FKJGZS  , dlg.m_edit5);
	strcpy(FKSJ  , dlg.m_edit6);
	strcpy(KH  , dlg.m_edit7);
	strcpy(AQM  , dlg.m_edit8);
	strcpy(XPXLH  , dlg.m_edit9);
	strcpy(YYCSDM  , dlg.m_edit10);
	
	nRet =  iW_DDF1EF05Info(
							  (HANDLE)g_handle,
							   KLB,             //��������                                                                                        
							   GFBB,            //�淶�汾                                                                                          
							   FKJGMC,          //������������                                                                                      
							   FKJGDM,          //������������ 
							   FKJGZS,			//��������֤��
							   FKSJ,            //����ʱ�䣬YYYYMMDD��ʽ                                                                            
							   KH,              //���ţ���������֤�Ż���֤������һ��
							   AQM,             //��ȫ��                                                                                            
							   XPXLH,           //оƬ���к�
							   YYCSDM				//Ӧ�ó��д���
							  );
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;

}

void CInterfaceDemoDlg::OnButtonGmWrite() 
{
	CWnd *pWnd = GetTopWindow(); 

	InputDialog dlg = new InputDialog(pWnd );
	
	dlg.Setview(FILE_DF02EF07);
	dlg.DoModal();	
	if (dlg._CancelPressed)
		return;
	int nRet = 0;	

	char chsGMWZMC[20]= {"�������ʲ���1"};        //������������
	char chsGMFY[100] = {"������Ӧ����1"};			//������Ӧ

	strcpy(chsGMWZMC , dlg.m_edit1);
	strcpy(chsGMFY , dlg.m_edit2);
	
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	//ѭ����¼			
	nRet = iW_DF02EF07Info((HANDLE)g_handle ,
							chsGMWZMC, 
							chsGMFY		
							);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
	
}

void CInterfaceDemoDlg::OnButtonMyjbsjWrite() 
{

	CWnd *pWnd = GetTopWindow(); 

	InputDialog dlg = new InputDialog(pWnd );
	
	dlg.Setview(FILE_DF02EF08);
	dlg.DoModal();	
	if (dlg._CancelPressed)
		return;
	int nRet = 0;
	
	char chsMYJZMC[20+1] = {"���߲���1"}; //���߽������� 
	char chsMYJZSJ[8+1] = {"20120216"};   //���߽���ʱ��

	strcpy(chsMYJZMC , dlg.m_edit1);
	strcpy(chsMYJZSJ , dlg.m_edit2);
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	//ѭ����¼			
	nRet = iW_DF02EF08Info((HANDLE)g_handle ,
							chsMYJZMC, 
							chsMYJZSJ		
							);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
	
}

void CInterfaceDemoDlg::OnButtonZyjlWrite() 
{
	int nRet = 0;
	if (MessageBox("��ȷ��Ҫִ��д�������","������ʾ", MB_OKCANCEL) == IDCANCEL)
	{
	  return;
	}

	int id = m_cbo_zybzid.GetCurSel() + 1;
			
	nRet = iW_DF03EF05Info((HANDLE)g_handle ,
								id	
								);
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
	
}

void CInterfaceDemoDlg::OnButtonZzjlyxErase() 
{
	// TODO: Add your control notification handler code here

	if (MessageBox("��ȷ��Ҫִ�в���������","������ʾ", MB_OKCANCEL) == IDCANCEL)
	{
	  return;
	}
	
	int id = m_cbo_zybzid.GetCurSel() + 1;
	
	int nRet = 0;

	nRet =  iErase_DF03EF05Info((HANDLE)g_handle ,
	  id	
	  );
	if (nRet == 0)
	{
	  m_cListBox.ResetContent();
	  m_cListBox.AddString("д��ɹ�");
	  MessageBox("д��ɹ�");
	}
	else
	{
	  CString s = "";
	  s.Format("ErrorCode: %d", nRet);
	  m_cListBox.ResetContent();
	  m_cListBox.AddString(s);
	}
								  
	return;
}

void CInterfaceDemoDlg::OnButtonMzjlbsWrite() 
{
	if (MessageBox("��ȷ��Ҫִ��д�������","������ʾ", MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}
	
	int nRet = 0;
	int id = m_cbo_mzbzid.GetCurSel() + 1;
		
	nRet =  iW_DF03EF06Info((HANDLE)g_handle ,
								id	
								);
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
	
}

void CInterfaceDemoDlg::OnButtonMzjlbsErase() 
{
	if (MessageBox("��ȷ��Ҫִ�в���������","������ʾ", MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}
	
	int nRet = 0;
	
	int id = m_cbo_mzbzid.GetCurSel() + 1;

	nRet =  iErase_DF03EF06Info((HANDLE)g_handle ,
		id	
		);
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
	
}

void CInterfaceDemoDlg::OnButtonZyxxWrite() 
{

	if (MessageBox("��ȷ��Ҫִ��д�������","������ʾ", MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}
	
	int nRet = 0;
	
	int nPos = 0;
	int nLen = 0;
	int style = 0;

	char chsData[MAX_BIN_SIZE] = {0};
	int id = m_cbo_zyid.GetCurSel() + 1;

	(CEdit*)GetDlgItemText(IDC_EDIT_ZY_WDATA, chsData, sizeof(chsData));
	int len = strlen(chsData);
	nRet = iW_DF03EEInfo((HANDLE)g_handle ,
								id,
								chsData,
								nPos,
								1639,
								AN_style
								);
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
}

void CInterfaceDemoDlg::OnButtonMzxxWrite() 
{
									  
	
	if (MessageBox("��ȷ��Ҫִ��д�������","������ʾ", MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}
	
	int nRet = 0;

	int nPos = 0;
	int nLen = 0;
	int style = 0;
	
	char chsData[MAX_BIN_SIZE] = {0};
	int id = m_cbo_mzid.GetCurSel() + 1;
	
	(CEdit*)GetDlgItemText(IDC_EDIT_MZ_WDATA, chsData, sizeof(chsData));
	int len = strlen(chsData);
	nRet = iW_DF03EDInfo((HANDLE)g_handle ,
		id,
		chsData,
		nPos,
		3013,
		AN_style
		);
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;	
}

void CInterfaceDemoDlg::OnButtonDzxxWrite() 
{

	CWnd *pWnd = GetTopWindow(); 

	InputDialog dlg = new InputDialog(pWnd );
	
	dlg.Setview(FILE_DF01EF05);
	dlg.DoModal();
	if (dlg._CancelPressed)
		return;
	int nRet = 0;
	
	char chsDZLB1[2+1+ 5] = {"01"};									//��ַ���1
	char chsDZ1[100+1] = {"�������������Ļ���·211��"}; 				//��ַ1
	char chsDZLB2[2+1+ 5] = {"02"};									//��ַ���1
	char chsDZ2[100+1] = {"���������йش嶦��B1"}; 				//��ַ1
	
	strcpy(chsDZLB1 , dlg.m_edit1);
	strcpy(chsDZ1 , dlg.m_edit2);
	strcpy(chsDZLB2 , dlg.m_edit3);
	strcpy(chsDZ2 , dlg.m_edit4);
	
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	nRet = iW_DF01EF05Info((HANDLE)g_handle ,
		chsDZLB1,         
		chsDZ1,            
		chsDZLB2,        
		chsDZ2
		);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
	
}

void CInterfaceDemoDlg::OnButtonLxrxxWrite() 
{

	CWnd *pWnd = GetTopWindow(); 

	InputDialog dlg = new InputDialog(pWnd );
	
	dlg.Setview(FILE_DF01EF06);
	dlg.DoModal();
	if (dlg._CancelPressed)
		return;
	int nRet = 0;
/*
//��ϵ������1                                                                                       
//��ϵ�˹�ϵ����1                                                                                   
//��ϵ�˵绰1                                                                                       
//��ϵ������2                                                                                       
//��ϵ�˹�ϵ����2                                                                                   
//��ϵ�˵绰2                                                                                       
//��ϵ������3                                                                                       
//��ϵ�˹�ϵ����3                                                                                   
//��ϵ�˵绰3
*/	
	char LXRXM1[30+1] = {"�Ŵ���"};			
	char LXRGX1[2+1+ 5] = {"01"}; 			
	char LXRDH1[20+1] = {"086-021-1111"};  
	char LXRXM2[30+1] = {"��С��"};			
	char LXRGX2[2+1+ 5] = {"02"}; 			
	char LXRDH2[20+1] = {"11111111111"};    
	char LXRXM3[30+1] = {"����"};			
	char LXRGX3[2+1+ 5] = {"03"}; 			
	char LXRDH3[20+1] = {"222222"};    	
	
	strcpy(LXRXM1 , dlg.m_edit1);
	strcpy(LXRGX1 , dlg.m_edit2);
	strcpy(LXRDH1 , dlg.m_edit3);
	strcpy(LXRXM2 , dlg.m_edit4);
	strcpy(LXRGX2 , dlg.m_edit5);
	strcpy(LXRDH2 , dlg.m_edit6);
	strcpy(LXRXM3 , dlg.m_edit7);
	strcpy(LXRGX3 , dlg.m_edit8);
	strcpy(LXRDH3 , dlg.m_edit9);

	SetCursor(LoadCursor(NULL, IDC_WAIT));
	nRet = 	iW_DF01EF06Info((HANDLE)g_handle ,
							LXRXM1,
							LXRGX1,
							LXRDH1,
							LXRXM2,
							LXRGX2,
							LXRDH2,
							LXRXM3,
							LXRGX3,
							LXRDH3
							);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
	
}

void CInterfaceDemoDlg::OnButton1ZyhyxxWrite() 
{
	CWnd *pWnd = GetTopWindow(); 

	InputDialog dlg = new InputDialog(pWnd );
	
	dlg.Setview(FILE_DF01EF07);
	dlg.DoModal();
	if (dlg._CancelPressed)
		return;
	
	int nRet = 0;
	char WHCD[2+1+ 5] = {"02"};	//�Ļ��̶ȴ���		
	char HYZK[2+1+ 5] = {"01"}; 	//����״������		
	char ZY[3+1+ 5] = {"001"};    //ְҵ����	
	
	strcpy( WHCD , dlg.m_edit1);
	strcpy( HYZK , dlg.m_edit2);
	strcpy( ZY , dlg.m_edit3);
	SetCursor(LoadCursor(NULL, IDC_WAIT));

	nRet = 	iW_DF01EF07Info((HANDLE)g_handle ,
		WHCD,
		HYZK,
		ZY
		);

	SetCursor(LoadCursor(NULL, IDC_ARROW));
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
	
}

void CInterfaceDemoDlg::OnButtonZjjlxxWrite() 
{
	CWnd *pWnd = GetTopWindow(); 

	InputDialog dlg = new InputDialog(pWnd );
	
	dlg.Setview(FILE_DF01EF08);
	dlg.DoModal();	
	if (dlg._CancelPressed)
		return;
	int nRet = 0;

	char chsZJLB[2+1+ 5] = {"01"};            //֤�������룬�������֤�ź�֤��������һ�����
	char chsZJHM[18+1] = {"111203198802012215"};            //֤������
	char chsJKDAH[17+1] = {"11120319880201221"};           //����������
	char chsXNHZH[18+1] = {"111203198802012215"};           //��ũ��֤��
	
	strcpy(chsZJLB , dlg.m_edit1);
	strcpy(chsZJHM , dlg.m_edit2);
	strcpy(chsJKDAH , dlg.m_edit3);
	strcpy(chsXNHZH , dlg.m_edit4);
	
	SetCursor(LoadCursor(NULL, IDC_WAIT));

	nRet = 	iW_DF01EF08Info((HANDLE)g_handle ,
		chsZJLB,
		chsZJHM,
		chsJKDAH,
		chsXNHZH
		);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
	
}

void CInterfaceDemoDlg::OnButtonLcjbsjWrite() 
{
	CWnd *pWnd = GetTopWindow(); 

	

	dialogInput2 dlg = new dialogInput2(pWnd );
	
	dlg.DoModal();	
	if (dlg._CancelPressed)
		return;
	int nRet = 0;
	
	char chsABOXX[2+1+ 5] = {"01"};           //ABOѪ�ʹ���
	char chsRHXX[2+1+ 5] = {"02"};            //RHѪ�ʹ���
	char chsXCBZ[2+1+ 5] = {"03"};            //������־
	char chsXZBBZ[2+1+ 5] = {"04"};           //���ಡ��־
	char chsXNXGBBZ[2+1+ 5] = {"05"};         //����Ѫ�ܲ���־

	char chsDXBBZ[2+1+ 5] = {"06"};           //��ﲡ��־
	char chsNXWLBZ[2+1+ 5] = {"07"};          //��Ѫ���ұ�־
	char chsTNBBZ[2+1+ 5] = {"08"};           //���򲡱�־
	char chsQGYBZ[2+1+ 5] = {"09"};           //����۱�־
	char chsTXBZ[2+1+ 5] = {"10"};            //͸����־

	char chsQGYZBZ[2+1+ 5] = {"11"};          //������ֲ��־
	char chsQGQSBZ[2+1+ 5] = {"12"};          //����ȱʧ��־
	char chsKZXYZBZ[2+1+ 5] = {"13"};         //��װж��֫��־
	char chsXZQBQBZ[2+1+ 5] = {"14"};        //����������־
	char chsQTYXJSMC[40+1] = {"����ҽѧ��ʾ���Ʋ���"};        //����ҽѧ��ʾ����
	
	strcpy(chsABOXX , dlg.m_edit1 );
	strcpy(chsRHXX , dlg.m_edit2 );
	strcpy(chsXCBZ , dlg.m_edit3 );
	strcpy(chsXZBBZ , dlg.m_edit4 );
	strcpy(chsXNXGBBZ , dlg.m_edit5 );

	strcpy(chsDXBBZ , dlg.m_edit6 );
	strcpy(chsNXWLBZ , dlg.m_edit7 );
	strcpy(chsTNBBZ , dlg.m_edit8 );
	strcpy(chsQGYBZ , dlg.m_edit9 );
	strcpy(chsTXBZ , dlg.m_edit10 );
	
	strcpy(chsQGYZBZ , dlg.m_edit11 );
	strcpy(chsQGQSBZ , dlg.m_edit12 );
	strcpy(chsKZXYZBZ , dlg.m_edit13 );
	strcpy(chsXZQBQBZ , dlg.m_edit14 );
	strcpy(chsQTYXJSMC , dlg.m_edit15 );
	
	
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	nRet = 	iW_DF02EF05Info((HANDLE)g_handle ,
							chsABOXX,   
							chsRHXX,    
							chsXCBZ,    
							chsXZBBZ,   
							chsXNXGBBZ, 
							chsDXBBZ,   
							chsNXWLBZ,  
							chsTNBBZ,   
							chsQGYBZ,   
							chsTXBZ,    
							chsQGYZBZ,  
							chsQGQSBZ,  
							chsKZXYZBZ, 
							chsXZQBQBZ, 
							chsQTYXJSMC
		);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
	
}

void CInterfaceDemoDlg::OnButtonTsxxsjWrite() 
{
	CWnd *pWnd = GetTopWindow(); 

	InputDialog dlg = new InputDialog(pWnd );
	
	dlg.Setview(FILE_DF02EF06);
	dlg.DoModal();	
	if (dlg._CancelPressed)
		return;
	int nRet = 0;
	
	char chsJSBBZ[2+1+ 5] = {"02"};           //���񲡱�־
	
	strcpy(chsJSBBZ , dlg.m_edit1);

nRet = 	iW_DF02EF06Info((HANDLE)g_handle ,
							chsJSBBZ
							);
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
	
}

void CInterfaceDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
//	GdiplusShutdown(m_pGdiToken);
}

void CInterfaceDemoDlg::OnButtonZpRead() 
{
	int nRet = 0;
	
	int nDataLen = 0;
	
	BYTE bysZHAOPIAN[3072] = {0};

// 	WORD wMilliseconds = 0;
// 	WORD wMilliseconds1 = 0;
// 	WORD wMilliseconds2 = 0;
// 	LPSYSTEMTIME lpSystemTime = new SYSTEMTIME;
// 	GetSystemTime(lpSystemTime);
// 	wMilliseconds = lpSystemTime->wSecond *1000 + lpSystemTime->wMilliseconds;

	nRet = iR_DDF1EF07Info((HANDLE)g_handle ,
							bysZHAOPIAN        //��Ƭ												  												  
							);
	
	
// 	GetSystemTime(lpSystemTime);
// 	wMilliseconds1 = lpSystemTime->wSecond *1000 + lpSystemTime->wMilliseconds;
// 	wMilliseconds2 = wMilliseconds1 - wMilliseconds;
// 	delete lpSystemTime;
	if (nRet == 0)
	{

		m_cListBox.ResetContent();
		m_cListBox.AddString("����Ƭ�ɹ�");

		//��ȡ��Ƭ����
		nDataLen = bysZHAOPIAN[0] * 0x100 + bysZHAOPIAN[1];

		DisPlayJPG(nDataLen, &bysZHAOPIAN[2]);
		SavePic(nDataLen, &bysZHAOPIAN[2]);

	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
}

int CInterfaceDemoDlg::DisPlayJPG(int nDataLen, byte * pbysZHAOPIAN)
{
	int nRet = 0;

	try
	{
/*
		CDC* pDC =GetDC();
		
		Graphics graphics( pDC->m_hDC);

		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nDataLen);
		LPVOID pvData = NULL;
		pvData = GlobalLock(hGlobal);
		memcpy(pvData, &pbysZHAOPIAN[0], nDataLen);
		
		GlobalUnlock(hGlobal);
		
		IStream *pStream = NULL;
		HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pStream);
		

		Image image(pStream, FALSE);
		
		graphics.DrawImage(&image, 719,30, image.GetWidth(), image.GetHeight());

		GlobalFree(hGlobal);*/
	}
	catch(...)
	{
		//
	}
	return nRet;
}

int CInterfaceDemoDlg::SavePic(int nDataLen, byte * pbysZHAOPIAN)
{
	int nRet = 0;
	int i = 0;
	try
	{
		ofstream outfile("card_pic.jpg", ios::binary);
		if (!outfile)
		{
			m_cListBox.AddString("����outfile����ʧ��");
			nRet = 1;
			throw nRet;
		}
		
		for(i = 0; i < nDataLen; i++)
		{
			outfile.write((char*)&pbysZHAOPIAN[i], sizeof(pbysZHAOPIAN[i]));
		}
		outfile.close();
		m_cListBox.AddString("card_pic.jpgͼƬ�����ڵ�ǰ·����");
	}
	catch(...)
	{
		//
	}
	return nRet;

	//��ʾ//Image image(L"card_pic.jpg", FALSE);
	//...

}

void CInterfaceDemoDlg::OnButtonWsbRead() 
{
/*	int nRet = 0;

	DWORD error[10] = {0};

	//DDF1EF05
	TCHAR szCard[2+1];
	TCHAR szVersion[8+1];
	TCHAR szIssuer[30+1];
	TCHAR szIssuercode[22+1];
	TCHAR szCert[360+1];
	TCHAR szIssuertime[8+1];
	TCHAR szValidTime[8+1];
	TCHAR szCardNo[18+1];
	TCHAR szSecCode[3+1];
	TCHAR szChipNum[10+1];
	TCHAR szYYCSDM[6+1];
	//DDF1EF06
	TCHAR szName[30+1];
	TCHAR szSex[2+1];
	//DF01EF06
	TCHAR szLXRXM1[30+1];
	//DF03 EF05
	//סԺ��¼��Ч��ʶ
	TCHAR szZYJLYXBS1[2+1];
	TCHAR szZYJLYXBS2[2+1];
	//�����¼
	TCHAR szMZJLYXBS1[2+1];
	//����
	TCHAR szGM[120+1];

	//סԺ��������
	TCHAR szZYJGMC[70+1];
	//סԺ��������
	TCHAR szZYJGMD[10+1];

	//�����������
	TCHAR szJZJGMC[70+1];
	//�����������
	TCHAR szJZJGMD[10+1];


	ITEMSELECT itemSelRead[] = 
	{	
		{1, szCard, 1 },
		{2,  szVersion, 4 },
		{3,  szIssuer, 30 },
		{4,  szIssuercode, 11 },
		{5,  szCert, 180 },
		{6,  szIssuertime, 4 },
		{7,  szValidTime, 4 },
		{8,  szCardNo, 18 },
		{9,  szSecCode, 3 },
		{10, szChipNum, 10 },
		{57,  szYYCSDM, 3 },
		{11,  szName, 30 },
		{12,  szSex, 1 },
		{25,  szLXRXM1, 30 }


	};

	int nCount = 14;

	nRet = UH_Reader_CardItem((int)g_handle , UHSLOT_PSAM1,itemSelRead, nCount);

	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		for(int i = 0; i < nCount; i++)
		{
			m_cListBox.AddString((LPCTSTR)itemSelRead[i].pValue);
		}
		//��ʾ����
		m_cListBox.AddString(&szGM[0]);
		m_cListBox.AddString(&szGM[20]);
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}*/
}

void CInterfaceDemoDlg::OnButtonWsbWrite() 
{
	int nRet = 0;
	
	DWORD error[10] = {0};
	
	//DDF1EF05
	/*
	TCHAR szCard[2+1];
	TCHAR szVersion[8+1];
	TCHAR szIssuer[30+1];
	TCHAR szIssuercode[22+1];
	TCHAR szCert[360+1];
	TCHAR szIssuertime[8+1];
	TCHAR szValidTime[8+1];
	TCHAR szCardNo[18+1];
	TCHAR szSecCode[3+1];
	TCHAR szChipNum[10+1];
	TCHAR szYYCSDM[6+1];
	*/
	//DDF1EF06
	TCHAR szName[30+1] = {"��������д"};
	TCHAR szSex[2+1] = {"02"};

	//DF01EF06
	TCHAR szLXRXM1[30+1] = {"��ϵ����������д1"};

	//DF03 EF05
	//סԺ��¼��Ч��ʶ
	TCHAR szZYJLYXBS1[2+1] = {"ff"};
	TCHAR szZYJLYXBS2[2+1] = {"00"};

	//��������
	TCHAR szGMWZ[20+1] = {"�������ʵ���1"};
	//������Ӧ
	TCHAR szGMFY[100+1] = {"������Ӧ����1"};

    TCHAR szGM[120+1];
	memcpy(&szGM[0], szGMWZ, 20);
	memcpy(&szGM[20], szGMFY, 100);

	//����
	TCHAR szMYMC[20+1] = {"�������Ƶ���1"};
	TCHAR szMYSJ[8+1] = {"20120219"};
	TCHAR szMY[28+1];
	memcpy(&szMY[0], szMYMC, 20);
	memcpy(&szMY[20], szMYSJ, 8);

	//סԺ��������
	TCHAR szZYJGMC[70+1] = {"סԺ��������1"};
	//סԺ��������
	TCHAR szZYJGMD[10+1] = {"100860219"};

	//����������
	TCHAR szJKDAH[17+1] = {"12345678901234567"};
	
	//�����¼
	TCHAR szMZJLYXBS1[2+1]  = {"00"};;		
	//�����������
	TCHAR szJZJGMC[70+1] = {"�����������1"};
	//�����������
	TCHAR szJZJGMD[10+1] ={"1000000"};
/*	*/

	
    memcpy(&szGM[0], &szGMWZ[0], 20);
	memcpy(&szGM[20], &szGMFY[0], 100);
	
	ITEMSELECT itemSelRead[] = 
	{

		{25,  szLXRXM1, 30 },	

		{39,  szJKDAH, 17 }	,
		

		
	};
/*	
	int nCount = 2;
	
	nRet = UH_Writer_CardItem((int)g_handle , UHSLOT_PSAM1,itemSelRead, nCount);
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}	*/
}

void CInterfaceDemoDlg::OnButtonZpWrite() 
{
	BYTE bysZHAOPIAN[3072] = {0};
	int nRet = 0;
	CString szGetName = "";
	nRet = GetZhaoPianPath(szGetName);	

	CFile cfile;
	int nDataLen;

	if (cfile.Open(szGetName, CFile::modeRead))
	{  
		int size = cfile.GetLength();
		nDataLen = size;
	}  
	cfile.Close();
//	int nDataLen = GetFileLength(); //2918
	
	try{
		//bysZHAOPIAN[0] = 0x0A;
		//bysZHAOPIAN[1] = 0x56;
		bysZHAOPIAN[0] = nDataLen/0x100;
		bysZHAOPIAN[1] = nDataLen%0x100;
		ifstream infile(szGetName, ios::binary);
		for(int i = 2; i < nDataLen + 2; i++)
		{
			infile.read ((char*)&bysZHAOPIAN[i], sizeof(bysZHAOPIAN[i]));
		}
		infile.close();
	}
	catch (...) {
	}
	
	nRet = iW_DDF1EF07Info((HANDLE)g_handle ,
							bysZHAOPIAN        //��Ƭ												  												  
							);

	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
}

int CInterfaceDemoDlg::GetZhaoPianPath(CString &strPicPath)
{

	int nRet = 1;

	char cCurrentpath[MAX_PATH]= {""}; 
	CFileDialog *lpszOpenFile;
	
	try
	{

		GetCurrentDirectory(MAX_PATH/2, cCurrentpath);

		lpszOpenFile = new CFileDialog(
			TRUE,
			"",
			"",
			OFN_FILEMUSTEXIST |OFN_HIDEREADONLY ,
			"�ļ�����(*.jpg)|*.jpg||");
		
		
		lpszOpenFile->m_ofn.lpstrInitialDir = cCurrentpath;
		
		//
		if(lpszOpenFile->DoModal() == IDOK)
		{
			
			//�õ����ļ���·��
			strPicPath = lpszOpenFile->GetPathName();
			nRet = 0;
		}
		
		//
		delete lpszOpenFile;
		lpszOpenFile = NULL;
		SetCurrentDirectory(cCurrentpath);
	}
	catch(...)
	{
		if (nRet == 0)
		{
			nRet = 2;
		}
	}

	return nRet;
	
}


void CInterfaceDemoDlg::OnButtonWsbOpen() 
{
//	g_handle = wsc_OpenDevice();
//
//	if (g_handle == NULL)
//	{
//		m_cListBox.ResetContent();
//		m_cListBox.AddString("���豸ʧ��");
//	}
//	else
//	{
//		m_cListBox.ResetContent();
//		m_cListBox.AddString("���豸�ɹ�");
//	}
	
}

void CInterfaceDemoDlg::OnButtonWsbClose() 
{
	// TODO: Add your control notification handler code here
//	DWORD dwRet = wsc_CloseDevice(g_handle);
//
//	CString s = "";
////	s.Format("%d", dwRet);
//	m_cListBox.ResetContent();
// 	m_cListBox.AddString(s);

}

void CInterfaceDemoDlg::OnButtonDizhiRead2() 
{
	int nRet = 0;
		
	
	char KYXQ[8+1] = {0};			
	char GRDH1[20+1] = {0}; 			
	char GRDH2[20+1] = {0};  
	char ZHFS1[2+1] = {0};			
	char ZHFS2[2+1] = {0}; 			
	char ZHFS3[20+1] = {0};    
		
	nRet = 	iR_DDF1EF08Info((HANDLE)g_handle ,
							KYXQ,
							GRDH1,
							GRDH2,
							ZHFS1,
							ZHFS2,
							ZHFS3
							);
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(KYXQ);
		m_cListBox.AddString(GRDH1);
		m_cListBox.AddString(GRDH2);
		m_cListBox.AddString(ZHFS1);
		m_cListBox.AddString(ZHFS2);
		m_cListBox.AddString(ZHFS3);
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	return;
}

void CInterfaceDemoDlg::OnButtonDzxxWrite2() 
{
	CWnd *pWnd = GetTopWindow(); 

	InputDialog dlg = new InputDialog(pWnd );
	
	dlg.Setview(FILE_DDF1EF08);
	dlg.DoModal();
	
	if (dlg._CancelPressed)
		return;
	int nRet = 0;

	char KYXQ[8+1] = {"20121212"};			
	char GRDH1[20+1] = {"1391321524"}; 			
	char GRDH2[20+1] = {"01084575125"};  
	char ZHFS1[2+1+ 5] = {"1"};			
	char ZHFS2[2+1+ 5] = {"2"}; 			
	char ZHFS3[2+1+ 5] = {"3"};    
	
	strcpy(KYXQ  , dlg.m_edit1);
	strcpy(GRDH1  , dlg.m_edit2);
	strcpy(GRDH2  , dlg.m_edit3);
	strcpy(ZHFS1  , dlg.m_edit4);
	strcpy(ZHFS2  , dlg.m_edit5);
	strcpy(ZHFS3  , dlg.m_edit6);
	
	nRet = 	iW_DDF1EF08Info((HANDLE)g_handle ,
							KYXQ,
							GRDH1,
							GRDH2,
							ZHFS1,
							ZHFS2,
							ZHFS3
							);
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
}




void CInterfaceDemoDlg::OnBUTTONerrmsg() 
{
	char info [100];
//	int nRet =   UH_Reader_GetLastErrorMsg( info);			  

	m_cListBox.ResetContent();
	m_cListBox.AddString(info);
	
}

void CInterfaceDemoDlg::OnButtonMzSign() 
{
	int id = m_cbo_mzid.GetCurSel() + 1;
	BYTE szData[6000];
/*	memset(szData , 0 , sizeof(szData));
	int nRet =  UH_Reader_Sign_DF03ED00((int)g_handle , UHSLOT_PSAM1,
							id,
							szData										  
								);

	if (nRet == 0)
	{
		//������ļ�
		m_cListBox.ResetContent();
		m_cListBox.AddString("��ȡǩ���ɹ�");

		int nDataLen =  3013 + 64 + 190;
		ofstream outfile("DF03ED00.dat", ios::binary);
		if (!outfile)
		{
			m_cListBox.AddString("����outfile����ʧ��");
			nRet = 1;
			throw nRet;
		}
		
		for(int i = 0; i < nDataLen; i++)
		{
			outfile.write((char*)&szData[i], sizeof(szData[i]));
		}
		outfile.close();
		m_cListBox.AddString("DF03ED00.dat�����ڵ�ǰ·����");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	
*/	

	return;
	
}

void CInterfaceDemoDlg::OnButtonZySign() 
{
		int id = m_cbo_zyid.GetCurSel() + 1;
	BYTE szData[2000];
	memset(szData , 0 , sizeof(szData));
/*	int nRet =  UH_Reader_Sign_DF03EE00((int)g_handle , UHSLOT_PSAM1,
							id,
							szData										  
								);
	

	if (nRet == 0)
	{
		//������ļ�

		m_cListBox.ResetContent();
		m_cListBox.AddString("��ȡǩ���ɹ�");
		int nDataLen = 1639 + 64 + 190;
		ofstream outfile("DF03EE00.dat", ios::binary);
		if (!outfile)
		{
			m_cListBox.AddString("����outfile����ʧ��");
			nRet = 1;
			throw nRet;
		}
		
		for(int i = 0; i < nDataLen; i++)
		{
			outfile.write((char*)&szData[i], sizeof(szData[i]));
		}
		outfile.close();
		m_cListBox.AddString("DF03EE00.dat�����ڵ�ǰ·����");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
*/
	return;
}

void CInterfaceDemoDlg::OnButtonPsam() 
{
	CWnd *pWnd = GetTopWindow(); 

	PSAMDialog dlg = new PSAMDialog(pWnd);
	dlg.SetHandle((int)g_handle);
	dlg.DoModal();	
}

void CInterfaceDemoDlg::OnButtonReset() 
{
	int nRet = 0;
	char ATR[60] = {0};
	int resLen;

	memset(ATR, 0, sizeof(ATR));

	if((((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()))
	{
		CString code;
		GetDlgItem(IDC_CITYCODE)->GetWindowText(code);
		strcpy(ATR,"YSDM");
		strcat(ATR,code);	
	}


//	PowerOn(HANDLE hDev,int slot, char * ATR) 

	nRet = PowerOn((HANDLE)g_handle , SLOT_USER , ATR);
	if (nRet != 0)
	{
		MessageBox("�û����ϵ�ʧ��");
		return;
	}

	m_cListBox.ResetContent();
	m_cListBox.AddString(ATR);

	char cardNo[20]={0};
	memcpy(cardNo , ATR + 10 , 16 );

//	m_cListBox.ResetContent();
	CString s;
	s+="��ɢ���ӣ�";
	s+=cardNo;
	m_cListBox.AddString(s);
	
}


void CInterfaceDemoDlg::OnReadall() 
{
	// TODO: Add your control notification handler code here
	/*iW_DF03EE_ALLInfo(hDev,1,"�㶫ʡ����ʡ�˲��еط�˰��|222222|20120123|0212|1234566665");
			char data[3000]={0};
			iR_DF03EE_ALLInfo(hDev,1,data);

			iW_DF03ED_ALLInfo(hDev,1,"�㶫ʡ����ʡ�˲��еط�˰��|222222|20120123");
			char data1[6000]={0};
			iR_DF03ED_ALLInfo(hDev,1,data1);*/

		char chsDATA[0x1000] = {0};	

	int nPos = 0;
	int nLen = 0;
	int style = 0;
	int nRet = 0;
	
	int id = m_cbo_zyid.GetCurSel() + 1;

	nRet = 	iR_DF03EE_ALLInfo((HANDLE)g_handle ,
							id,
							chsDATA								  
							);
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(chsDATA);
		m_out = chsDATA;
		UpdateData(FALSE);

	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	return;
}

void CInterfaceDemoDlg::OnWriteall() 
{
	// TODO: Add your control notification handler code here
	if (MessageBox("��ȷ��Ҫִ��д�������","������ʾ", MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}
	
	int nRet = 0;
	
	int nPos = 0;
	int nLen = 0;
	int style = 0;

	char chsData[MAX_BIN_SIZE] = {0};
	int id = m_cbo_zyid.GetCurSel() + 1;

	(CEdit*)GetDlgItemText(IDC_EDIT_ZY_WDATA, chsData, sizeof(chsData));
	int len = strlen(chsData);
	nRet = iW_DF03EE_ALLInfo((HANDLE)g_handle ,
								id,
								chsData
								);
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
}

void CInterfaceDemoDlg::OnReadedll() 
{
	// TODO: Add your control notification handler code here
			char chsDATA[0x1000] = {0};	

	int nPos = 0;
	int nLen = 0;
	int style = 0;
	int nRet = 0;
	
	int id = m_cbo_mzid.GetCurSel() + 1;

	nRet = 	iR_DF03ED_ALLInfo((HANDLE)g_handle ,
							id,
							chsDATA								  
							);
	
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString(chsDATA);
		m_out = chsDATA;
		UpdateData(FALSE);

	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	return;
}

void CInterfaceDemoDlg::OnWriteedll() 
{
	// TODO: Add your control notification handler code here
	if (MessageBox("��ȷ��Ҫִ��д�������","������ʾ", MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}
	
	int nRet = 0;
	
	int nPos = 0;
	int nLen = 0;
	int style = 0;

	char chsData[MAX_BIN_SIZE] = {0};
	int id = m_cbo_mzid.GetCurSel() + 1;
	
	(CEdit*)GetDlgItemText(IDC_EDIT_MZ_WDATA, chsData, sizeof(chsData));
	int len = strlen(chsData);
	nRet = iW_DF03ED_ALLInfo((HANDLE)g_handle ,
								id,
								chsData
								);
	if (nRet == 0)
	{
		m_cListBox.ResetContent();
		m_cListBox.AddString("д��ɹ�");
		MessageBox("д��ɹ�");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	
	return;
}

void CInterfaceDemoDlg::OnBtnTestzkr() 
{
	char iszData[500]="213002AA315002102150041234";
	int re=HD_WDF03ED00(1,iszData);
}
