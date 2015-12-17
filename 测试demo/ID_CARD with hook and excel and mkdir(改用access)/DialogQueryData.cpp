// DialogQueryData.cpp : implementation file
//

#include "stdafx.h"
#include "ID_CARD.h"
#include "DialogQueryData.h"
#include "excel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogQueryData dialog


CDialogQueryData::CDialogQueryData(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogQueryData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogQueryData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogQueryData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogQueryData)
	DDX_Control(pDX, IDC_COMBO_EXPRESSION, m_combo_exp);
	DDX_Control(pDX, IDC_LIST_DATA, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogQueryData, CDialog)
	//{{AFX_MSG_MAP(CDialogQueryData)
	ON_BN_CLICKED(IDC_BTN_SHOWALL, OnBtnShowall)
	ON_BN_CLICKED(IDC_BTN_QUERY, OnBtnQuery)
	ON_BN_CLICKED(IDC_BTN_EXPORT, OnBtnExport)
	ON_BN_CLICKED(IDC_BTN_BACKUP, OnBtnBackup)
	ON_BN_CLICKED(IDC_BTN_OPENBACKUP, OnBtnOpenbackup)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogQueryData message handlers


BOOL CDialogQueryData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	this->CenterWindow();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, "����", LVCFMT_CENTER, 60);
	m_list.InsertColumn(1, "�Ա�", LVCFMT_CENTER, 40);
	m_list.InsertColumn(2, "����", LVCFMT_CENTER, 40);
	m_list.InsertColumn(3, "��������", LVCFMT_CENTER, 90);
	m_list.InsertColumn(4, "��ͥסַ", LVCFMT_CENTER, 220);
	m_list.InsertColumn(5, "���֤����", LVCFMT_CENTER,130);
	m_list.InsertColumn(6, "ǩ������", LVCFMT_CENTER, 170);
	m_list.InsertColumn(7, "��Ч����", LVCFMT_CENTER, 90);
	m_list.InsertColumn(8, "��Ч��ֹ", LVCFMT_CENTER, 90);
	_variant_t name,sex,nation,born,addr,cardno,issue,yxq,jiezhi;
	//m_pRecordset->Open("SELECT * FROM DBID WHERE ����='������'",m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	while(!m_pRecordset->adoEOF)
	{
		name = m_pRecordset->GetCollect(_variant_t((long)1));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		sex = m_pRecordset->GetCollect(_variant_t((long)2));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		nation = m_pRecordset->GetCollect(_variant_t((long)3));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		born = m_pRecordset->GetCollect(_variant_t((long)4));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		addr = m_pRecordset->GetCollect(_variant_t((long)5));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		cardno = m_pRecordset->GetCollect(_variant_t((long)6));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		issue = m_pRecordset->GetCollect(_variant_t((long)7));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		yxq = m_pRecordset->GetCollect(_variant_t((long)8));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		jiezhi = m_pRecordset->GetCollect(_variant_t((long)9));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		if(name.vt != VT_NULL && sex.vt != VT_NULL && nation.vt != VT_NULL && 
			born.vt != VT_NULL&& addr.vt != VT_NULL&& jiezhi.vt != VT_NULL&& 
			cardno.vt != VT_NULL&& issue.vt != VT_NULL	&& yxq.vt != VT_NULL)
		{
			int n=m_list.GetItemCount();
			m_list.InsertItem(n,(LPCTSTR)(_bstr_t)name,0);
			m_list.SetItemText(n,1,(LPCTSTR)(_bstr_t)sex);
			m_list.SetItemText(n,2,(LPCTSTR)(_bstr_t)nation);
			m_list.SetItemText(n,3,(LPCTSTR)(_bstr_t)born);
			m_list.SetItemText(n,4,(LPCTSTR)(_bstr_t)addr);
			m_list.SetItemText(n,5,(LPCTSTR)(_bstr_t)cardno);
			m_list.SetItemText(n,6,(LPCTSTR)(_bstr_t)issue);
			m_list.SetItemText(n,7,(LPCTSTR)(_bstr_t)yxq);
			m_list.SetItemText(n,8,(LPCTSTR)(_bstr_t)jiezhi);
		}
		m_pRecordset->MoveNext();///�Ƶ���һ����¼
	}
	isOpenBackup=false;
