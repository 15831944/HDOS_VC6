// InputDialog.cpp : implementation file
//

#include "stdafx.h"
#include "InterfaceDemo.h"
#include "InputDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// InputDialog dialog
static int _formType;

InputDialog::InputDialog(CWnd* pParent /*=NULL*/)
	: CDialog(InputDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(InputDialog)
	m_static1 = _T("");
	m_static2 = _T("");
	m_static3 = _T("");
	m_static4 = _T("");
	m_static5 = _T("");
	m_static6 = _T("");
	m_static7 = _T("");
	m_static8 = _T("");
	m_static9 = _T("");
	m_edit1 = _T("");
	m_edit2 = _T("");
	m_edit3 = _T("");
	m_edit4 = _T("");
	m_edit5 = _T("");
	m_edit6 = _T("");
	m_edit7 = _T("");
	m_edit8 = _T("");
	m_edit9 = _T("");
	m_static10 = _T("");
	m_edit10 = _T("");
	//}}AFX_DATA_INIT

//	switch (type)
//	{
//	case 0 :
//		m_static1 = "����1";
//		UpdateData(TRUE);
//		break;
//
//	case 1:
//		m_static1 = "����1";
//		UpdateData(TRUE);
//		break;
//	}
}


void InputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InputDialog)
	DDX_Control(pDX, IDC_EDIT1, m_cedit1);
	DDX_Text(pDX, IDC_STATIC1, m_static1);
	DDX_Text(pDX, IDC_STATIC2, m_static2);
	DDX_Text(pDX, IDC_STATIC3, m_static3);
	DDX_Text(pDX, IDC_STATIC4, m_static4);
	DDX_Text(pDX, IDC_STATIC5, m_static5);
	DDX_Text(pDX, IDC_STATIC6, m_static6);
	DDX_Text(pDX, IDC_STATIC7, m_static7);
	DDX_Text(pDX, IDC_STATIC8, m_static8);
	DDX_Text(pDX, IDC_STATIC9, m_static9);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_EDIT4, m_edit4);
	DDX_Text(pDX, IDC_EDIT5, m_edit5);
	DDX_Text(pDX, IDC_EDIT6, m_edit6);
	DDX_Text(pDX, IDC_EDIT7, m_edit7);
	DDX_Text(pDX, IDC_EDIT8, m_edit8);
	DDX_Text(pDX, IDC_EDIT9, m_edit9);
	DDX_Text(pDX, IDC_STATIC10, m_static10);
	DDX_Text(pDX, IDC_EDIT10, m_edit10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InputDialog, CDialog)
	//{{AFX_MSG_MAP(InputDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InputDialog message handlers

void InputDialog::OnCancel() 
{
	m_edit1 = _T("");
	m_edit2 = _T("");
	m_edit3 = _T("");
	m_edit4 = _T("");
	m_edit5 = _T("");
	m_edit6 = _T("");
	m_edit7 = _T("");
	m_edit8 = _T("");
	m_edit9 = _T("");
	_CancelPressed = true;
	CDialog::OnCancel();
}


int CheckDec(CString strIN)
{
	char StrIN[256];
	strcpy(StrIN , strIN);
	int Lng,i;
	char C[2];
	Lng=strlen(StrIN);
	for(i=1;i<=Lng;i++)
	{
		memcpy(C,StrIN+i-1,1);
		if (!((C[0]>=0x30 )&&(C[0]<=0x39)))
		return -1;
	}
	return 0;
}


int CheckHex(CString strIN)
{
	char StrIN[256];
	strcpy(StrIN , strIN);
	int Lng,i;
	char C[2];
	Lng=strlen(StrIN);
	for(i=1;i<=Lng;i++)
	{
		memcpy(C,StrIN+i-1,1);
		if (  !((C[0]>=0x30 && C[0]<=0x39)||(C[0]>=0x41 && C[0]<=0x46)||(C[0]>=0x61 && C[0]<=0x66))  )
		return -1;
	}
	return 0;
}


bool isErase(CString t)
{
	CString tmp ;
	tmp = t;
	tmp.MakeLower();
	if (tmp.Compare("%erase%") )
		return false;
	else
		return true;
}

