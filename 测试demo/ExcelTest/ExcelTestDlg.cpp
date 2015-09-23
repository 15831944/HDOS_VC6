// ExcelTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExcelTest.h"
#include "ExcelTestDlg.h"

//���ȱ����˰���ͷ�ļ���excel.h�������õ�_variant_t()ʱ����Ҫ����ͷ�ļ���comdef.h���͡�comutil.h�����������ִ���
//��error C2065: '_variant_t' : undeclared identifier��
#include "excel.h"
#include "comdef.h"//��߶����˸��ֽӿڼ��࣬��ʵ��COM����Ļ�������
#include "comutil.h"
#include <direct.h>

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
// CExcelTestDlg dialog

CExcelTestDlg::CExcelTestDlg(CWnd* pParent /*=NULL*/)
: CDialog(CExcelTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExcelTestDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExcelTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExcelTestDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExcelTestDlg, CDialog)
//{{AFX_MSG_MAP(CExcelTestDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_EXCELTEST, OnExceltest)
ON_BN_CLICKED(IDC_OPEN_ADD, OnOpenAdd)
ON_BN_CLICKED(IDC_OPEN_READ, OnOpenRead)
ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExcelTestDlg message handlers

BOOL CExcelTestDlg::OnInitDialog()
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

void CExcelTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExcelTestDlg::OnPaint() 
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
HCURSOR CExcelTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//���ܣ���Excel�ļ�,ʹ��Excel������ʾ���������ݣ�Ҳ��д������,�ֹ�ʹ�����ر�Excel�ļ���
//hlt2012.4.1
void CExcelTestDlg::OnExceltest() 
{
//_Application		CApplicaton		Application.h	ExcelӦ�÷��ȡ�
/*
	Workbooks	CWorkbooks	Workbooks.h	�����������������������ExcelӦ�÷��ȴ򿪵����й�������

	_Workbook	CWorkbook	Workbook.h		������������

	Worksheets	CWorksheets	Worksheets.h	�����������е�Sheet����������
											�����ù������е�����Sheet��

	_Worksheet	CWorksheet	Worksheet.h	   ����Sheet���
		
	Range	CRange	Range.h	��Ȼ�����ĵ�λ�񣬿ɶԵ�λ����е���������λ����в��ݡ�
*/
	// TODO: Add your control notification handler code here
	CString path;
	
	CString  str_t;
	CTime t = CTime::GetCurrentTime();//����ǰҪ��CTime::����Ȼ����ת�����ִ�����
	int m_year = t.GetYear();
	int m_month = t.GetMonth();
	int m_day = t.GetDay();
	
	str_t.Format("\SSC_%d.%d.%d.",m_year,m_month,m_day);
	
	//sInfoPath = "F:\\Card��Ϣ";
	//sInfoPath = "\Card��Ϣ";
	sInfoPath = str_t;
	//	sInfoPath = sInfoPath + str_t;
	//DeleteFile(picPathstr);
	//����EXCELĿ¼
//	path = sInfoPath;
//	_mkdir(path);//Ҫ#include <direct.h>
	
	//��������excel�ļ���Ķ���
    _Application objApp;// _application������EXCEL������   
    Workbooks objBooks; //workbooks��ʾ����Excel������(����Ϊһ��.xls�ļ�)�����еı�,
					//(����ͨ��"�½�"�õ������,��MDI�������һ���Ӵ�һ��,���е��Ӵ�����workbooks), 
   	COleVariant VOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
    
	//���������Ƿ�װ��Excel����
    if(!objApp.CreateDispatch("Excel.Application"))     
	{ AfxMessageBox("�޷�����Excel��������ȷ��װ!");     
	return;     
	}     
	
    objApp.m_bAutoRelease   =   TRUE; //??ʲô��˼��
	objApp.SetVisible(TRUE);  //��Excel����û����ʾ�κ����ݡ� 
	
	objApp.SetUserControl(TRUE);//���������û�����Excel,����Excel��һ������
	
	//��������Ĺ��ܺ� objBooks = objApp.GetWorkbooks();  һ����
    LPDISPATCH   pWkBooks   =   objApp.GetWorkbooks();  //GetWorkbooksʲô���ܣ�
	objBooks.AttachDispatch(pWkBooks,TRUE);   //��һ��IDispatch���Ӹ�����COleDispatchDriver����
    
	//��õ�ǰ�������ڵ�·��,excel�ļ��ڴ�·���¡�
    char CurrentProgramPath[MAX_PATH];     
    GetCurrentDirectory(MAX_PATH,CurrentProgramPath);   
    CString ExcelFilePathName =  CurrentProgramPath;//ExcelFilePathName��ʾexcel�ļ���·�����ļ��� 
    //ExcelFilePathName   +=   "\\CardInfo.xls"; 
	ExcelFilePathName   +=   "\\sInfoPath";
	ExcelFilePathName   +=   ".xls";
	
    //��Excel�ļ������ǰ��������objApp.SetVisible(TRUE)�������¾�����ִ�к�
														//��ʾ���excel�ļ������ݡ�
	//���ǰ��û������objAppApp.SetVisible(TRUE)���¾�����ִ�к󣬲�����ʾ���Excel�ļ������ݡ�
    //����ֻ����ʽ��excel�ļ���_variant_t(true), true����ΪСд����д�������
	objBooks.Open(ExcelFilePathName,VOptional, _variant_t(false), VOptional, VOptional, VOptional, VOptional, VOptional,     
		VOptional,  VOptional,  VOptional,   VOptional, VOptional,VOptional,VOptional);   
	
	
}