//	if (m_pRecordset->GetState() == adStateOpen)
//	{
//		m_pRecordset->Close();
//	}
//	if (m_pRecordset)
//	{
//		m_pRecordset.Release();
//		m_pRecordset = NULL;
//	}
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogQueryData::OnBtnShowall() 
{
	if(isOpenBackup)
	{
		if (m_pRecordset_backup->GetState() == adStateOpen)
		{
			m_pRecordset_backup->Close();
		}
		if(m_pConnection_backup->GetState()==adStateOpen) 
			m_pConnection_backup->Close(); ///����Ѿ�����������ر���
		if (m_pConnection_backup)
		{
			m_pConnection_backup.Release();
			m_pConnection_backup = NULL;
		}
		isOpenBackup=false;
	}
	GetDlgItem(IDC_BTN_BACKUP)->EnableWindow(TRUE);//���ð�ť����
	m_list.DeleteAllItems();
	m_pRecordset->MoveFirst();
	_variant_t name,sex,nation,born,addr,cardno,issue,yxq,jiezhi;
	while(!m_pRecordset->adoEOF)
	{
		name = m_pRecordset->GetCollect(_variant_t((long)1));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		sex = m_pRecordset->GetCollect(_variant_t((long)2));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		nation = m_pRecordset->GetCollect(_variant_t((long)3));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		born = m_pRecordset->GetCollect(_variant_t((long)4));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		addr = m_pRecordset->GetCollect(_variant_t((long)5));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		cardno = m_pRecordset->GetCollect(_variant_t((long)6));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		issue = m_pRecordset->GetCollect(_variant_t((long)7));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		yxq = m_pRecordset->GetCollect(_variant_t((long)8));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		jiezhi = m_pRecordset->GetCollect(_variant_t((long)9));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		///��DEBUG��ʽ�µ�OUTPUT���������¼���еļ�¼
		if(name.vt != VT_NULL && sex.vt != VT_NULL && nation.vt != VT_NULL && 
			born.vt != VT_NULL&& addr.vt != VT_NULL&& jiezhi.vt != VT_NULL&& 
			cardno.vt != VT_NULL&& issue.vt != VT_NULL	&& yxq.vt != VT_NULL)
		{
			int n=m_list.GetItemCount();
			m_list.InsertItem(n,(LPCTSTR)(_bstr_t)name,0);
			m_list.SetItemText(n,1,(LPCTSTR)(_bstr_t)sex);
			m_list.SetItemText(n,2,(LPCTSTR)(_bstr_t)nation);
			m_list.SetItemText(n,3,(LPCTSTR)(_bstr_t)born);
			m_list.SetItemText(n,4,(LPCTSTR)(_bstr_t)addr);
			m_list.SetItemText(n,5,(LPCTSTR)(_bstr_t)cardno);
			m_list.SetItemText(n,6,(LPCTSTR)(_bstr_t)issue);
			m_list.SetItemText(n,7,(LPCTSTR)(_bstr_t)yxq);
			m_list.SetItemText(n,8,(LPCTSTR)(_bstr_t)jiezhi);
		}
		m_pRecordset->MoveNext();///�Ƶ���һ����¼
	}
}

