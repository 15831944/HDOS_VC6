// ICCInter.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "ICCInter.h"
#include <stdio.h>

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
long hReader=NULL;
int __stdcall IC_GetData(ICC_ENV *iccenv,int datatype,char *data)
{
	char ch='|';
	hReader=ICC_Reader_Open("USB1");
	if(hReader<=0)//�豸��ʧ�ܷ���
	{
		char *p="Open device failure";
		memcpy(data,p,strlen(p));
		return 1;
	}
	unsigned char Response[50]={0};
	long rt=0;
	//��λ
	rt=ICC_Reader_PowerOn(hReader,0x01,Response);
	if(rt<=0)
	{
		char *p="PowerOn failure";
		memcpy(data,p,strlen(p));
		return 2;
	}
	//����ѡSSSEָ��
	unsigned char cmd[100]=
		{0x00,0xA4,0x04,0x00,0x0F,
		0x73,0x78,0x31,0x2E,0x73,
		0x68,0x2E,0xC9,0xE7,0xBB,
		0xE1,0xB1,0xA3,0xD5,0xCF};
	unsigned char ResponseAPDU[200]={0};
    int len=ICC_Reader_Application(hReader,0x01,20,cmd,ResponseAPDU);
	if(len<=0)
	{
		char *p="��������-00A4";;
		memcpy(data,p,strlen(p));
		return 3;
	}
	if( (ResponseAPDU[len-2]!=0x61) && (ResponseAPDU[len-2]!=0x90) )
	{
		char *p="��������-00A4";
		memcpy(data,p,strlen(p));
		return 4;
	}
	//ѡSSSE/EF05
	memset(cmd,0,100);
	memset(ResponseAPDU,0,200);
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xEF\x05",7);
	len=ICC_Reader_Application(hReader,0x01,7,cmd,ResponseAPDU);//Xѡ��EF05�ļ�
	if(len<=0 || ResponseAPDU[len-2]!=0x90)
	{
		char *p="00A4-EF05";
		memcpy(data,p,strlen(p));
		return 4;
	}
	//�������ͱ�ʶ
	memset(cmd,0,100);
	memset(ResponseAPDU,0,200);
	memcpy(cmd, "\x00\xB2\x02\x04\x03",5);
	len = ICC_Reader_Application(hReader,0x01,5,cmd,ResponseAPDU);
	if(len<=0 || ResponseAPDU[len-2]!=0x90)
	{
		char *p="00B202";
		memcpy(data,p,strlen(p));
		return 4;
	}
	char CardType[2]={0};
	memcpy(CardType,ResponseAPDU+2,1);//�����ͱ�ʶ
	//��  ����	��ᱣ�Ͽ�����ᱣ�Ͽ�ʶ���� 
	memset(cmd,0,100);
	memset(ResponseAPDU,0,200);
	memcpy(cmd, "\x00\xB2\x01\x04\x12",5);
	len = ICC_Reader_Application(hReader,0x01,5,cmd,ResponseAPDU);
	if(len<=0 || ResponseAPDU[len-2]!=0x90)
	{
		char *p="00B201";
		memcpy(data,p,strlen(p));
		return 4;
	}
	char CardNo[0x10*2+1]={0};
	HexToStr(ResponseAPDU+2,0x10,(unsigned char *)CardNo);
	//memcpy(CardNo,ResponseAPDU+2,0x10);//�񿨺�
	//��  ���˱��	��ᱣ�Ͽ��������
	memset(cmd,0,100);
	memset(ResponseAPDU,0,200);
	memcpy(cmd, "\x00\xB2\x07\x04\x0b",5);
	len = ICC_Reader_Application(hReader,0x01,5,cmd,ResponseAPDU);
	if(len<=0 || ResponseAPDU[len-2]!=0x90)
	{
		char *p="00B207";
		memcpy(data,p,strlen(p));
		return 4;
	}
	char UserNo[0x0a]={0};
	memcpy(UserNo,ResponseAPDU+2,0x09);//����˱��
	//ѡDDF03
	memset(cmd,0,100);
	memset(ResponseAPDU,0,200);
	memcpy(cmd, "\x00\xA4\x01\x00\x02\xDF\x03",7);
	len = ICC_Reader_Application(hReader,0x01,7,cmd,ResponseAPDU);
	if(len<=0 || (ResponseAPDU[len-2]!=0x61 && ResponseAPDU[len-2]!=0x90))
	{
		char *p="00A4-DF03";
		memcpy(data,p,strlen(p));
		return 4;
	}
	//��֤PIN
	memset(cmd,0,100);
	memset(ResponseAPDU,0,200);
	memcpy(cmd, "\x00\x20\x00\x00\x03\x12\x34\x56",8);
	len = ICC_Reader_Application(hReader,0x01,8,cmd,ResponseAPDU);
	if(len<=0 || ResponseAPDU[len-2]!=0x90)
	{
		char *p="VeryfyPin-00200003";
		memcpy(data,p,strlen(p));
		return 4;
	}
	//ѡEF18
	memset(cmd,0,100);
	memset(ResponseAPDU,0,200);
	memcpy(cmd, "\x00\xa4\x00\x00\x02\xEF\x19",7);
	len = ICC_Reader_Application(hReader,0x01,7,cmd,ResponseAPDU);
	if(len<=0 || ResponseAPDU[len-2]!=0x90)
	{
		char *p="00a4-EF18";
		memcpy(data,p,strlen(p));
		return 4;
	}
	//��  �α���������������
	memset(cmd,0,100);
	memset(ResponseAPDU,0,200);
	memcpy(cmd, "\x00\xb2\x79\x00\x29",5);
	len = ICC_Reader_Application(hReader,0x01,5,cmd,ResponseAPDU);
	if(len<=0 || ResponseAPDU[len-2]!=0x90)
	{
		char *p="00b2 75 0005";
		memcpy(data,p,strlen(p));
		return 4;
	}
	char JAdress[0x03*2+1]={0};
	//memcpy(JAdress,ResponseAPDU+9,0x03);//��α���������������
	HexToStr(ResponseAPDU+9,0x03,(unsigned char *)JAdress);
	char DevMN[6]="HD100";                //���������ͺ�
	//��ȡ���������к�
	char DevN[100]={0};                 //�����������к�
	int nDevN=ICC_Reader_GetDeviceCSN(hReader,DevN);
	if(nDevN<=0)
	{
		char *p="Get device number failure";
		memcpy(data,p,strlen(p));
		return 5;
	}
	char DLLVersion[4]={"1.0"};                 //DLL�汾
	char LIBVersion[4]={"1.0"};                 //LIB�汾
	//����SAM��
	memset(Response,0,50);
	rt=ICC_Reader_PowerOn(hReader,0x11,Response); //sam����λ
	if(rt<=0)
	{
		char *p="SAM PowerOn failure";
		memcpy(data,p,strlen(p));
		return 6;
	}
	//ѡSAM����MF
	memset(cmd,0,100);
	memset(ResponseAPDU,0,200);
	memcpy(cmd, "\x00\xA4\x00\x00\x00",5); 
	len = ICC_Reader_Application(hReader,0x11,5,cmd,ResponseAPDU);
	if( (ResponseAPDU[len-2]!=0x61) && (ResponseAPDU[len-2]!=0x90) )
	{
		char *p="SAM-��������-00A4000000";
		memcpy(data,p,strlen(p));
		return 4;
	}
	//ѡSAM����MF/0015
	memset(cmd,0,100);
	memset(ResponseAPDU,0,200);
	memcpy(cmd, "\x00\xA4\x00\x00\x02\x00\x15",7); 
	len = ICC_Reader_Application(hReader,0x11,7,cmd,ResponseAPDU);
	if( (ResponseAPDU[len-2]!=0x61) && (ResponseAPDU[len-2]!=0x90) )
	{
		char *p="SAM-00A4-0015";
		memcpy(data,p,strlen(p));
		return 4;
	}
	//��0015������
	memset(cmd,0,100);
	memset(ResponseAPDU,0,200);
	memcpy(cmd, "\x00\xb0\x00\x00\x0f",5); 
	len = ICC_Reader_Application(hReader,0x11,5,cmd,ResponseAPDU);
	if(len<=0 || ResponseAPDU[len-2]!=0x90)
	{
		char *p="00b000000f";
		memcpy(data,p,strlen(p));
		return 4;
	}
	char SamN[10*2+1]={0};
	//memcpy(SamN,ResponseAPDU+1,10); //��ȡSAM�������к�
	HexToStr(ResponseAPDU+1,10,(unsigned char *)SamN);
	//ѡSAM����MF/0016
	memset(cmd,0,100);
	memset(ResponseAPDU,0,200);
	memcpy(cmd, "\x00\xA4\x00\x00\x02\x00\x16",7); 
	len = ICC_Reader_Application(hReader,0x11,7,cmd,ResponseAPDU);
	if( (ResponseAPDU[len-2]!=0x61) && (ResponseAPDU[len-2]!=0x90) )
	{
		char *p="SAM-00A4-0016";
		memcpy(data,p,strlen(p));
		return 4;
	}
	//��0016������
	memset(cmd,0,100);
	memset(ResponseAPDU,0,200);
	memcpy(cmd, "\x00\xb0\x00\x00\x06",5); 
	len = ICC_Reader_Application(hReader,0x11,5,cmd,ResponseAPDU);
	if(len<=0 || ResponseAPDU[len-2]!=0x90)
	{
		char *p="00b0000006";
		memcpy(data,p,strlen(p));
		return 4;
	}
	char MachineN[6*2+1]={0};
	//memcpy(MachineN,ResponseAPDU,6); //��ȡ�ն˻����
	HexToStr(ResponseAPDU,6,(unsigned char *)MachineN);
	//char CardType[2]={0};              �����ͱ�ʶ
	//char CardNo[0x11]={0};             �񿨺�
	//char UserNo[0x0a]={0};             ���˱��
	//char JAdress[0x04]={0};            ��α���������������
	//char DevMN[6]="HD100";             ���������ͺ�
	//char DevN[100]={0};                �����������к�(ע�ⳤ��)  nDevN
    //char DLLVersion[4]="1.0";          DLL�汾
    //char LIBVersion[4]="1.0";          LIB�汾
	//char SamN[11]={0};      SAM�������к�
	//char MachineN[7]={0};   �˻����
	memcpy(data,CardType,1);
	data[1]=ch;
	int ich=0;
	while(data[ich]!=ch)
		ich++;
	memcpy(data+ich+1,CardNo,0x10*2);
	data[ich+1+0x10*2]=ch;
	ich=ich+1+0x10*2;
	memcpy(data+ich+1,UserNo,0x09);
	data[ich+1+0x09]=ch;
	ich=ich+1+0x09;
	memcpy(data+ich+1,JAdress,0x03*2);
	data[ich+1+0x03*2]=ch;
	ich=ich+1+0x03*2;
	memcpy(data+ich+1,DevMN,5);
	data[ich+1+5]=ch;
	ich=ich+1+5;
	memcpy(data+ich+1,DevN,nDevN);
	data[ich+1+nDevN]=ch;
	ich=ich+1+nDevN;
	memcpy(data+ich+1,DLLVersion,3);
	data[ich+1+3]=ch;
	ich=ich+1+3;
	memcpy(data+ich+1,LIBVersion,3);
	data[ich+1+3]=ch;
	ich=ich+1+3;
	memcpy(data+ich+1,MachineN,6*2);
	data[ich+1+6*2]=',';
	ich=ich+1+6*2;
	memcpy(data+ich+1,SamN,10*2);
	ich=ich+1+10*2;
	return 0;
}

int __stdcall IC_OpenSession(ICC_ENV *iccenv)
{
	return 0;
}
int __stdcall IC_CloseSession(ICC_ENV *iccenv)
{
	return 0;
}
int __stdcall IC_SaveData(ICC_ENV *iccenv, int datatype, unsigned char *data)
{
	return 0;
}
int __stdcall IC_PINVerify(ICC_ENV *iccenv)
{
	return 0;
}
int __stdcall IC_Beep(unsigned char time)
{
//	CString s;
	long hReader=NULL;
	hReader=ICC_Reader_Open("USB1");
	ICC_PosBeep(hReader, 100);//����
	return 0;
}