//��Excel�ļ����������е����ݣ�����������Mschart�ؼ�ʹ�á�
void CExcelTestDlg::OnOpenRead() 
{
	// TODO: Add your control notification handler code here
	
	//Excel�ļ�ʹ�����У���һ�б�ʾ��ţ��ڶ��б�ʾ��һ��ݵ����ݣ��ڶ��б�ʾ�ڶ���ݵ����ݡ�
	//��������excel�ļ���Ķ���
	_Application objApp;  //_application������EXCEL������  
    Workbooks objBooks;//workbooks��ʾ����Excel������(����Ϊһ��.xls�ļ�)�����еı�,
	//(����ͨ��"�½�"�õ������,��MDI�������һ���Ӵ�һ��,���е��Ӵ�����workbooks), 
    _Workbook objBook;//_workbook����һ����,�൱��MDI�е�һ���Ӵ�, 
    Worksheets objSheets; // worksheets��ʾ���еı�,ÿ���������кܶ��,
	//(����һ��Excel�ļ�֮��,��,���Կ�����sheet1,sheet2��,������Щsheetn�������worksheets)  
    _Worksheet objSheet;//_worksheet�ͱ�ʾһ����,

    Range objRange,usedRange;//Range ��ʾԪ�صļ���  

    COleVariant VOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	
    VARIANT ret;
    CString cstr="";//���ն�ȡ��������
	
	//���������Ƿ�װ��Excel����
    if(!objApp.CreateDispatch("Excel.Application"))     
	{ AfxMessageBox("�޷�����Excel������!");     
	return;     
	}     
	
    //objApp.SetVisible(TRUE);  //��Excel����û����ʾ�κ����ݡ�
	
	// objApp.SetUserControl(FALSE);//���������û�����Excel,����Excel��һ������
    
	// objApp.m_bAutoRelease   =   TRUE; //??ʲô��˼��
	
	objBooks = objApp.GetWorkbooks();
	
    //��õ�ǰ�������ڵ�·��,excel�ļ��ڴ�·���¡�
    char CurrentProgramPath[MAX_PATH];     
    GetCurrentDirectory(MAX_PATH,CurrentProgramPath);   
    CString ExcelFilePathName =  CurrentProgramPath;//ExcelFilePathName��ʾexcel�ļ���·�����ļ��� 
    ExcelFilePathName   +=   "\\sInfoPath";
	ExcelFilePathName   +=   ".xls";    
	
    //��Excel�ļ������ǰ��������objApp.SetVisible(TRUE)�������¾�����ִ�к���ʾ���excel�ļ������ݡ�
	//���ǰ��û������objAppApp.SetVisible(TRUE)���¾�����ִ�к󣬲�����ʾ���Excel�ļ������ݡ�
    //����ֻ����ʽ��excel�ļ���_variant_t(true), true����ΪСд����д�������
    objBook = objBooks.Open(ExcelFilePathName,VOptional, _variant_t(true), VOptional, VOptional,  VOptional, 
		VOptional, VOptional, VOptional,  VOptional, VOptional, VOptional, VOptional,  VOptional, VOptional);
	
    objSheets = objBook.GetWorksheets();
    //�趨��ǰ�Ĺ�����sheet��excel�ļ��ĵڼ���������
	//sheet COleVariant((short)1)��ʾ��һ�� COleVariant((short)2)��ʾ�ڶ���
    objSheet = objSheets.GetItem(COleVariant((short)1));
	
    //����Ѿ�ʹ�õ�������������
    usedRange.AttachDispatch(objSheet.GetUsedRange());  
	
    objRange.AttachDispatch(usedRange.GetRows());
    long   iRowNum=objRange.GetCount();//�Ѿ�ʹ�õ�����

    objRange.AttachDispatch(usedRange.GetColumns());
    long iColumnNum=objRange.GetCount();//�Ѿ�ʹ�õ�����
	
    //�趨��ȡ�����з�Χ
    //objRange = objSheet.GetRange(COleVariant("A1"), COleVariant("C1000"));
    ret = objRange.GetValue(VOptional);
    COleSafeArray sa(ret);
	
	//�������ݡ�
    long lNumRows; long lNumCols;
    sa.GetUBound(1, &lNumRows); sa.GetUBound(2, &lNumCols);
	
    long index[2];
    VARIANT val;
    int row, column;
	
    for(row=1;row<=iRowNum;row++)//row��ʾ����
	{   
		for(column=1;column<=iColumnNum;column++)//c��ʾ����
			
		{	
			index[0]=row;index[1]=column;
			sa.GetElement(index, &val);//val������а���ȡ��row�С�column�е�����
			switch(val.vt)
			{
			case VT_R8:   //����
				{ //TRACE("\t\t%1.2f", val.dblVal);
					CString cstr2=""; 
					cstr2.Format("%1.1f",val.dblVal); cstr+=cstr2+"\n";
					break;
				}
			case VT_BSTR:  //����
				{//TRACE("\t\t%s",(CString)val.bstrVal);
					cstr+=(CString)val.bstrVal+"\n";
					break;
				}
			case VT_EMPTY://��ʾ��row�С�column�е�����Ϊ�ա�
				break;
			}
		}
	}
    AfxMessageBox(cstr);
	
    objBook.Close(COleVariant((short)FALSE),VOptional,VOptional);
    objApp.Quit();
	
	
}


