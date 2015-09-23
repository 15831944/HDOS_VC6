// HD_ReadDemo_HNDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HD_ReadDemo_HN.h"
#include "HD_ReadDemo_HNDlg.h"

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
// CHD_ReadDemo_HNDlg dialog

CHD_ReadDemo_HNDlg::CHD_ReadDemo_HNDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHD_ReadDemo_HNDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHD_ReadDemo_HNDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHD_ReadDemo_HNDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHD_ReadDemo_HNDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHD_ReadDemo_HNDlg, CDialog)
	//{{AFX_MSG_MAP(CHD_ReadDemo_HNDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	ON_BN_CLICKED(IDC_BTN_SAMON, OnBtnSamon)
	ON_BN_CLICKED(IDC_BTN_READ, OnBtnRead)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	ON_BN_CLICKED(IDC_BTN_TEST, OnBtnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHD_ReadDemo_HNDlg message handlers

BOOL CHD_ReadDemo_HNDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHD_ReadDemo_HNDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHD_ReadDemo_HNDlg::OnPaint() 
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
HCURSOR CHD_ReadDemo_HNDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHD_ReadDemo_HNDlg::OnBtnOpen() 
{
//	CString account,password,doctype,funtype,userid,para;
//	this->GetDlgItemText(IDC_EDIT_USERNAME,account);
//	this->GetDlgItemText(IDC_EDIT_PASSWORD,password);
//	this->GetDlgItemText(IDC_EDIT_DOCTYPE,doctype);
//	this->GetDlgItemText(IDC_EDIT_FUNTYPE,funtype);
//	this->GetDlgItemText(IDC_EDIT_OPERID,userid);
//	this->GetDlgItemText(IDC_EDIT_PARA,para);
//	int i=IDOpenPort(account.GetBuffer(0),password.GetBuffer(0));//�����豸
//	account.ReleaseBuffer();
//	password.ReleaseBuffer();
//	CString temp;
//	if(i)
//	{
//		temp.Format("���豸ʧ�ܣ��������:%d",i);
//		this->SetDlgItemText(IDC_EDIT_DATA,temp);
//	}
//	else
//	{
//		temp.Format("���豸�ɹ�");
//		this->SetDlgItemText(IDC_EDIT_DATA,temp);
//	}
}

void CHD_ReadDemo_HNDlg::OnBtnClose() 
{
//	IDClosePort();
}

void CHD_ReadDemo_HNDlg::OnBtnSamon() 
{
//	CString account,password,doctype,funtype,userid,para,sampin;
//	this->GetDlgItemText(IDC_EDIT_USERNAME,account);
//	this->GetDlgItemText(IDC_EDIT_PASSWORD,password);
//	this->GetDlgItemText(IDC_EDIT_DOCTYPE,doctype);
//	this->GetDlgItemText(IDC_EDIT_FUNTYPE,funtype);
//	this->GetDlgItemText(IDC_EDIT_OPERID,userid);
//	this->GetDlgItemText(IDC_EDIT_PARA,para);
//	this->GetDlgItemText(IDC_EDIT_SAMPIN,sampin);
//	HANDLE hDev;
//	char ATR[50]={0};
//	int idoctype=atoi(doctype.GetBuffer(0));
//	int i=IPowerOn(hDev,0x11,ATR,account.GetBuffer(0),password.GetBuffer(0),
//		idoctype,para.GetBuffer(0),userid.GetBuffer(0),sampin.GetBuffer(0));
//	CString temp;
//	if(i)
//	{
//		temp.Format("SAM���ϵ�ʧ�ܣ��������:%d",i);
//		this->SetDlgItemText(IDC_EDIT_DATA,temp);
//	}
//	else
//	{
//		temp.Format("SAM�ϵ�ɹ�");
//		this->SetDlgItemText(IDC_EDIT_DATA,temp);
//	}
}

void CHD_ReadDemo_HNDlg::OnBtnCardon() 
{
//	CString account,password,doctype,funtype,userid,para,sampin;
//	this->GetDlgItemText(IDC_EDIT_USERNAME,account);
//	this->GetDlgItemText(IDC_EDIT_PASSWORD,password);
//	this->GetDlgItemText(IDC_EDIT_DOCTYPE,doctype);
//	this->GetDlgItemText(IDC_EDIT_FUNTYPE,funtype);
//	this->GetDlgItemText(IDC_EDIT_OPERID,userid);
//	this->GetDlgItemText(IDC_EDIT_PARA,para);
//	this->GetDlgItemText(IDC_EDIT_SAMPIN,sampin);
//	HANDLE hDev;
//	char ATR[50]={0};
//	int idoctype=atoi(doctype.GetBuffer(0));
//	int i=IPowerOn(hDev,0x01,ATR,account.GetBuffer(0),password.GetBuffer(0),
//		idoctype,para.GetBuffer(0),userid.GetBuffer(0),sampin.GetBuffer(0));
//	CString temp;
//	if(i)
//	{
//		temp.Format("�������ϵ�ʧ�ܣ��������:%d",i);
//		this->SetDlgItemText(IDC_EDIT_DATA,temp);
//	}
//	else
//	{
//		temp.Format("�������ϵ�ɹ�");
//		this->SetDlgItemText(IDC_EDIT_DATA,temp);
//	}
}

void CHD_ReadDemo_HNDlg::OnBtnRead() 
{
	CString account,password,doctype,funtype,userid,para,sampin;
	this->GetDlgItemText(IDC_EDIT_USERNAME,account);
	this->GetDlgItemText(IDC_EDIT_PASSWORD,password);
	this->GetDlgItemText(IDC_EDIT_DOCTYPE,doctype);
	this->GetDlgItemText(IDC_EDIT_OPERID,userid);
	this->GetDlgItemText(IDC_EDIT_PARA,para);
	this->GetDlgItemText(IDC_EDIT_SAMPIN,sampin);
	char ATR[50]={0};
	int idoctype=atoi(doctype.GetBuffer(0));
	char dataOut[10000]={0};
	int i=ReadCard(para.GetBuffer(0),dataOut,account.GetBuffer(0),password.GetBuffer(0),atoi(doctype),userid.GetBuffer(0),
					sampin.GetBuffer(0));
	CString temp;
	if(i)
	{
		temp.Format("������ʧ�ܣ��������:%d",i);
		this->SetDlgItemText(IDC_STATIC_STATE,temp);
	}
	else
	{
		this->SetDlgItemText(IDC_EDIT_DATA,dataOut);
	}
	if(0==strcmp(para,"102"))
	{
		unsigned char strOut[4000]={0};
		StrToHex((unsigned char *)dataOut,strlen(dataOut),strOut);

		char temp1[10]={0};
		sprintf(temp1,"%02x%02x",strOut[0],strOut[1]);
		long len=strtol(temp1,NULL,16);

//		CFile file("test.jpg",CFile::modeRead);
//		long len=file.GetLength();
//		char buf[8000]={0};
//		file.Read(buf,len);
//		file.Close();

		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, (unsigned int)len);    
		if (hGlobal== NULL)   
		{  
			temp="�����ڴ����!";
			this->SetDlgItemText(IDC_STATIC_STATE,temp);
			return ;  
		} 
		// �����ղŷ�����ڴ�ռ�  
		LPVOID pvData = NULL;    
		pvData = GlobalLock(hGlobal);  
		if (pvData == NULL)    
		{    
            GlobalFree(hGlobal);  // �ǵ��ͷ��ڴ� 
			temp="�����ڴ����!";
			this->SetDlgItemText(IDC_STATIC_STATE,temp);
            return;  
		}
		// ����Ƭ���ݷŵ�����  
		IStream *pStm;    
		memcpy(pvData,strOut+2,len);
		//memcpy(pvData,buf,len);
		GlobalUnlock(hGlobal);    
		CreateStreamOnHGlobal(hGlobal, TRUE, &pStm);
		// �����м���ͼƬ  
		// ��ʾJPEG��GIF��ʽ��ͼƬ��GIFֻ����ʾһ֡����������ʾ������  
		// Ҫ��ʾ����GIF��ʹ��ACTIVE�ؼ���  
		IPicture *pPic;   
		if(OleLoadPicture(pStm,(LONG)len,TRUE,IID_IPicture,(LPVOID*)&pPic)!=S_OK)   
		{   
			GlobalFree(hGlobal);  // �ǵ��ͷ��ڴ�  
			temp="������ͼƬ����!";
			this->SetDlgItemText(IDC_STATIC_STATE,temp);
			return;  
		}
	    //��ȡͼ���͸�,ע������Ŀ�͸߲���ͼ��ķֱ���  
		OLE_XSIZE_HIMETRIC hmWidth;    
		OLE_YSIZE_HIMETRIC hmHeight;    
		pPic->get_Width(&hmWidth);    
		pPic->get_Height(&hmHeight);
		CSize sz(hmWidth,hmHeight);   //��ȡԭʼ��С
		CDC *pDC=this->GetDC();
		pDC->HIMETRICtoDP(&sz);
		RECT rtWnd;
		pDC->GetWindow()->GetWindowRect(&rtWnd);  
		int iWndWidth=rtWnd.right-rtWnd.left;  
		int iWndHeight=rtWnd.bottom-rtWnd.top;  
		
		if(FAILED(pPic->Render(*pDC,30,30,sz.cx,sz.cy,0,hmHeight,hmWidth,-hmHeight,NULL)))    
		{  
			pPic->Release();  
			GlobalFree(hGlobal);  // �ǵ��ͷ��ڴ�  
			temp="��ʾͼƬ����!";
			this->SetDlgItemText(IDC_STATIC_STATE,temp);
			return;  
		}  
		pPic->Release();   
		GlobalFree(hGlobal);  // �ǵ��ͷ��ڴ�  
	}
}

