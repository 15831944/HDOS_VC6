// HD_ZTHM1Interface.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "HD_ZTHM1Interface.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

int __stdcall HD_WriteM1(char *Key,char *Name,char *Sex,char *IDNo,char *Born,char *CardNo,char *MakeCDT,char *pErr)
{
	char XM[40]={0};
	char XB[40]={0};
	char MZ[40]={0};
	char CSRQ[40]={0};
	char SFZH[40]={0};
	char FKSJ[40]={0};
	char KYXQ[40]={0};
	char KH[40]={0};
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
	//д�������Ա�
	strcpy(XM,Name);
	ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,1,key);
	if(ret!=0)
	{
		ICC_Reader_Close(ReaderHandle);
		sprintf(pErr,"(��ʱ��)��֤����1����ʧ��,�������:%d",ret);
		return 1;
	}
	//::MessageBox(NULL,"HAHA",NULL,MB_OK);
	if(strlen(Name)>0)
	{
		ret=PICC_Reader_Write(ReaderHandle,4,(unsigned char*)XM);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(��ʱ��)д����1ʧ��,�������:%d",ret);
			return 1;
		}
		ret=PICC_Reader_Write(ReaderHandle,5,(unsigned char*)XM+16);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(��ʱ��)д����2ʧ��,�������:%d",ret);
			return 1;
		}
	}
	if(strlen(Sex)>0)
	{
		strcpy(XB,Sex+1);
		ret=PICC_Reader_Write(ReaderHandle,6,(unsigned char*)XB);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(��ʱ��)д�Ա�ʧ��,�������:%d",ret);
			return 1;
		}
	}
	//д���֤�źͳ�������
	strcpy(SFZH,IDNo);
	ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,2,key);
	if(ret!=0)
	{
		ICC_Reader_Close(ReaderHandle);
		sprintf(pErr,"(��ʱ��)��֤����2����ʧ��,�������:%d",ret);
		return 1;
	}
	if(strlen(IDNo)>0)
	{
		ret=PICC_Reader_Write(ReaderHandle,8,(unsigned char*)SFZH);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(��ʱ��)д���֤��1ʧ��,�������:%d",ret);
			return 1;
		}
		ret=PICC_Reader_Write(ReaderHandle,9,(unsigned char*)SFZH+16);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(��ʱ��)д���֤��2ʧ��,�������:%d",ret);
			return 1;
		}
	}
	if(strlen(Born)>0)
	{
		StrToHex((unsigned char *)Born,8,(unsigned char *)CSRQ);
		ret=PICC_Reader_Write(ReaderHandle,10,(unsigned char*)CSRQ);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(��ʱ��)д��������,�������:%d",ret);
			return 1;
		}
	}
	//д��ʱ���źͰ쿨����
	ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,3,key);
	if(ret!=0)
	{
		ICC_Reader_Close(ReaderHandle);
		sprintf(pErr,"(��ʱ��)��֤����3����ʧ��,�������:%d",ret);
		return 1;
	}
	if(strlen(CardNo)>0)
	{
		strcpy(KH,"0000000000000");
		strcat(KH,CardNo);
		char temp[50]={0};
		StrToHex((unsigned char *)KH,32,(unsigned char *)temp);
		ret=PICC_Reader_Write(ReaderHandle,12,(unsigned char*)temp);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(��ʱ��)д��ʱ����ʧ��,�������:%d",ret);
			return 1;
		}
	}
	if(strlen(MakeCDT)>0)
	{
		StrToHex((unsigned char *)MakeCDT,8,(unsigned char *)FKSJ);
		ret=PICC_Reader_Write(ReaderHandle,13,(unsigned char*)FKSJ);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(��ʱ��)д��ʱ���쿨����,�������:%d",ret);
			return 1;
		}
	}
	ICC_Reader_Close(ReaderHandle);
	return 0;
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