//��һ��Excel�ļ�����ǰ������ݺ�������µ�����
void CExcelTestDlg::OnOpenAdd() 
{
	// TODO: Add your control notification handler code here
	HRESULT hr; 
	hr = CoInitialize(NULL); 
	bool isExist=true;
	//��������excel�ļ���Ķ���
	_Application   objApp;   //����������ĸ���classes   //_application������EXCEL������    
	Workbooks   objBooks;//workbooks��ʾ����Excel������(����Ϊһ��.xls�ļ�)�����еı�,(����ͨ��"�½�"�õ������,��MDI�������һ���Ӵ�һ��,���е��Ӵ�����workbooks), 
	_Workbook   objBook;     //_workbook����һ����,�൱��MDI�е�һ���Ӵ�, 
	Worksheets   objSheets;  // worksheets��ʾ���еı�,ÿ���������кܶ��(����һ��Excel�ļ�֮��,��,���Կ�����sheet1,sheet2��,������Щsheetn�������worksheets)  
	_Worksheet   objSheet;  //_worksheet�ͱ�ʾһ����,   
	Range   objRange,usedRange; //Range ��ʾԪ�صļ���  
	COleVariant VOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	objApp.SetAlertBeforeOverwriting(FALSE);
	objApp.SetDisplayAlerts(FALSE);
	//���������Ƿ�װ��Excel����
	if(!objApp.CreateDispatch("Excel.Application"))   //����������     
	{   AfxMessageBox("�޷�����Excel������!");     
	return;     
	} 
	
	//��õ�ǰ�������ڵ�·��,excel�ļ��ڴ�·���¡�
	char CurrentProgramPath[MAX_PATH];     
	GetCurrentDirectory(MAX_PATH,CurrentProgramPath);   
	CString ExcelFilePathName =  CurrentProgramPath; 
	//ExcelFilePathName��ʾexcel�ļ���·�����ļ��� 
	ExcelFilePathName   +=   "\\sInfoPath";
	ExcelFilePathName   +=   ".xls"; 
	
	objBooks=objApp.GetWorkbooks();
	//�˾�Ĺ���objBooks = objApp.GetWorkbooks();һ��
	//��Excel�ļ������ǰ��������objApp.SetVisible(TRUE)�������¾�����ִ�к���ʾ���excel�ļ������ݡ�
	//���ǰ��û������objAppApp.SetVisible(TRUE)���¾�����ִ�к󣬲�����ʾ���Excel�ļ������ݡ�
	try
	{
	objBook = objBooks.Open(ExcelFilePathName,VOptional,VOptional,
		VOptional,VOptional,VOptional,
		VOptional,VOptional,VOptional,
		VOptional,VOptional,VOptional,
		VOptional,VOptional,VOptional);   
	}catch(...)
	{
		objBook=objBooks.Add(vtMissing);
		isExist=false;
		//MessageBox("aaa");
	}

	objSheets = objBook.GetWorksheets(); 
	try
	{
		objSheet = objSheets.GetItem(COleVariant((short)1));
	}catch(...)
	{
		objSheet=objSheets.Add(vtMissing, vtMissing, _variant_t((long)1), vtMissing);
		//objSheet.SetName("test");
	}

	objRange.AttachDispatch(objSheet.GetCells(),true);

	
	//����Ѿ�ʹ�õ�����
	usedRange = objSheet.GetUsedRange();

	usedRange = usedRange.GetRows();
	long iRowNum=usedRange.GetCount();//�Ѿ�ʹ�õ����� 

	objRange.SetItem(COleVariant(long(1)),COleVariant(long(1)),COleVariant("header"));     
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(2)),COleVariant("header")); 
	
	objRange.SetItem(COleVariant(long(iRowNum+1)),COleVariant(long(1)),COleVariant("12"));     
	objRange.SetItem(COleVariant(long(iRowNum+1)),COleVariant(long(2)),COleVariant("34")); 
	
	if(isExist)
		objBook.Save();//����򿪵����excel�ļ��������Ľ����Ѿ����ˣ��˾����ִ�к󣬻������ʾ�Ƿ񱣴�ĶԻ���
	////����򿪵����excel�ļ��������Ľ���ʹ��ֻ����ʽ�Ѿ����ˣ��˾����ִ�к󣬲��������ʾ�Ƿ񱣴�ĶԻ���
	objBook.SetSaved(TRUE);
	if(!isExist)
		objBook.SaveAs(_variant_t(ExcelFilePathName),_variant_t(long(18)), vtMissing, vtMissing, vtMissing, 
			vtMissing, 0, vtMissing, vtMissing, vtMissing, 
			vtMissing, vtMissing);
	objRange.ReleaseDispatch();
	objRange.Clear();  
	objBook.Close(COleVariant((short)FALSE),VOptional,VOptional);
	objBooks.Close();     
	objApp.Quit();   
	
	
	
	
}

//����
void CExcelTestDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	this->OnExceltest();
	
}
