// CardDevDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CardDevDemo.h"
#include "CardDevDemoDlg.h"
#include "CardDev.h"
#include <string>
using namespace std;

#pragma comment(lib, "CardDev.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int UnicodeToAnsi(unsigned short *Src, char *Des, int start, int len)
{
	wchar_t wsztemp[70]={0};
	//	char szStr[100];
	for(int i=0;i<len/2;i++)
	{
		wsztemp[i]=Src[2*i]+(Src[2*i+1]<<8);		
	}
	sprintf(Des, "%S", wsztemp);
	return 0;
}

//�ַ���ת��Ϊʮ����������
int StrToHex(unsigned char *strIn, int inLen, unsigned char *strOut)
{
	int j = 0;
	
	int len = strlen((char*)strIn);
	
	if(inLen > len)
	{
		return -2;  //�ַ����ȳ�����Ч��Χ
	}
	
	unsigned char *pstrTemp  = new unsigned char[len+1];
	
	for(int i=0; i<inLen-1; i+=2, j++)
	{
		if(strIn[i]>='0' && strIn[i]<='9')
		{
			pstrTemp[i] = strIn[i] - '0';
		}
		else if(strIn[i]>='A' && strIn[i]<='F')
		{
			pstrTemp[i] = strIn[i] - 'A' + 10;
		}
		else if(strIn[i]>='a' && strIn[i]<='f')
		{
			pstrTemp[i] = strIn[i] - 'a' + 10;
		}
		else
		{
			return -1;     //��ʮ�������ַ�
		}
		
		if(strIn[i+1]>='0' && strIn[i+1]<='9')
		{
			pstrTemp[i+1] = strIn[i+1] - '0';
		}
		else if(strIn[i+1]>='A' && strIn[i+1]<='F')
		{
			pstrTemp[i+1] = strIn[i+1] - 'A' + 10;
		}
		else if(strIn[i+1]>='a' && strIn[i+1]<='f')
		{
			pstrTemp[i+1] = strIn[i+1] - 'a' + 10;
		}
		else
		{
			return -1;     //��ʮ�������ַ�
		}
		
		strOut[j] = (pstrTemp[i] << 4) & 0xF0;
		strOut[j] += pstrTemp[i+1] & 0x0F;
	}
	
	delete []pstrTemp;
	
	return 0;   //�ɹ�����
}

void HexToStr(unsigned char *Src,unsigned char *Des,int len)
{
	char a[3]={0};
	for(int i=0;i<len;i++)
	{
		sprintf(a,"%X",Src[i]);
		if (i==0)
			strcpy((char*)Des,a);
		else
			strcat((char*)Des,a);
	}
}

int UnicodeToANSI( const wstring& str, char* Des)   
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte( CP_ACP, 0,str.c_str(),-1,NULL,0,NULL,NULL );
	pElementText = new char[iTextLen + 1];
	memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
	::WideCharToMultiByte( CP_ACP,0, str.c_str(),-1,pElementText, iTextLen,NULL,NULL );
	strcpy(Des, pElementText);
	delete[] pElementText;
	return 0;
}

int AnsiToUnicode(const char *Src, wchar_t *Des)
{
	int    iLen;
	// Ansi char to Unicode
	iLen = MultiByteToWideChar( CP_ACP, 0, Src, -1, NULL, 0 );
	::MultiByteToWideChar( CP_ACP, 0, Src, -1, Des, iLen );
	return 0;
}

// CCardDevDemoDlg �Ի���

CCardDevDemoDlg::CCardDevDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCardDevDemoDlg::IDD, pParent)
	, m_key(0x60)
	, m_strbuf(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCardDevDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCardDevDemoDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_OPEN, &CCardDevDemoDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CCardDevDemoDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_ACTIVE, &CCardDevDemoDlg::OnBnClickedBtnActive)
	ON_BN_CLICKED(IDC_BTN_AUTH, &CCardDevDemoDlg::OnBnClickedBtnAuth)
	ON_BN_CLICKED(IDC_RADIO1, &CCardDevDemoDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CCardDevDemoDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BTN_READ, &CCardDevDemoDlg::OnBnClickedBtnRead)
	ON_BN_CLICKED(IDC_BTN_WRITE, &CCardDevDemoDlg::OnBnClickedBtnWrite)
	ON_BN_CLICKED(IDC_BTN_CERT, &CCardDevDemoDlg::OnBnClickedBtnCert)
END_MESSAGE_MAP()


// CCardDevDemoDlg ��Ϣ�������

BOOL CCardDevDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

#ifdef WIN32_PLATFORM_WFSP
	if (!m_dlgCommandBar.Create(this) ||
	    !m_dlgCommandBar.InsertMenuBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ��� CommandBar\n");
		return FALSE;      // δ�ܴ���
	}
#endif // WIN32_PLATFORM_WFSP
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//��ʼ������
	SetDlgItemText(IDC_EDIT_KEY, L"FFFFFFFFFFFF");
	//���ں�
	CString strItem = L"";
	int i = 0;
	CComboBox *pCmbComNo = (CComboBox*)GetDlgItem(IDC_CMB_COM_NO);
	pCmbComNo->ResetContent();
	for (i=0; i < 10; i++)
	{
		strItem.Format(L"com%d",i+1);
		pCmbComNo->AddString(strItem);
	}
	pCmbComNo->SetCurSel(0);// com1:

	CComboBox *pCmbNum = (CComboBox*)GetDlgItem(IDC_CMB_COM_NUM);
	pCmbNum->ResetContent();
	for (i=0; i < 64; i++)
	{
		strItem.Format(L"%d",i);
		pCmbNum->AddString(strItem);
	}
	pCmbNum->SetCurSel(0);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CCardDevDemoDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_CARDDEVDEMO_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_CARDDEVDEMO_DIALOG));
	}
}
#endif


void CCardDevDemoDlg::OnBnClickedBtnOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CComboBox *pCmbComNo = (CComboBox*)GetDlgItem(IDC_CMB_COM_NO);
	int port = pCmbComNo->GetCurSel() + 1;

	long ren = hd_Open(port);
	if(ren)
	{
		AfxMessageBox(_T("�򿪶˿�ʧ��"));
		return;
	}
	MessageBox(_T("�򿪶˿ڳɹ�"));
}

void CCardDevDemoDlg::OnBnClickedBtnClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	long ren = hd_Close();
	if(ren)
	{
		AfxMessageBox(_T("�رն˿�ʧ��"));
		return;
	}
	MessageBox(_T("�رն˿ڳɹ�"));
}

void CCardDevDemoDlg::OnBnClickedBtnActive()
{
	// TODO: �ڴ���ӿؼ�֪ͨ���������� 
	TCHAR uid[41] = {0};
	CString temp;
	m_strbuf.Empty();
	long ren = hd_Active(uid);
	if(ren)
	{
		temp.Format(_T("%d"), ren);
		m_strbuf += _T("Ѱ��ʧ��, �����룺");
		m_strbuf += temp;
		SetDlgItemText(IDC_STATIC_RE, m_strbuf);
		return;
	}

	m_strbuf += _T("Ѱ���ɹ�");
	SetDlgItemText(IDC_EDIT_RED, uid);
	SetDlgItemText(IDC_STATIC_RE, m_strbuf);
}

void CCardDevDemoDlg::OnBnClickedBtnAuth()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str, temp;
	char databuf[20] = {0};
	unsigned char data[20] = {0};
	TCHAR data1[20] = {0};
	int stat = 0;
	m_strbuf.Empty();
	CComboBox *pCmbNum = (CComboBox*)GetDlgItem(IDC_CMB_COM_NUM);
	int SecNr = pCmbNum->GetCurSel() / 4;
	GetDlgItemText(IDC_EDIT_KEY, str);

	memcpy(data1, str, str.GetLength()*2);
	UnicodeToANSI(data1, databuf);

	StrToHex((unsigned char*)databuf, 12, data);

	long ren = hd_AuthPass(m_key, SecNr, data);
	if(ren)
	{
		temp.Format(_T("%d"), ren);
		m_strbuf += _T("��֤ʧ��, �����룺");
		m_strbuf += temp;
		SetDlgItemText(IDC_STATIC_RE, m_strbuf);
		return;
	}
	
	m_strbuf += _T("��֤�ɹ�");
	SetDlgItemText(IDC_STATIC_RE, m_strbuf);
	
}

void CCardDevDemoDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_key = 0x60;
}

void CCardDevDemoDlg::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_key = 0x61;
}