void CDialogQueryData::OnBtnQuery() 
{
	int i=m_combo_exp.GetCurSel();
	if(i<0)
	{
		this->MessageBox("��ѡ���ѯ����!");
		return;
	}
	m_list.DeleteAllItems();
	char sql[500]={0};
	CString sExp;
	GetDlgItemText(IDC_EDIT_EXPRESSION,sExp);
	_RecordsetPtr m_pRecordset_q;
	switch(i)
	{
	case 4:
		sprintf(sql,"select * from DBID where ����='%s'",sExp.GetBuffer(0));
		break;
	case 3:
		sprintf(sql,"select * from DBID where �Ա�='%s'",sExp.GetBuffer(0));
		break;
	case 0:
		sprintf(sql,"select * from DBID where ����='%s'",sExp.GetBuffer(0));
		break;
	case 2:
		sprintf(sql,"select * from DBID where ���֤����='%s'",sExp.GetBuffer(0));
		break;
	case 1:
		sprintf(sql,"select * from DBID where ǩ������='%s'",sExp.GetBuffer(0));
		break;
	}
	sExp.ReleaseBuffer();
	if(isOpenBackup)
	{
		m_pRecordset_q=m_pConnection_backup->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}else
	{
		m_pRecordset_q=m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}
	_variant_t name,sex,nation,born,addr,cardno,issue,yxq,jiezhi;
	while(!m_pRecordset_q->adoEOF)
	{
		name = m_pRecordset_q->GetCollect(_variant_t((long)1));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		sex = m_pRecordset_q->GetCollect(_variant_t((long)2));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		nation = m_pRecordset_q->GetCollect(_variant_t((long)3));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		born = m_pRecordset_q->GetCollect(_variant_t((long)4));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		addr = m_pRecordset_q->GetCollect(_variant_t((long)5));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		cardno = m_pRecordset_q->GetCollect(_variant_t((long)6));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		issue = m_pRecordset_q->GetCollect(_variant_t((long)7));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		yxq = m_pRecordset_q->GetCollect(_variant_t((long)8));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		jiezhi = m_pRecordset_q->GetCollect(_variant_t((long)9));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		if(name.vt != VT_NULL && sex.vt != VT_NULL && nation.vt != VT_NULL && 
			born.vt != VT_NULL&& addr.vt != VT_NULL&& jiezhi.vt != VT_NULL&& 
			cardno.vt != VT_NULL&& issue.vt != VT_NULL	&& yxq.vt != VT_NULL)
		{
			int n=m_list.GetItemCount();
			m_list.InsertItem(n,(LPCTSTR)(_bstr_t)name,0);
			m_list.SetItemText(n,1,(LPCTSTR)(_bstr_t)sex);
			m_list.SetItemText(n,2,(LPCTSTR)(_bstr_t)nation);
			m_list.SetItemText(n,3,(LPCTSTR)(_bstr_t)born);
			m_list.SetItemText(n,4,(LPCTSTR)(_bstr_t)addr);
			m_list.SetItemText(n,5,(LPCTSTR)(_bstr_t)cardno);
			m_list.SetItemText(n,6,(LPCTSTR)(_bstr_t)issue);
			m_list.SetItemText(n,7,(LPCTSTR)(_bstr_t)yxq);
			m_list.SetItemText(n,8,(LPCTSTR)(_bstr_t)jiezhi);
		}
		m_pRecordset_q->MoveNext();///�Ƶ���һ����¼
	}
	if (m_pRecordset_q->GetState() == adStateOpen)
	{
		m_pRecordset_q->Close();
	}
	if (m_pRecordset_q)
	{
		m_pRecordset_q.Release();
		m_pRecordset_q = NULL;
	}
}