void CHD_ReadDemo_HNDlg::OnBtnSamau() 
{
}

void CHD_ReadDemo_HNDlg::OnBtnWrite() 
{
	CString account,password,doctype,funtype,userid,para,sampin,value;
	this->GetDlgItemText(IDC_EDIT_USERNAME,account);
	this->GetDlgItemText(IDC_EDIT_PASSWORD,password);
	this->GetDlgItemText(IDC_EDIT_DOCTYPE,doctype);
	this->GetDlgItemText(IDC_EDIT_OPERID,userid);
	this->GetDlgItemText(IDC_EDIT_PARA,para);
	this->GetDlgItemText(IDC_EDIT_SAMPIN,sampin);
	this->GetDlgItemText(IDC_EDIT_VALUE,value);
	char ATR[50]={0};
	int idoctype=atoi(doctype.GetBuffer(0));
	char dataOut[5000]={0};
	int i=WriteCard(para.GetBuffer(0),value.GetBuffer(0),account.GetBuffer(0),password.GetBuffer(0),atoi(doctype),userid.GetBuffer(0),
					sampin.GetBuffer(0));
	CString temp;
	if(i)
	{
		temp.Format("д����ʧ�ܣ��������:%d",i);
		this->SetDlgItemText(IDC_EDIT_DATA,temp);
	}
	else
	{
		this->SetDlgItemText(IDC_EDIT_DATA,"д���ݳɹ�!");
	}
}

void CHD_ReadDemo_HNDlg::OnBtnTest() 
{
}