void InputDialog::OnOK() 
{
	UpdateData(TRUE);
	int i;
	switch(_formType) 
	{
	case FILE_DDF1EF08:
		if (!isErase(m_edit1))
		{
			if ((m_edit1.GetLength() > 8) ||(CheckDec(m_edit1) != 0))
			{
				MessageBox("����Ч�����ݴ���","", MB_ICONERROR);
				return;
			}
		}
		i = strlen(m_edit2);
		if (i > 20) 
		{
			MessageBox("���˵绰1���ݴ���","", MB_ICONERROR);
			return;
		}
		i = strlen(m_edit3);
		if (i > 20) 
		{
			MessageBox("���˵绰2���ݴ���","", MB_ICONERROR);
			return;
		}
		if (!isErase(m_edit4))
		{
		if ((m_edit4.GetLength() > 2) ||(CheckDec(m_edit4) != 0))
		{
			MessageBox("ҽ�Ʒ���֧����ʽ1���ݴ���","", MB_ICONERROR);
			return;
		}}
		if (!isErase(m_edit5))
		{
		if ((m_edit5.GetLength() > 2) ||(CheckDec(m_edit5) != 0))
		{
			MessageBox("ҽ�Ʒ���֧����ʽ2���ݴ���","", MB_ICONERROR);
			return;
		}}
		if (!isErase(m_edit6))
		{
		if ((m_edit6.GetLength() > 2) ||(CheckDec(m_edit6) != 0))
		{
			MessageBox("ҽ�Ʒ���֧����ʽ6���ݴ���","", MB_ICONERROR);
			return;
		}}
		
		break;
	case FILE_DF01EF05:
		if (!isErase(m_edit1))
		{
		if ((m_edit1.GetLength() > 2) ||(CheckDec(m_edit1) != 0))
		{
			MessageBox("��ַ���1���ݴ���","", MB_ICONERROR);
			return;
		}}
		i = strlen(m_edit2);
		if (i > 100) 
		{
			MessageBox("��ַ1���ݴ���","", MB_ICONERROR);
			return;
		}
		if (!isErase(m_edit3))
		{
		if ((m_edit3.GetLength() > 2) ||(CheckDec(m_edit3) != 0))
		{
			MessageBox("��ַ���2���ݴ���","", MB_ICONERROR);
			return;
		}}
		i = strlen(m_edit4);
		if (i > 100) 
		{
			MessageBox("��ַ2���ݴ���","", MB_ICONERROR);
			return;
		}
		break;
	case FILE_DF01EF06:
		i = strlen(m_edit1);
		if (i > 30) 
		{
			MessageBox("��ϵ������1���ݴ���","", MB_ICONERROR);
			return;
		}
		if (!isErase(m_edit2))
		{
			if ((m_edit2.GetLength() > 2) ||(CheckDec(m_edit2) != 0))
			{
				MessageBox("��ϵ�˹�ϵ1���ݴ���","", MB_ICONERROR);
				return;
			}
		}
		if (strlen(m_edit3) > 20) 
		{
			MessageBox("��ϵ�˵绰1���ݴ���","", MB_ICONERROR);
			return;
		}
		i = strlen(m_edit4);
		if (i > 30) 
		{
			MessageBox("��ϵ������2���ݴ���","", MB_ICONERROR);
			return;
		}
		if (!isErase(m_edit5))
		{
			if ((m_edit5.GetLength() > 2) ||(CheckDec(m_edit5) != 0))
			{
				MessageBox("��ϵ�˹�ϵ2���ݴ���","", MB_ICONERROR);
				return;
			}
		}
		if (strlen(m_edit6) > 20) 
		{
			MessageBox("��ϵ�˵绰2���ݴ���","", MB_ICONERROR);
			return;
		}
		i = strlen(m_edit7);
		if (i > 30) 
		{
			MessageBox("��ϵ������3���ݴ���","", MB_ICONERROR);
			return;
		}
		if (!isErase(m_edit8))
		{
		if ((m_edit8.GetLength() > 2) ||(CheckDec(m_edit8) != 0))
		{
			MessageBox("��ϵ�˹�ϵ3���ݴ���","", MB_ICONERROR);
			return;
		}}
		if (strlen(m_edit9) > 20) 
		{
			MessageBox("��ϵ�˵绰3���ݴ���","", MB_ICONERROR);
			return;
		}

		break;
	case FILE_DF01EF07:
		if (!isErase(m_edit1))
		{
		if ((m_edit1.GetLength() > 2) ||(CheckDec(m_edit1) != 0))
		{
			MessageBox("�Ļ��̶ȴ������ݴ���","", MB_ICONERROR);
			return;
		}}
		if (!isErase(m_edit2))
		{
		if ((m_edit2.GetLength() > 2) ||(CheckDec(m_edit2) != 0))
		{
			MessageBox("����״���������ݴ���","", MB_ICONERROR);
			return;
		}}
		if (!isErase(m_edit3))
		{
			if (strlen(m_edit3) > 3) 
			{
				MessageBox("ְҵ�������ݴ���","", MB_ICONERROR);
				return;
			}
		}
		break;
	case FILE_DF01EF08:
		if (!isErase(m_edit1))
		{
		if ((m_edit1.GetLength() > 2) ||(CheckDec(m_edit1) != 0))
		{
			MessageBox("֤��������ݴ���","", MB_ICONERROR);
			return;
		}}
		if (!isErase(m_edit2))
		{
		if (strlen(m_edit2) > 18) 
		{
			MessageBox("֤���������ݴ���","", MB_ICONERROR);
			return;
		}}
		if (strlen(m_edit3) > 17) 
		{
			MessageBox("��������������ݴ���","", MB_ICONERROR);
			return;
		}
		if (strlen(m_edit4) > 18) 
		{
			MessageBox("��ũ��֤�����ݴ���","", MB_ICONERROR);
			return;
		}

		break;
	case FILE_DF02EF05:		
		break;
	case FILE_DF02EF06:
		if (!isErase(m_edit1))
		{
		if ((m_edit1.GetLength() != 2) ||(CheckHex(m_edit1) != 0))
		{
			MessageBox("���񲡱�־���ݴ���","", MB_ICONERROR);
			return;
		}}
		break;	
	case FILE_DF02EF07:
		if (strlen(m_edit1) > 20) 
		{
			MessageBox("���������������ݴ���","", MB_ICONERROR);
			return;
		}
		if (strlen(m_edit2) > 100) 
		{
			MessageBox("������Ӧ���ݴ���","", MB_ICONERROR);
			return;
		}

		break;
	case FILE_DF02EF08:
		if (strlen(m_edit1) > 20) 
		{
			MessageBox("���߽����������ݴ���","", MB_ICONERROR);
			return;
		}
		if ((m_edit2.GetLength() > 8) ||(CheckDec(m_edit2) != 0))
		{
			MessageBox("���߽���ʱ�����ݴ���","", MB_ICONERROR);
			return;
		}
		break;
	default:
		break;
	}
	_CancelPressed = false;
	CDialog::OnOK();
}