void CDialogQueryData::OnBtnExport() 
{
	BOOL isOpen = FALSE;		//�Ƿ��(����Ϊ����)
	CString defaultDir = L"E:\\FileTest";	//Ĭ�ϴ򿪵��ļ�·��
	CString fileName = L"test.xls";			//Ĭ�ϴ򿪵��ļ���
	CTime tm; 
	tm=tm.GetCurrentTime();
	fileName=tm.Format("%Y-%m-%d");
	CString filter = L"�ļ� (*.xls)|*.xls||";	//�ļ����ǵ�����
	CFileDialog openFileDlg(isOpen, NULL, fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\" + fileName;
	if(result == IDOK) 
	{
		filePath = openFileDlg.GetPathName();
		//this->MessageBox(filePath);
	}else
		return;
	//дexcel
	COleVariant VOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	CString sValue = "";
	_Application objApp;
	_Workbook objBook;
	Workbooks objBooks;
	Worksheets objSheets;
	_Worksheet objSheet;
	Range objRange, usedRange;
	objApp.SetAlertBeforeOverwriting(FALSE);
	objApp.SetDisplayAlerts(FALSE);
	if (!objApp.CreateDispatch("Excel.Application"))
	{
			::AfxMessageBox("ȷ���Ƿ�װ��Excel");
			return;
	}
	objBooks = objApp.GetWorkbooks();
	try
	{
		objBook = objBooks.Add(_variant_t(filePath));
	}
	catch (CException* e)
	{
		objBook = objBooks.Add(vtMissing);//�Ҳ������½�һ��
	}
	objSheets = objBook.GetWorksheets();
	objSheet = objSheets.GetItem(COleVariant((short)1));
	objRange.AttachDispatch(objSheet.GetCells(), true);
	/////////////////////////////////
	//���ñ�ͷ
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(1)),COleVariant("����"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(2)),COleVariant("�Ա�"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(3)),COleVariant("����"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(4)),COleVariant("��������"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(5)),COleVariant("��ͥסַ"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(6)),COleVariant("���֤����"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(7)),COleVariant("ǩ������"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(8)),COleVariant("��Ч����"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(9)),COleVariant("��Ч��ֹ"));
	int SelectedCount=m_list.GetSelectedCount();
	if(0==SelectedCount)
	{
		for(int i=0;i<m_list.GetItemCount();i++)
		{
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(1)),COleVariant(m_list.GetItemText(i,0)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(2)),COleVariant(m_list.GetItemText(i,1)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(3)),COleVariant(m_list.GetItemText(i,2)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(4)),COleVariant(m_list.GetItemText(i,3)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(5)),COleVariant(m_list.GetItemText(i,4)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(6)),COleVariant(m_list.GetItemText(i,5)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(7)),COleVariant(m_list.GetItemText(i,6)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(8)),COleVariant(m_list.GetItemText(i,7)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(9)),COleVariant(m_list.GetItemText(i,8)));
		}
	}else
	{
		POSITION pos=m_list.GetFirstSelectedItemPosition(); 
		int nId=0,count=0;
		while(pos)
		{
			nId=(int)m_list.GetNextSelectedItem(pos); 
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(1)),COleVariant(m_list.GetItemText(nId,0)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(2)),COleVariant(m_list.GetItemText(nId,1)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(3)),COleVariant(m_list.GetItemText(nId,2)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(4)),COleVariant(m_list.GetItemText(nId,3)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(5)),COleVariant(m_list.GetItemText(nId,4)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(6)),COleVariant(m_list.GetItemText(nId,5)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(7)),COleVariant(m_list.GetItemText(nId,6)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(8)),COleVariant(m_list.GetItemText(nId,7)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(9)),COleVariant(m_list.GetItemText(nId,8)));
			count++;
		}
	}
	objRange.AttachDispatch(objSheet.GetColumns(),true);
	//�����е��п�  
	Range cols;
	cols.AttachDispatch(objRange.GetItem(COleVariant((long)4),VOptional).pdispVal,TRUE);
	//cols.AttachDispatch(objSheet.GetUsedRange());
	//cols=objSheet.GetRange(COleVariant("A1"),COleVariant("A1"));
	cols.SetColumnWidth(COleVariant((long)15)); //�����п�
	cols.SetHorizontalAlignment(_variant_t((long)-4131)); //�����
	cols.AttachDispatch(objRange.GetItem(COleVariant((long)5),VOptional).pdispVal,TRUE);
	cols.SetColumnWidth(COleVariant((long)25)); //�����п�
	cols.AttachDispatch(objRange.GetItem(COleVariant((long)6),VOptional).pdispVal,TRUE);
	cols.SetColumnWidth(COleVariant((long)30)); //�����п�
	cols.AttachDispatch(objRange.GetItem(COleVariant((long)7),VOptional).pdispVal,TRUE);
	cols.SetColumnWidth(COleVariant((long)30)); //�����п�
	cols.AttachDispatch(objRange.GetItem(COleVariant((long)8),VOptional).pdispVal,TRUE);
	cols.SetColumnWidth(COleVariant((long)15)); //�����п�
	cols.SetHorizontalAlignment(_variant_t((long)-4131)); //�����
	cols.AttachDispatch(objRange.GetItem(COleVariant((long)9),VOptional).pdispVal,TRUE);
	cols.SetColumnWidth(COleVariant((long)15)); //�����п�
	cols.SetHorizontalAlignment(_variant_t((long)-4131)); //�����
	//cols.SetWrapText((_variant_t)(short)TRUE);
				
	//// �����ļ�
	//objBook.Save();
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	//objBook.SetSaved(TRUE);
	objBook.SaveAs(COleVariant(filePath.GetBuffer(0)),_variant_t((long)18),covOptional,covOptional,
						covOptional,covOptional,(long)0,covOptional,covOptional,covOptional,covOptional,covOptional);
	objRange.ReleaseDispatch();
	//// �ر��ļ�
	objRange.Clear();
	objBook.Close(COleVariant((short)FALSE),VOptional,VOptional);
	objBooks.Close();
	objApp.Quit();	
	filePath.ReleaseBuffer();
	this->MessageBox("�������!");
}

