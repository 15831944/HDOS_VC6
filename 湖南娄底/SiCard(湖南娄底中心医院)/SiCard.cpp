// SiCard.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "SiCard.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
long ReaderHandle=NULL;

int __stdcall IOpenPort(char *Dest)
{
	ReaderHandle=ICC_Reader_Open("USB1"); 
	return ReaderHandle; 
}
int __stdcall IClosePort(char *Dest)
{
	return ICC_Reader_Close(ReaderHandle);
}
void procPassWord(unsigned char *instr, unsigned char *outstr, int len)
{
	int i;
	//1��ʮ�����ƽ��л�λ����
	for(i = 0; i < len; i++)
	{
		outstr[i] = ~((instr[i] & 0xf0)/0x10 + (instr[i] & 0x0f)*0x10) ;
	}
}
int Read_Contact_Card_Info(int cardtype,char *Dest)
{
	switch(cardtype)
	{
	case 1://4442
		{
			char cbuff[30]={0};
			unsigned char data[100]={0};
			int st=ICC_Reader_4442_PowerOn(ReaderHandle,data); //4442���ϵ�
			if(st)
			{
				strcpy(Dest,"4442�ϵ�ʧ��!");
				return st;
			}
			st = ICC_Reader_4442_Read(ReaderHandle,100,14,(unsigned char*)Dest);
			if(st<0)
			{
				strcpy(Dest,"4442��ȡ����ʧ��!");
				ICC_Reader_4442_PowerOff(ReaderHandle);
				return st;
			}
			
			for(int i=0;i<14;i++)
			{
				if(Dest[i]<0x30 || Dest[i]>0x39)
				{
					Dest[i]=0;
					break;
				}
			}
			ICC_Reader_4442_PowerOff(ReaderHandle);
		}
		break;
	case 2://4428
		{
			unsigned char card_buff[100]={0};
			unsigned char chack_buff[100]={0};
			char cbuff[100]={0};
			char a[3]={0};
			
			int st = ICC_Reader_4428_Read(ReaderHandle,50,20,card_buff);
			if(st<0)
			{
				strcpy(Dest,"4428��ȡ����ʧ��-1!");
				ICC_Reader_4428_PowerOff(ReaderHandle);
				return st;
			}
			for (int i =0; i < 20;i++)
			{
				sprintf(a,"%02X",card_buff[i]);
				strcat(cbuff,a);
			}
			bool fflag=true;;
			for(i=0;i<8;i++)//���ǰ8Ϊ��Ч���֣���Ϊ����
			{
				if(cbuff[i]<0x30 || cbuff[i]>0x39)
				{
					fflag=false;//���ǿ���
					break;
				}
			}
			if(!fflag)//���ǿ���
			{
				memset(card_buff,0,100);
				st = ICC_Reader_4428_Read(ReaderHandle,100,14,card_buff);
				if(st<0)
				{
					strcpy(Dest,"4428��ȡ����ʧ��!-2");
					ICC_Reader_4428_PowerOff(ReaderHandle);
					return st;
				}
				bool ffflag=true;
				for(i=0;i<4;i++)//���ǰ4Ϊ��Ч���֣���Ϊ����
				{
					if(card_buff[i]<0x30 || card_buff[i]>0x39)
					{
						ffflag=false;//���ǿ���
						break;
					}
				}
				if(!ffflag)//���ǿ���
				{
					memset(card_buff,0,100);
					st = ICC_Reader_4428_Read(ReaderHandle,27,14,card_buff);
					if(st<0)
					{
						strcpy(Dest,"4428��ȡ����ʧ��!-3");
						ICC_Reader_4428_PowerOff(ReaderHandle);
						return st;
					}
					
					bool feflag=true;;
					for(i=0;i<8;i++)//���ǰ4Ϊ��Ч���֣���Ϊ����
					{
						if(card_buff[i]<0x30 || card_buff[i]>0x39)
						{
							feflag=false;//���ǿ���
							break;
						}
					}
					if(!feflag)//��Ҫ����
					{
						memset(card_buff,0,100);
						st = ICC_Reader_4428_Read(ReaderHandle,37,20,card_buff);
						if(st<0)
						{
							strcpy(Dest,"4428��ȡ����ʧ��!-4");
							ICC_Reader_4428_PowerOff(ReaderHandle);
							return st;
						}
						memset(cbuff,0,100);
						procPassWord(card_buff, (unsigned char*)cbuff, 20);
						/*strdata += "431382";*/
						for(i=0;i<20;i++)
						{
							if(cbuff[i]==' ')
							{
								cbuff[i]=0;
								break;
							}
						}
					}
					else
					{
						memset(cbuff,0,100);
						memcpy(cbuff,card_buff,14);
						for(i=0;i<14;i++)//
						{
							if(cbuff[i]<0x30 || cbuff[i]>0x39)
							{
								cbuff[i]=0;//
								break;
							}
						}
					}
				}
				else //�ǿ���
				{
					memset(cbuff,0,100);
					memcpy(cbuff,card_buff,14);
					for(i=0;i<14;i++)//
					{
						if(cbuff[i]<0x30 || cbuff[i]>0x39)
						{
							cbuff[i]=0;//
							break;
						}
					}
				}
			}
			else
			{
				//memset(cbuff,0,100);
				//memcpy(cbuff,card_buff,20);
				for(i=0;i<40;i++)//
				{
					if(cbuff[i]<0x30 || cbuff[i]>0x39)
					{
						cbuff[i]=0;//
						break;
					}
				}
				cbuff[20]=0;
			}
			strcpy(Dest,cbuff);
			ICC_Reader_4428_PowerOff(ReaderHandle);
		}
		break;
	case 3://�籣
		{
			unsigned char cmd[100]={0};
			unsigned char Response[100]={0};
			unsigned char fakariqi[100] = {0};//��������
			unsigned char kayouxiaoqi[100] = {0};//����Ч��
			unsigned char Shebaokahao[100] = {0};//�籣����
			unsigned char Shehuibaozhang[100] = {0};//��ᱣ�Ϻ���
			unsigned char Name[100] = {0};//����
			unsigned char Sex[100] = {0};//�Ա�
			unsigned char Nation[100] = {0};//����
			unsigned char Address[100] = {0};//������
			unsigned char Birth[100] = {0};//��������

			//ѡSSSE
			memcpy(cmd, "\x00\xA4\x04\x00\x0F\x73\x78\x31\x2E\x73\x68\x2E\xC9\xE7\xBB\xE1\xB1\xA3\xD5\xCF", 20);
			int rt= ICC_Reader_Application(ReaderHandle,0x01, 20, cmd, Response);
			if(Response[rt-2]!=0x61 && Response[rt-2]!=0x90)
			{
				strcpy(Dest,"�籣��ѡSSSEʧ��!");
				ICC_Reader_PowerOff(ReaderHandle,0x01);
				return rt;
			}
			//ѡSSSE/EF05
			memset(cmd, 0, 100);
			memset(Response, 0, 100);
			memcpy(cmd, "\x00\xA4\x02\x00\x02\xEF\x05", 7);
			rt = ICC_Reader_Application(ReaderHandle, 0x01, 7, cmd, Response);
			if(rt<0 || Response[rt-2]!=0x90)
			{
				strcpy(Dest,"�籣��ѡSSSE-EF05ʧ��!");
				ICC_Reader_PowerOff(ReaderHandle,0x01);
				return rt;
			}
			//��������
			memset(cmd, 0, 100);
			memset(Response, 0, 100);
			memcpy(cmd, "\x00\xB2\x05\x00\x04", 5);
			rt = ICC_Reader_Application(ReaderHandle, 0x01, 5, cmd, Response);
			if(rt<0 && Response[rt-2]!=0x90)
			{
				strcpy(Dest,"�������ڶ�ȡʧ��");
				ICC_Reader_PowerOff(ReaderHandle,0x01);
				return rt;
			}
			HexToStr(Response+2,rt-4,fakariqi);//��16����������תΪ�ַ���
			
			//
			//����Ч��
			memset(cmd, 0, 100);
			memset(Response, 0, 100);
			memcpy(cmd, "\x00\xB2\x05\x00\x04", 5);
			rt = ICC_Reader_Application(ReaderHandle, 0x01, 5, cmd, Response);
			if(rt<0 && Response[rt-2]!=0x90)
			{
				strcpy(Dest,"����Ч�ڶ�ȡʧ��");
				ICC_Reader_PowerOff(ReaderHandle,0x01);
				return rt;
			}
			HexToStr(Response+2,rt-4,kayouxiaoqi);//��16����������תΪ�ַ���
			//����
			memset(cmd, 0, 100);
			memset(Response, 0, 100);
			memcpy(cmd, "\x00\xB2\x07\x00\x09", 5);
			rt = ICC_Reader_Application(ReaderHandle, 0x01, 5, cmd, Response);
			if(rt<0 && Response[rt-2]!=0x90)
			{
				strcpy(Dest,"�籣����ʧ��");
				ICC_Reader_PowerOff(ReaderHandle,0x01);
				return rt;
			}
			memcpy(Shebaokahao, Response+2,rt-4);
			//======================================================================
			//ѡSSSE 
			memcpy(cmd, "\x00\xA4\x04\x00\x0F\x73\x78\x31\x2E\x73\x68\x2E\xC9\xE7\xBB\xE1\xB1\xA3\xD5\xCF", 20);
			rt= ICC_Reader_Application(ReaderHandle,0x01, 20, cmd, Response);
			if(Response[rt-2]!=0x61 && Response[rt-2]!=0x90)
			{
				strcpy(Dest,"�籣��ѡSSSEʧ��!");
				ICC_Reader_PowerOff(ReaderHandle,0x01);
				return rt;
			}
			//ѡSSSE/EF06
			memset(cmd, 0, 100);
			memset(Response, 0, 100);
			memcpy(cmd, "\x00\xA4\x02\x00\x02\xEF\x06", 7);
			rt = ICC_Reader_Application(ReaderHandle, 0x01, 7, cmd, Response);
			if(rt<0 || Response[rt-2]!=0x90)
			{
				strcpy(Dest,"�籣��ѡSSSE-EF06ʧ��!");
				ICC_Reader_PowerOff(ReaderHandle,0x01);
				return rt;
			}
			//��ᱣ�Ϻ���
			memset(cmd, 0, 100);
			memset(Response, 0, 100);
			memcpy(cmd, "\x00\xB2\x08\x00\x12", 5);
			rt = ICC_Reader_Application(ReaderHandle, 0x01, 5, cmd, Response);
			if(rt<0 && Response[rt-2]!=0x90)
			{
				strcpy(Dest,"��ᱣ�Ϻ����ȡʧ��");
				ICC_Reader_PowerOff(ReaderHandle,0x01);
				return rt;
			}

			memcpy(Shehuibaozhang, Response+2,rt-4);
			//����
			memset(cmd, 0, 100);
			memset(Response, 0, 100);
			memcpy(cmd, "\x00\xB2\x09\x00\x1E", 5);
			rt = ICC_Reader_Application(ReaderHandle, 0x01, 5, cmd, Response);
			if(rt<0 && Response[rt-2]!=0x90)
			{
				strcpy(Dest,"������ȡʧ��");
				ICC_Reader_PowerOff(ReaderHandle,0x01);
				return rt;
			}
			memcpy(Name, Response+2,rt-4);
			//�Ա�
			memset(cmd, 0, 100);
			memset(Response, 0, 100);
			memcpy(cmd, "\x00\xB2\x0A\x00\x01", 5);
			rt = ICC_Reader_Application(ReaderHandle, 0x01, 5, cmd, Response);
			if(rt<0 && Response[rt-2]!=0x90)
			{
				strcpy(Dest,"�Ա��ȡʧ��");
				ICC_Reader_PowerOff(ReaderHandle,0x01);
				return rt;
			}
			memcpy(Sex, Response+2,rt-4);
			//����
			memset(cmd, 0, 100);
			memset(Response, 0, 100);
			memcpy(cmd, "\x00\xB2\x0B\x00\x01", 5);
			rt = ICC_Reader_Application(ReaderHandle, 0x01, 5, cmd, Response);
			if(rt<0 && Response[rt-2]!=0x90)
			{
				strcpy(Dest,"�����ȡʧ��");
				ICC_Reader_PowerOff(ReaderHandle,0x01);
				return rt;
			}
			HexToStr(Response+2,rt-4,Nation);
			//������
			memset(cmd, 0, 100);
			memset(Response, 0, 100);
			memcpy(cmd, "\x00\xB2\x0C\x00\x03", 5);
			rt = ICC_Reader_Application(ReaderHandle, 0x01, 5, cmd, Response);
			if(rt<0 && Response[rt-2]!=0x90)
			{
				strcpy(Dest,"�����ض�ȡʧ��");
				ICC_Reader_PowerOff(ReaderHandle,0x01);
				return rt;
			}
			HexToStr(Response+2,rt-4,Address);
			//��������
			memset(cmd, 0, 100);
			memset(Response, 0, 100);
			memcpy(cmd, "\x00\xB2\x0D\x00\x04", 5);
			rt = ICC_Reader_Application(ReaderHandle, 0x01, 5, cmd, Response);
			if(rt<0 && Response[rt-2]!=0x90)
			{
				strcpy(Dest,"�������ڶ�ȡʧ��");
				ICC_Reader_PowerOff(ReaderHandle,0x01);
				return rt;
			}
			HexToStr(Response+2,rt-4,Birth);

			sprintf(Dest,"%s|%s|%s|%s|%s|%s|%s|%s|%s",fakariqi,kayouxiaoqi,Shebaokahao,Shehuibaozhang,Name,Sex,Nation,Address,Birth);
		}

		break;
	}
	return 0;
}
int __stdcall IReadCard(char *Source,char *Dest)
{
	int iState=ICC_Reader_GetStatus(ReaderHandle,0x01);
	int rt=0;
	if(iState==-2) //�ǽӴ���
	{
		rt=PICC_Reader_ID_Request(ReaderHandle);//���֤Ѱ��
		if(rt)
		{
			//M1;
		}else
		{
			rt=PICC_Reader_ID_Select(ReaderHandle);//���֤ѡ��
			if(rt) 
			{
				strcpy(Dest,"���֤ѡ��ʧ��!");
				return rt;
			}
			char pName[200]={0};
			char pSex[200]={0};
			char pNation[200]={0};
			char pBirth[200]={0};
			char pAddress[200]={0};
			char pCertNo[200]={0};
			char pDepartment[200]={0};
			char pEffectData[200]={0};
			char pExpire[200]={0};
			char pErrMsg[200]={0};
			rt=PICC_Reader_ReadIDMsg(ReaderHandle,NULL,pName,pSex,pNation,pBirth,pAddress,pCertNo,pDepartment,pEffectData,pExpire,pErrMsg);
			if(rt)
			{
				strcpy(Dest,"���֤����ʧ��!");
				strcat(Dest,pErrMsg);
				return rt;
			}
			for(int i=0;i<200;i++)
			{
				if(pName[i]==0x20) pName[i]=0;
				if(pSex[i]==0x20) pSex[i]=0;
				if(pNation[i]==0x20) pNation[i]=0;
				if(pBirth[i]==0x20) pBirth[i]=0;
				if(pAddress[i]==0x20) pAddress[i]=0;
				if(pCertNo[i]==0x20) pCertNo[i]=0;
				if(pDepartment[i]==0x20) pDepartment[i]=0;
				if(pEffectData[i]==0x20) pEffectData[i]=0;
				if(pExpire[i]==0x20) pExpire[i]=0;
			}
			sprintf(Dest,"%s|%s|%s|%s|%s|%s|%s|%s|%s",pName,pSex,pNation,pBirth,pAddress,pCertNo,pDepartment,pEffectData,pExpire);
			return 0;
		}
	}
	else if(iState==-3 || iState==0)//�Ӵ�
	{
		unsigned char resp[100]={0}; 
		rt=ICC_Reader_pre_PowerOn(ReaderHandle,0x01,resp);//�ϵ� �� �������ݳ���
		if(rt<0) //4428/4442
		{
			memset(resp,0,100);
			rt = ICC_Reader_4428_PowerOn(ReaderHandle,resp);
			if(rt)
			{
				strcpy(Dest,"���֤����ʧ��!");
				return rt;
			}
			else//4428/4442�ϵ�ɹ�
			{
				memset(resp,0,100);
				unsigned char Data1[1025]={0};
				rt = ICC_Reader_4428_Read(ReaderHandle,0,1024,Data1);
				if(Data1[1022] == 0) //4428
				{
					rt=Read_Contact_Card_Info(2,Dest);
					if(rt) return rt;
					return 0;
				}
				else if(Data1[1022] == 0xFF) //4442
				{
					rt=Read_Contact_Card_Info(1,Dest);
					if(rt) return rt;
					return 0;
				}
			}

		}//end if 4442/4428
		//���籣��
		rt=Read_Contact_Card_Info(3,Dest);
		if(rt) return rt;
		return 0;
	}
	else
	{
		strcpy(Dest,"�޿���");
		return 1;
	}
}
int __stdcall IWriteCard(const char *Source,char *Dest)
{
	return 0;
}