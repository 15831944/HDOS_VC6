// HDCardDevDemo.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "HDCardDevDemo.h"
#include "HDCardDevDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHDCardDevDemoApp

BEGIN_MESSAGE_MAP(CHDCardDevDemoApp, CWinApp)
END_MESSAGE_MAP()


// CHDCardDevDemoApp ����
CHDCardDevDemoApp::CHDCardDevDemoApp()
	: CWinApp()
{
	// TODO: �ڴ˴����ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CHDCardDevDemoApp ����
CHDCardDevDemoApp theApp;

// CHDCardDevDemoApp ��ʼ��

BOOL CHDCardDevDemoApp::InitInstance()
{

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CHDCardDevDemoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô�����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}