void CDialogQueryData::OnBtnBackup() 
{
	BOOL isOpen = FALSE;		//�Ƿ��(����Ϊ����)
	CString defaultDir = L"E:\\FileTest";	//Ĭ�ϴ򿪵��ļ�·��
	CString fileName = L"test.xls";			//Ĭ�ϴ򿪵��ļ���
	CTime tm; 
	tm=tm.GetCurrentTime();
	fileName=tm.Format("%Y-%m-%d.mdb");
	CString filter = L"�ļ� (*.mdb)|*.mdb||";	//�ļ����ǵ�����
	CFileDialog openFileDlg(isOpen, NULL, fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\" + fileName;
	if(result == IDOK) 
	{
		filePath = openFileDlg.GetPathName();
		//this->MessageBox(filePath);
	}else
		return;
	if(CopyFile("HD_IDDB.mdb",filePath,FALSE)) //����
		AfxMessageBox("���ݿⱸ�ݳɹ�!"); 
	else 
	{
		int i=GetLastError();
		AfxMessageBox("���ݿⱸ��ʧ��!");  
	}

}

void CDialogQueryData::OnBtnOpenbackup() 
{
	//���ж��Ƿ��Ѿ��������ݿ�
	if(isOpenBackup)
	{
		//this->MessageBox("�ر�!");
		if (m_pRecordset_backup->GetState() == adStateOpen)
		{
			m_pRecordset_backup->Close();
		}
		if(m_pConnection_backup->GetState()==adStateOpen) 
			m_pConnection_backup->Close(); ///����Ѿ�����������ر���
		if (m_pConnection_backup)
		{
			m_pConnection_backup.Release();
			m_pConnection_backup = NULL;
		}
	}
	////////////////
	BOOL isOpen = TRUE;		//�Ƿ��(����Ϊ����)
	CString filter = L"�ļ� (*.mdb)|*.mdb||";	//�ļ����ǵ�����
	CFileDialog openFileDlg(isOpen, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath;
	if(result == IDOK) 
	{
		filePath = openFileDlg.GetPathName();
		//this->MessageBox(filePath);
	}else
	{
		isOpenBackup=false;
		return;
	}
	////////////�������ݿ�//////////////
	HRESULT hr;
	try
	{
		hr = m_pConnection_backup.CreateInstance("ADODB.Connection");///����Connection����
		if(SUCCEEDED(hr))
		{
			char sOpen[200]={0};
			sprintf(sOpen,"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s",filePath);
			m_pConnection_backup->ConnectionTimeout = 5;
			hr = m_pConnection_backup->Open(sOpen,"","",adModeUnknown);///�������ݿ�
			//����һ���������ִ��е�Provider�����ACCESS2000�����ģ�����ACCESS97,��Ҫ��Ϊ:Provider=Microsoft.Jet.OLEDB.3.51;  }
		}
	}
	catch(_com_error e)///��׽�쳣
	{
		CString errormessage;
		errormessage.Format("�������ݿ�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///��ʾ������Ϣ
		return ;
	} 
	//�򿪼�¼��Log
	//m_pRecordset=m_pConnection->Execute("INSERT INTO DBID(����,�Ա�,����,��������,��ͥסַ,���֤����,ǩ������,��Ч����,��Ч��ֹ) VALUES ('2','2','2','2','2','2','2','2','2')",&RecordsAffected,adCmdText);
	//	r.CreateInstance(_uuidof(Recordset));
	m_pRecordset_backup.CreateInstance("ADODB.Recordset");
	CString s="select * from DBID";
	_bstr_t bs=s.AllocSysString();
	m_pRecordset_backup->Open(bs,m_pConnection_backup.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	//��ʾ����
	_variant_t name,sex,nation,born,addr,cardno,issue,yxq,jiezhi;
	m_list.DeleteAllItems();
	while(!m_pRecordset_backup->adoEOF)
	{
		name = m_pRecordset_backup->GetCollect(_variant_t((long)1));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		sex = m_pRecordset_backup->GetCollect(_variant_t((long)2));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		nation = m_pRecordset_backup->GetCollect(_variant_t((long)3));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		born = m_pRecordset_backup->GetCollect(_variant_t((long)4));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		addr = m_pRecordset_backup->GetCollect(_variant_t((long)5));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		cardno = m_pRecordset_backup->GetCollect(_variant_t((long)6));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		issue = m_pRecordset_backup->GetCollect(_variant_t((long)7));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		yxq = m_pRecordset_backup->GetCollect(_variant_t((long)8));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		jiezhi = m_pRecordset_backup->GetCollect(_variant_t((long)9));//ȡ�õ�1�е�ֵ,��0��ʼ��������Ҳ����ֱ�Ӹ����е����ƣ�
		if(name.vt != VT_NULL && sex.vt != VT_NULL && nation.vt != VT_NULL && 
			born.vt != VT_NULL&& addr.vt != VT_NULL&& jiezhi.vt != VT_NULL&& 
			cardno.vt != VT_NULL&& issue.vt != VT_NULL	&& yxq.vt != VT_NULL)
		{
			int n=m_list.GetItemCount();
			m_list.InsertItem(n,(LPCTSTR)(_bstr_t)name,0);
			m_list.SetItemText(n,1,(LPCTSTR)(_bstr_t)sex);
			m_list.SetItemText(n,2,(LPCTSTR)(_bstr_t)nation);
			m_list.SetItemText(n,3,(LPCTSTR)(_bstr_t)born);
			m_list.SetItemText(n,4,(LPCTSTR)(_bstr_t)addr);
			m_list.SetItemText(n,5,(LPCTSTR)(_bstr_t)cardno);
			m_list.SetItemText(n,6,(LPCTSTR)(_bstr_t)issue);
			m_list.SetItemText(n,7,(LPCTSTR)(_bstr_t)yxq);
			m_list.SetItemText(n,8,(LPCTSTR)(_bstr_t)jiezhi);
		}
		m_pRecordset_backup->MoveNext();///�Ƶ���һ����¼
	}
	//
	isOpenBackup=true;
	GetDlgItem(IDC_BTN_BACKUP)->EnableWindow(FALSE);
}

void CDialogQueryData::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(isOpenBackup)
	{
		if (m_pRecordset_backup->GetState() == adStateOpen)
		{
			m_pRecordset_backup->Close();
		}
		if(m_pConnection_backup->GetState()==adStateOpen) 
			m_pConnection_backup->Close(); ///����Ѿ�����������ر���
		if (m_pConnection_backup)
		{
			m_pConnection_backup.Release();
			m_pConnection_backup = NULL;
		}
	}
	CDialog::OnClose();
}