void CCardDevDemoDlg::OnBnClickedBtnRead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	unsigned char data[20] = {0};
	char databuf[20] = {0};
	TCHAR data1[20] = {0};
	CString temp;
	m_strbuf.Empty();
	CComboBox *pCmbNum = (CComboBox*)GetDlgItem(IDC_CMB_COM_NUM);
	int Addr = pCmbNum->GetCurSel();
	long ren = hd_Read((unsigned char)Addr, data);
	if(ren)
	{
		temp.Format(_T("%d"), ren);
		m_strbuf += _T("����ʧ��, �����룺");
		m_strbuf += temp;
		SetDlgItemText(IDC_STATIC_RE, m_strbuf);
		return;
	}
	HexToStr((unsigned char *)databuf, data, 8);
	AnsiToUnicode(databuf, data1);
	SetDlgItemText(IDC_EDIT_RED, data1);

	m_strbuf += _T("�����ɹ�");
	SetDlgItemText(IDC_STATIC_RE, m_strbuf);
}

void CCardDevDemoDlg::OnBnClickedBtnWrite()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	unsigned char data[20] = {0};
	char databuf[20] = {0};
	TCHAR data1[20] = {0};
	long ren = -99;
	CString str, temp;
	m_strbuf.Empty();

	CComboBox *pCmbNum = (CComboBox*)GetDlgItem(IDC_CMB_COM_NUM);
	unsigned char Addr = (unsigned char)pCmbNum->GetCurSel();

	GetDlgItemText(IDC_EDIT_RED, str);
	memcpy(data1, str, str.GetLength()*2);
	UnicodeToANSI(data1, databuf);
	StrToHex((unsigned char*)databuf, strlen(databuf), data);
	//temp.Format(L"%d", Addr);
	//AfxMessageBox(temp);
	//AfxMessageBox(L"ִ��д����������������������ᵼ������");

	ren = hd_Write(Addr, data);
	if(ren)
	{
		temp.Format(_T("%d"), ren);
		m_strbuf += _T("д��ʧ��, �����룺");
		m_strbuf += temp;
		SetDlgItemText(IDC_STATIC_RE, m_strbuf);
		return;
	}
	
	m_strbuf += _T("д���ɹ�");
	SetDlgItemText(IDC_STATIC_RE, m_strbuf);
}

void CCardDevDemoDlg::OnBnClickedBtnCert()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR pName[200] = {0};
	TCHAR pSex[50] = {0};
	TCHAR pNation[50] = {0};
	TCHAR pBirth[50] = {0};
	TCHAR pAddress[400] = {0};
	TCHAR pCertNo[100] = {0};
	TCHAR pDepartment[100] = {0};
	TCHAR pEffectTime[100] = {0};
	TCHAR pExpire[100] = {0};
	int i = 0;
	//TCHAR pBmpFile[256] = L"\\Temp\\zp.bmp";
	//TCHAR *pBmpData = new TCHAR[77725];
	//TCHAR pBmpData[256] = {0};
	CString str, temp;
	m_strbuf.Empty();
	TCHAR wFilePath[256] = {0};
	char FilePath[256] = {0};

	GetModuleFileName(NULL, wFilePath, 256);
	//UnicodeToANSI(wFilePath, FilePath);
	for(i=wcslen(wFilePath)-1; i>0; i--)
	{
		if(wFilePath[i] == '\\')
		{
			memset(wFilePath+i+1, 0, wcslen(wFilePath)-i);
			memset(wFilePath+i+1, 0, (wcslen(wFilePath)-i)*sizeof(wchar_t));
			memcpy(wFilePath+i+1, L"zp.bmp", 12);
			break;
		}
	}

	long ren = hd_ReadIDCard(wFilePath, pName, pSex, pNation, pBirth, pAddress, pCertNo, pDepartment, pEffectTime,  pExpire);
	if(ren)
	{
		temp.Format(_T("%d"), ren);
		m_strbuf += _T("��ȡ���֤��Ϣʧ��, �����룺");
		m_strbuf += temp;
		SetDlgItemText(IDC_STATIC_RE, m_strbuf);
		return;
	}

	str += L"������";
	str += pName;
	str += L"\r\n";
	str += L"�Ա�";
	str += pSex;
	str += L"\r\n";
	str += L"���壺";
	str += pNation;
	str += L"\r\n";
	str += L"�������ڣ�";
	str += pBirth;
	str += L"\r\n";
	str += L"סַ��";
	str += pAddress;
	str += L"\r\n";
    str += L"���֤�ţ�";
	str += pCertNo;
	str += L"\r\n";
	str += L"��֤���أ�";
	str += pDepartment;
	str += L"\r\n";
	str += L"��֤���ڣ�";
	str += pEffectTime;
	str += L"\r\n";
	str += L"��Ч�ڣ�";
	str += pExpire;
	MessageBox(str);
}
