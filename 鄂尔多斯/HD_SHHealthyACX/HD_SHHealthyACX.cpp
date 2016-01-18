// HD_SHHealthyACX.cpp : Implementation of CHD_SHHealthyACXApp and DLL registration.

#include "stdafx.h"
#include "HD_SHHealthyACX.h"
#include "ComCat.h"  
#include "ObjSafe.h"  

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CHD_SHHealthyACXApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xf1a172c0, 0x7206, 0x4cb0, { 0xbb, 0x87, 0x2e, 0xb7, 0xd, 0x5c, 0x69, 0xe1 } };
const GUID CDECL CLSID_SafeItem =  
        { 0xD4C825DB, 0x2ABF, 0x4DCC, { 0xb4, 0x4c, 0xbb, 0x66, 0xda, 0x69, 0xfb, 0x03 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXApp::InitInstance - DLL initialization

BOOL CHD_SHHealthyACXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXApp::ExitInstance - DLL termination

int CHD_SHHealthyACXApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}

//����Component Categories�еĳ�ʼ����ȫ�ͽű���ȫ��
HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription)
{
	ICatRegister *pcr = NULL ;
    HRESULT hr = S_OK ;
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
            NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
    if (FAILED(hr))
        return hr;

    // ȷ��HKCR\Component Categories\{..catid...}��ֵ��ע��
    CATEGORYINFO catinfo;
    catinfo.catid = catid;
    catinfo.lcid = 0x0409; // english
    //size_t len;
    // ȷ����������̫����
	// ֻ���ƿ�ʼ��127���ַ���
	// StringCchLength�ĵڶ���������ʾ������catDescription������ַ�����
    // ������������ʾ�ַ����ĳ���
    //hr = StringCchLength(catDescription, STRSAFE_MAX_CCH, &len);
	int len = wcslen(catDescription);
    if (SUCCEEDED(hr))
	{
		if (len>127)
		{
			len = 127;
		}
	}   
    else
	{
		// TODO: Write an error handler;
	}

	wcsncpy(catinfo.szDescription, catDescription, len);
    //hr = StringCchCopy(catinfo.szDescription, len + 1, catDescription);
    // ����ַ���������.
    //catinfo.szDescription[len + 1] = '\0';
	catinfo.szDescription[len] = '/0';

    hr = pcr->RegisterCategories(1, &catinfo);
    pcr->Release();
    return hr;
}

//��CLSID�д�����Component Categories�г�ʼ����ȫ�ͽű���ȫ�������Ӧ��implemented Categories��
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
	// ע�����������Ϣ
    ICatRegister *pcr = NULL ;
    HRESULT hr = S_OK ;
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
                NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);

    if (SUCCEEDED(hr))
    {
       CATID rgcatid[1] ;
       rgcatid[0] = catid;
       hr = pcr->RegisterClassImplCategories(clsid, 1, rgcatid);
    }

    if (pcr != NULL)
        pcr->Release();
            
    return hr;

}

//ע����CLSID�е���Ӧimplemented Categories�һ���ò�������Ϊ�����������Ҳ���õ������
HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
	ICatRegister *pcr = NULL ;
    HRESULT hr = S_OK ;
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
            NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);

    if (SUCCEEDED(hr))
    {
       CATID rgcatid[1] ;
       rgcatid[0] = catid;
       hr = pcr->UnRegisterClassImplCategories(clsid, 1, rgcatid);
    }

    if (pcr != NULL)
        pcr->Release();
    return hr;
}
/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);
	//�����ű���ȫ�����䡱���CLSID��
	HRESULT hr = CreateComponentCategory(CATID_SafeForScripting, L"Controls safely scriptable!");
	if (FAILED(hr))
		return hr;

	//������ʼ����ȫ�����䡱���CLSID��
	hr = CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data!");
	if (FAILED(hr))
		return hr;

	//���ÿؼ�CLSID�в�����Ľű���ȫ��롰���䡱���еĽű���ȫ���Ӧ
	hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);
	if (FAILED(hr))
		return hr;

	//���ÿؼ�CLSID�в�����ĳ�ʼ����ȫ��롰���䡱���еĳ�ʼ����ȫ���Ӧ
	hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);
	if (FAILED(hr))
		return hr;
	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	// ɾ���ؼ���ʼ����ȫ���.
	HRESULT hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);
	if (FAILED(hr))
		return hr;

	// ɾ���ؼ��ű���ȫ���
	hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);
	if (FAILED(hr))
		return hr;

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);
	return NOERROR;
}
