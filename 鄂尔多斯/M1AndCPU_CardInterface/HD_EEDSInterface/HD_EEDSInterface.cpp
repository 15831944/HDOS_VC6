// HD_EEDSInterface.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "HD_EEDSInterface.h"
#include "Utils.h"
#include "ConvertUtil.h"
#include "StringUtil.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
char Encode_GetChar(BYTE num)
{
    return 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "+/="[num];
}
//����
size_t Base64_Encode(char *pDest, const char *pSrc, size_t srclen)
{
    BYTE input[3], output[4];
    size_t i, index_src = 0, index_dest = 0;
    for(i = 0; i < srclen; i += 3)
    {
        //char [0]
        input[0] = pSrc[index_src++];
        output[0] = (BYTE)(input[0] >> 2);
        pDest[index_dest++] = Encode_GetChar(output[0]);

        //char [1]
        if(index_src < srclen)
        {
            input[1] = pSrc[index_src++];
            output[1] = (BYTE)(((input[0] & 0x03) << 4) + (input[1] >> 4));
            pDest[index_dest++] = Encode_GetChar(output[1]);
        }
        else
        {
            output[1] = (BYTE)((input[0] & 0x03) << 4);
            pDest[index_dest++] = Encode_GetChar(output[1]);
            pDest[index_dest++] = '=';
            pDest[index_dest++] = '=';
            break;
        }
        
        //char [2]
        if(index_src < srclen)
        {
            input[2] = pSrc[index_src++];
            output[2] = (BYTE)(((input[1] & 0x0f) << 2) + (input[2] >> 6));
            pDest[index_dest++] = Encode_GetChar(output[2]);
        }
        else
        {
            output[2] = (BYTE)((input[1] & 0x0f) << 2);
            pDest[index_dest++] = Encode_GetChar(output[2]);
            pDest[index_dest++] = '=';
            break;
        }

        //char [3]
        output[3] = (BYTE)(input[2] & 0x3f);
        pDest[index_dest++] = Encode_GetChar(output[3]);
    }
    //null-terminator
    pDest[index_dest] = 0;
    return index_dest;
}
int CleanName(char *name)
{
	int i;
	int len = (int)strlen(name);

	for(i=0; i < len; i++) {
		if(name[i] == 'F' && (!(i%5))) {
			name[i] = 0;
			break;
		}
	}

	return 0;
}
EEDS_HD_API int __stdcall ReadInfo(unsigned char *pKey, 
								   unsigned char *GECHH, 
								   unsigned char *XM, 
								   unsigned char *SFZH, 
								   unsigned char *CSRQ, 
								   unsigned char *XB, 
								   unsigned char *MZ,
								   char *pErr)
{
	HANDLE hDev=NULL;
	char sGECHH[50]={0};
	char sXM[40]={0};
	char sSFZH[20]={0};
	char sCSRQ[10]={0};
	char sXB[10]={0};
	char sMZ[10]={0};
	char ATR[50]={0};
	int ret=iDOpenPort();
//	if(ret!=0)
//	{
//		sprintf(pErr,"���豸ʧ��,�������(WSB):%d",ret);
//		return 1;
//	}
	ret=PowerOn(hDev ,0x01,ATR);
	if(ret==0)
	{
		ret=PowerOn(hDev ,0x11,ATR);
		if(ret!=0)
		{
			iDClosePort();
			sprintf(pErr,"SAM���ϵ�ʧ��,�������(WSB):%d",ret);
			return 1;
		}
		ret=iVerifyPIN(hDev,"123456");
		if(ret!=0)
		{
			iDClosePort();
			sprintf(pErr,"SAM��֤PINʧ��,�������(WSB):%d",ret);
			return 1;
		}
		ret=iR_DDF1EF06Info(hDev,sXM,sXB,sMZ,sCSRQ,sSFZH);
		if(ret)
		{
			iDClosePort();
			sprintf(pErr,"��DDF1EF06ʧ��,�������(WSB):%d",ret);
			return 1;
		}
		char Temp[50]={0};
		ret=iR_DF01EF08Info(hDev,Temp,Temp,Temp,sGECHH);
		if(ret)
		{
			iDClosePort();
			sprintf(pErr,"��DDF1EF08ʧ��,�������(WSB):%d",ret);
			return 1;
		}
		iDClosePort();
		strcpy((char *)GECHH,sGECHH);
		strcpy((char *)XM,sXM);
		strcpy((char *)SFZH,sSFZH);
		strcpy((char *)CSRQ,sCSRQ);
		strcpy((char *)XB,sXB);
		strcpy((char *)MZ,sMZ);
	}
	else
	{
//		char Test[100]="����";//641945115841655fffffffffffffffff
//		char szName[100] ={0} ;
//		string strName=CConvertUtil::uf_gbk_int_covers(Test,"toint");
//		char Test2[100]="5448549601";
//		strName=CConvertUtil::uf_gbk_int_covers(Test2,"togbk");
		//memcpy(Test2,"\x64\x19\x45\x11\x58\x41\x65\x50",8);\x54\x48\x54\x96\x01
		//memcpy(Test2,"\x54\x48\x54\x96\x01\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff",16);
			////////////////////
		iDClosePort();
		long ReaderHandle=ICC_Reader_Open("USB1");
		if(ReaderHandle<=0)
		{
			sprintf(pErr,"SSSE32�򿪶˿�ʧ��,�������:%d",ReaderHandle);
			return 1;
		}
		int ret=PICC_Reader_Request(ReaderHandle);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32����Ƭʧ��,�������(�޿�):%d",ret);
			return 1;
		}
		unsigned char uid[50]={0};
		ret=PICC_Reader_anticoll(ReaderHandle,uid);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32����ײʧ��,�������:%d",ret);
			return 1;
		}
		ret=PICC_Reader_Select(ReaderHandle,0x41);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32ѡ��ʧ��,�������:%d",ret);
			return 1;
		}
		unsigned char Data[40]={0};
		unsigned char DataStr[40]={0};
		unsigned char key[10]={0};
		Utils::HexstrToBin(key,pKey,12);
		//��ũ�Ͽ���
		ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,1,key);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32��֤s1����ʧ��,�������:%d",ret);
			return 1;
		}
		ret=PICC_Reader_Read(ReaderHandle,6,Data);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32����6ʧ��,�������:%d",ret);
			return 1;
		}
		Utils::BinToHexstr(DataStr,Data,16);
		memcpy(sGECHH,DataStr+6,18);
		//��������Ϣ
		ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,2,key);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32��֤s2����ʧ��,�������:%d",ret);
			return 1;
		}
		//����
		ret=PICC_Reader_Read(ReaderHandle,8,Data);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32����8ʧ��,�������:%d",ret);
			return 1;
		}
		ret=PICC_Reader_Read(ReaderHandle,9,Data+16);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32����9ʧ��,�������:%d",ret);
			return 1;
		}
		unsigned char stemp[100]={0};
		Utils::BinToHexstr(stemp,Data,32);
		CleanName((char *)stemp);
		string szName;
		if(Is_IntName((char *)stemp))
		{
			szName = CConvertUtil::uf_gbk_int_covers((char *)stemp,"togbk");
			strcpy(sXM,(const char *)szName.c_str());
		}else
		{
			strcpy(sXM,(const char *)Data);
		}
		//���֤�ţ��������ڣ��Ա�
		ret=PICC_Reader_Read(ReaderHandle,10,Data);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32����10ʧ��,�������:%d",ret);
			return 1;
		}
		Utils::BinToHexstr(DataStr,Data,16);
		memcpy(sSFZH,DataStr,18);
		memcpy(sCSRQ,DataStr+18,8);
		memcpy(sXB,DataStr+26,1);
		//������
		ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,3,key);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32��֤s3����ʧ��,�������:%d",ret);
			return 1;
		}
		ret=PICC_Reader_Read(ReaderHandle,12,Data);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32����12ʧ��,�������:%d",ret);
			return 1;
		}
		ICC_Reader_Close(ReaderHandle);
		Utils::BinToHexstr(DataStr,Data,16);
		memcpy(sMZ,DataStr,2);

		strcpy((char *)GECHH,sGECHH);
		strcpy((char *)XM,sXM);
		strcpy((char *)SFZH,sSFZH);
		strcpy((char *)CSRQ,sCSRQ);
		strcpy((char *)XB,sXB);
		strcpy((char *)MZ,sMZ);
	}
	return 0;
}
EEDS_HD_API int __stdcall iReadCard(unsigned char *OutXml,char *pErr)
{
	HANDLE hDev=NULL;
	int rt=iDOpenPort();
	if(rt!=0)
	{
		sprintf(pErr,"<ERROR>�򿪶˿�ʧ��,�������%d</ERROR>",rt);
		return 1;
	}
	char ATR[50]={0};
	rt=PowerOn(hDev,0x01,ATR);
	if(rt==0)
	{
		rt=PowerOn(hDev,0x11,ATR);
		if(rt!=0)
		{
			iDClosePort();
			sprintf(pErr,"<ERROR>PSAM���ϵ�ʧ��,�������%d</ERROR>",rt);
			return 1;
		}
		rt=iVerifyPIN(hDev,"123456");
		if(rt!=0)
		{
			sprintf(pErr,"<ERROR>У��PSAM��PINʧ��,�������%d</ERROR>",rt);
			iDClosePort();
			return 1;
		}
		//���ֿ��˻�����Ϣ
		char XM[50]={0};             //����
		char XB[50]={0};               //�Ա����
		char MZ[50]={0};               //�������
		char CSRQ[50]={0};             //�������ڣ�YYYYMMDD��ʽ
		char SFZH[50]={0};            //�������֤��
		rt=iR_DDF1EF06Info(hDev,XM,XB,MZ,CSRQ,SFZH);
		if(rt!=0)
		{
			sprintf(pErr,"<ERROR>���ֿ��˻�����Ϣʧ��,�������%d</ERROR>",rt);
			iDClosePort();
			return 1;
		}
		//����Ƭ��Ϣ
		unsigned char picData[3075]={0};
		char picDataBase64[6000]={0};
		rt=iR_DDF1EF07Info(hDev,picData);
		if(rt!=0)
		{
			sprintf(pErr,"<ERROR>����Ƭ��Ϣʧ��,�������%d</ERROR>",rt);
			iDClosePort();
			return 1;
		}
		char piclen[10]={0};
		sprintf(piclen,"%02x%02x",picData[0],picData[1]);
		long len=strtol(piclen,NULL,16);
		Base64_Encode(picDataBase64,(const char *)picData+2,len);
		//���ֿ���֧����Ϣ
		char KYXQ[21]={0};			//����Ч��
		char BRDH1[21]={0};         //���˵绰1
		char BRDH2[21]={0};           //���˵绰2
		char YLFYZFFS1[21]={0};		  //ҽ�Ʒ���֧����ʽ1
		char YLFYZFFS2[21]={0};		  //ҽ�Ʒ���֧����ʽ2
		char YLFYZFFS3[21]={0};		  //ҽ�Ʒ���֧����ʽ3
		rt=iR_DDF1EF08Info(hDev,KYXQ,BRDH1,BRDH2,YLFYZFFS1,YLFYZFFS2,YLFYZFFS3);
		if(rt!=0)
		{
			sprintf(pErr,"<ERROR>���ֿ���֧����Ϣʧ��,�������%d</ERROR>",rt);
			iDClosePort();
			return 1;
		}
		//����ַ��Ϣ
		char DZLB1[21]={0};		
		char DZ1[120]={0};       
		char DZLB2[21]={0};     
		char DZ2[120]={0};		  
		rt=iR_DF01EF05Info(hDev,DZLB1,DZ1,DZLB2,DZ2);
		if(rt!=0)
		{
			sprintf(pErr,"<ERROR>����ַ��Ϣʧ��,�������%d</ERROR>",rt);
			iDClosePort();
			return 1;
		}
		//����ϵ����Ϣ
		char LXRXM1[40]={0};		
		char LXRGX1[2]={0};       
		char LXRDH1[30]={0};
		char LXRXM2[40]={0};		
		char LXRGX2[2]={0};       
		char LXRDH2[30]={0}; 
		char LXRXM3[40]={0};		
		char LXRGX3[2]={0};       
		char LXRDH3[30]={0}; 
		rt=iR_DF01EF06Info(hDev,LXRXM1,LXRGX1,LXRDH1,LXRXM2,LXRGX2,LXRDH2,LXRXM3,LXRGX3,LXRDH3);
		if(rt!=0)
		{
			sprintf(pErr,"<ERROR>����ϵ����Ϣʧ��,�������%d</ERROR>",rt);
			iDClosePort();
			return 1;
		}
		//��ְҵ������Ϣ
		char WHCD[10]={0};		
		char HYZK[10]={0};       
		char ZY[10]={0};
		rt=iR_DF01EF07Info(hDev,WHCD,HYZK,ZY);
		if(rt!=0)
		{
			sprintf(pErr,"<ERROR>��ְҵ������Ϣʧ��,�������%d</ERROR>",rt);
			iDClosePort();
			return 1;
		}
		//��֤����Ϣ
		char ZJLB[20]={0};		
		char ZJHM[20]={0};       
		char JKDAH[20]={0};
		char XNHZH[20]={0};
		rt=iR_DF01EF08Info(hDev,ZJLB,ZJHM,JKDAH,XNHZH);
		if(rt!=0)
		{
			sprintf(pErr,"<ERROR>��֤����Ϣʧ��,�������%d</ERROR>",rt);
			iDClosePort();
			return 1;
		}
		sprintf((char *)OutXml,"<DDF1EF06><XM>%s</XM><XB>%s</XB><MZ>%s</MZ><CSRQ>%s</CSRQ><JMSFZHM>%s</JMSFZHM></DDF1EF06>\r\n<DDF1EF07><ZPSJ>%s</ZPSJ></DDF1EF07>\r\n<DDF1EF08><KYXQ>%s</KYXQ><BRDH1>%s</BRDH1><BRDH2>%s</BRDH2><YLFYZFFS1>%s</YLFYZFFS1><YLFYZFFS2>%s</YLFYZFFS2><YLFYZFFS3>%s</YLFYZFFS3></DDF1EF08>\r\n<DF01EF05><DZLB1>%s</DZLB1><DZ1>%s</DZ1><DZLB2>%s</DZLB2><DZ2>%s</DZ2></DF01EF05>\r\n<DF01EF06><LXRXM1>%s</LXRXM1><LXRGX1>%s</LXRGX1><LXRDH1>%s</LXRDH1><LXRXM2>%s</LXRXM2><LXRGX2>%s</LXRGX2><LXRDH2>%s</LXRDH2><LXRXM3>%s</LXRXM3><LXRGX3>%s</LXRGX3><LXRDH3>%s</LXRDH3></DF01EF06>\r\n<DF01EF07><WHCD>%s</WHCD><HYZK>%s</HYZK><ZY>%s</ZY></DF01EF07>\r\n<DF01EF08><ZJLB>%s</ZJLB><ZJHM>%s</ZJHM><JKDAH>%s</JKDAH><XNHZH>%s</XNHZH></DF01EF08>",XM,XB,MZ,CSRQ,SFZH,picDataBase64,KYXQ,BRDH1,BRDH2,YLFYZFFS1,YLFYZFFS2,YLFYZFFS3,DZLB1,DZ1,DZLB2,DZ2,LXRXM1,LXRGX1,LXRDH1,LXRXM2,LXRGX2,LXRDH2,LXRXM3,LXRGX3,LXRDH3,WHCD,HYZK,ZY,ZJLB,ZJHM,JKDAH,XNHZH);
	}else
	{
		char sGECHH[50]={0};
		char sXM[40]={0};
		char sSFZH[20]={0};
		char sCSRQ[10]={0};
		char sXB[10]={0};
		char sMZ[10]={0};
		long ReaderHandle=ICC_Reader_Open("USB1");
		if(ReaderHandle<=0)
		{
			sprintf(pErr,"<ERROR>SSSE32�򿪶˿�ʧ��,�������:%d</ERROR>",rt);
			return 1;
		}
		int ret=PICC_Reader_Request(ReaderHandle);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"<ERROR>SSSE32����Ƭʧ��,�������(�޿�):%d</ERROR>",rt);
			return 1;
		}
		unsigned char uid[50]={0};
		ret=PICC_Reader_anticoll(ReaderHandle,uid);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"<ERROR>SSSE32����ײʧ��,�������:%d</ERROR>",rt);
			return 1;
		}
		ret=PICC_Reader_Select(ReaderHandle,0x41);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"<ERROR>SSSE32ѡ��ʧ��,�������:%d</ERROR>",rt);
			return 1;
		}
		unsigned char Data[40]={0};
		unsigned char DataStr[40]={0};
		unsigned char key[10]={0};
		//memcpy(key,"\x43\x97\x04\x47\x20\x47",6);
		memcpy(key,"\xff\xff\xff\xff\xff\xff",6);
		//��ũ�Ͽ���
		ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,1,key);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"<ERROR>SSSE32��֤s1����ʧ��,�������:%d</ERROR>",rt);
			return 1;
		}
		ret=PICC_Reader_Read(ReaderHandle,6,Data);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"<ERROR>SSSE32����6ʧ��,�������:%d</ERROR>",rt);
			return 1;
		}
		Utils::BinToHexstr(DataStr,Data,16);
		memcpy(sGECHH,DataStr+6,18);
		//��������Ϣ
		ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,2,key);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"<ERROR>SSSE32��֤s2����ʧ��,�������:%d</ERROR>",rt);
			return 1;
		}
		//����
		ret=PICC_Reader_Read(ReaderHandle,8,Data);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"<ERROR>SSSE32����8ʧ��,�������:%d</ERROR>",rt);
			return 1;
		}
		ret=PICC_Reader_Read(ReaderHandle,9,Data+16);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"<ERROR>SSSE32����9ʧ��,�������:%d</ERROR>",rt);
			return 1;
		}
		unsigned char stemp[100]={0};
		Utils::BinToHexstr(stemp,Data,32);
		CleanName((char *)stemp);
		string szName;
		if(Is_IntName((char *)stemp))
		{
			szName = CConvertUtil::uf_gbk_int_covers((char *)stemp,"togbk");
			strcpy(sXM,(const char *)szName.c_str());
		}else
		{
			strcpy(sXM,(const char *)Data);
		}
		//���֤�ţ��������ڣ��Ա�
		ret=PICC_Reader_Read(ReaderHandle,10,Data);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"<ERROR>SSSE32����10ʧ��,�������:%d</ERROR>",rt);
			return 1;
		}
		Utils::BinToHexstr(DataStr,Data,16);
		memcpy(sSFZH,DataStr,18);
		if(sSFZH[17]>'a'||sSFZH[17]<'z'||sSFZH[17]>='A'||sSFZH[17]<='Z')
		{
			sSFZH[17]='X';
		}
		memcpy(sCSRQ,DataStr+18,8);
		memcpy(sXB,DataStr+26,1);
		//������
		ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,3,key);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"<ERROR>SSSE32��֤s3����ʧ��,�������:%d</ERROR>",rt);
			return 1;
		}
		ret=PICC_Reader_Read(ReaderHandle,12,Data);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"<ERROR>SSSE32����12ʧ��,�������:%d</ERROR>",rt);
			return 1;
		}
		ICC_Reader_Close(ReaderHandle);
		Utils::BinToHexstr(DataStr,Data,16);
		memcpy(sMZ,DataStr,2);
		sprintf((char *)OutXml,"<DDF1EF06><XM>%s</XM><XB>%s</XB><MZ>%s</MZ><CSRQ>%s</CSRQ><JMSFZHM>%s</JMSFZHM></DDF1EF06>\r\n<DDF1EF07><ZPSJ></ZPSJ></DDF1EF07>\r\n<DDF1EF08><KYXQ></KYXQ><BRDH1></BRDH1><BRDH2></BRDH2><YLFYZFFS1></YLFYZFFS1><YLFYZFFS2></YLFYZFFS2><YLFYZFFS3></YLFYZFFS3></DDF1EF08>\r\n<DF01EF05><DZLB1></DZLB1><DZ1></DZ1><DZLB2></DZLB2><DZ2></DZ2></DF01EF05>\r\n<DF01EF06><LXRXM1></LXRXM1><LXRGX1></LXRGX1><LXRDH1></LXRDH1><LXRXM2></LXRXM2><LXRGX2></LXRGX2><LXRDH2></LXRDH2><LXRXM3></LXRXM3><LXRGX3></LXRGX3><LXRDH3></LXRDH3></DF01EF06>\r\n<DF01EF07><WHCD></WHCD><HYZK></HYZK><ZY></ZY></DF01EF07>\r\n<DF01EF08><ZJLB></ZJLB><ZJHM></ZJHM><JKDAH></JKDAH><XNHZH>%s</XNHZH></DF01EF08>",sXM,sXB,sMZ,sCSRQ,sSFZH,sGECHH);
	}
	iDClosePort();
	return 0;
}
