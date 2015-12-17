// HD_ZTHReadM1Interface.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include  "HD_ZTHReadM1Interface.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

int __stdcall HD_ReadM1(char *Key,char *Addr,char *DataOut,char *pErr)
{
	//��ʱ��
	long ReaderHandle=ICC_Reader_Open("USB1");
	if(ReaderHandle<=0)
	{
		sprintf(pErr,"(��ʱ��)�򿪶˿�ʧ��,�������:%d",ReaderHandle);
		return 1;
	}
	int ret=PICC_Reader_Request(ReaderHandle);
	if(ret!=0)
	{
		ICC_Reader_Close(ReaderHandle);
		sprintf(pErr,"(��ʱ��)����Ƭʧ��,�������:%d",ret);
		return 1;
	}
	unsigned char uid[50]={0};
	ret=PICC_Reader_anticoll(ReaderHandle,uid);
	if(ret!=0)
	{
		ICC_Reader_Close(ReaderHandle);
		sprintf(pErr,"(��ʱ��)����ײʧ��,�������:%d",ret);
		return 1;
	}
	ret=PICC_Reader_Select(ReaderHandle,0x41);
	if(ret!=0)
	{
		ICC_Reader_Close(ReaderHandle);
		sprintf(pErr,"(��ʱ��)ѡ��ʧ��,�������:%d",ret);
		return 1;
	}
	unsigned char key[10]={0};
	StrToHex((unsigned char*)Key,12,key);//���ַ�������תΪ16������
	int iAddr=atoi(Addr);
	int sq=iAddr/4;
	ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,sq,key);
	if(ret!=0)
	{
		ICC_Reader_Close(ReaderHandle);
		sprintf(pErr,"(��ʱ��)��֤����%d����ʧ��,�������:%d",sq,ret);
		return 1;
	}
	unsigned char DataHex[100]={0};
	ret=PICC_Reader_ReadHEX(ReaderHandle,iAddr,DataHex);
	if(ret!=0)
	{
		ICC_Reader_Close(ReaderHandle);
		sprintf(pErr,"(��ʱ��)��%d��ʧ��,�������:%d",iAddr,ret);
		return 1;
	}
	strcpy(DataOut,(char *)DataHex);
	ICC_Reader_Close(ReaderHandle);
	return 0;
}