void InputDialog::Setview(int type)
{
	_formType = type;

	switch (type)
	{
	case FILE_DDF1EF05:
		m_static1 = "�����  an01";
		m_static2 = "�淶�汾 an04";
		m_static3 = "������������ an30";
		m_static4 = "������������ cn11";
		m_static5 = "��������֤�� b180";
		m_static6 = "����ʱ�� cn4";
		
		m_static7 = "���� an18";
		m_static8 = "��ȫ�� an3";
		m_static9 = "�������к� an10";
		m_static10 = "Ӧ�ó��д��� cn3";
		break;
	case FILE_DDF1EF06:
		m_static1 = "����  an30";
		m_static2 = "�Ա� b1";
		m_static3 = "������� cn1";
		m_static4 = "�������� cn4";
		m_static5 = "�������֤���� an18";
		break;
	case FILE_DDF1EF08:
		m_static1 = "����Ч��  cn4";
		m_static2 = "���˵绰1 an20";
		m_static3 = "���˵绰2 an20";
		m_static4 = "ҽ�Ʒ���֧����ʽ1 cn1";
		m_static5 = "ҽ�Ʒ���֧����ʽ2 cn1";
		m_static6 = "ҽ�Ʒ���֧����ʽ3 cn1";		
		break;
	case FILE_DF01EF05:
		m_static1 = "��ַ���1 cn1";
		m_static2 = "��ַ1	   an100";
		m_static3 = "��ַ���2 cn1";
		m_static4 = "��ַ2	   an100";
		break;
	case FILE_DF01EF06:
		m_static1 = "��ϵ������1 an30";
		m_static2 = "��ϵ�˹�ϵ1 cn1";
		m_static3 = "��ϵ�˵绰1 an20";
		m_static4 = "��ϵ������2 an30";
		m_static5 = "��ϵ�˹�ϵ2 cn1";
		m_static6 = "��ϵ�˵绰2 an20";
		m_static7 = "��ϵ������3 an30";
		m_static8 = "��ϵ�˹�ϵ3 cn1";
		m_static9 = "��ϵ�˵绰3 an20";
		break;
	case FILE_DF01EF07:
		m_static1 = "�Ļ��̶ȴ��� cn1";
		m_static2 = "����״������ cn1";
		m_static3 = "ְҵ����	  an3";
		break;
	case FILE_DF01EF08:
		m_static1 = "֤����� cn1";
		m_static2 = "֤������ an18";
		m_static3 = "����������� an17";
		m_static4 = "��ũ��֤��   an18";
		break;
	case FILE_DF02EF05:		
		break;
	case FILE_DF02EF06:
		m_static1 = "���񲡱�־ b1";
		break;	
	case FILE_DF02EF07:
		m_static1 = "������������ an20";
		m_static2 = "������Ӧ	  an100";
		break;
	case FILE_DF02EF08:
		m_static1 = "���߽������� an20";
		m_static2 = "���߽���ʱ�� cn4";

		break;
	default:
		m_static1 = "�쳣����";
		break;
	}
	//UpdateData(TRUE);
}
