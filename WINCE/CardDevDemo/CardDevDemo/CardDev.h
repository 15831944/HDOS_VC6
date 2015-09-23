// HDCardDev.h : HDCardDev DLL ����ͷ�ļ�
//

#ifndef CARDDEV_H
#define CARDDEV_H

/*״̬��*/
#define IFD_OK	0					     /*ִ�гɹ�*/
#define IFD_OpenError	-1		     /*�򿪴���ʧ��*/
#define IFD_CloseError	-2			 /*�رմ���ʧ��*/
#define IFD_SendError	-3			 /*��������ʧ��*/
#define IFD_RevError   	-4	         /*��������ʧ��*/
#define IFD_ActiveError	-5	           /*Ѱ��ʧ��*/
#define IFD_AuthError    -6           /*��֤ʧ��*/
#define IFD_ReadError    -7          /*��M1ʧ��*/
#define IFD_WriteError   -8              /*дM1ʧ��*/
#define IFD_ReadIDCardError -9    /*дM1ʧ��*/
#define IFD_OTHER	        -10           /*��������*/

/*############�豸��������#################*/
#ifdef __cplusplus
extern "C" {
#endif

long WINAPI hd_Open(int Port);  //�򿪴���

long WINAPI hd_Close();  //�رմ���

long WINAPI hd_Active(TCHAR * uid);  // M1��Ѱ������

long WINAPI hd_AuthPass(unsigned char Mode, unsigned char SecNr, unsigned char *PassWord); //M1����֤

long WINAPI hd_Read(unsigned char Addr,unsigned char*Data);  //M1����������

long WINAPI hd_Write(unsigned char Addr, unsigned char*Data);  //M1��д������

long WINAPI hd_ReadIDCard(const TCHAR* sBmpFile,
					   TCHAR* sName, 
					   TCHAR* sSex, 
					   TCHAR* sNation, 
					   TCHAR* sBirth, 
					   TCHAR* sAddress, 
					   TCHAR* sCertNo, 
					   TCHAR* sDepartment, 
					   TCHAR* sEffectTime,
					   TCHAR* sExpire);

#ifdef __cplusplus
}
#endif
#endif