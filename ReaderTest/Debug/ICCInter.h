#ifndef ICCInter_H
#define ICCInter_H

#define OPEN_FAILURE	       1       //���豸ʧ��
#define POWERON_FAILURE	       2       //��Ƭ�ϵ�ʧ��
#define EXC_APDU_FAILURE	   3       //ִ��ָ��ʧ��
#define ERR_CARDTYPE	       4       //���ʹ���
#define GET_DEVN_FAILURE	   5       //��ȡ�豸���к�ʧ��
#define SAM_ON_FAILURE	       6       //SAM���ϵ�ʧ��

#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{
	unsigned long	readertype;			//����
	unsigned long	cardtype;			//����
	unsigned long	port;				//����
	unsigned long	baud;				//����
	HANDLE			commdevice;			//����
	unsigned long	timeout;			//����
	unsigned char	*PIN;				//����
	unsigned char	*Key;				//����
	unsigned char	*HostAddr;			//����
	unsigned long	HostTimeOut;		//����
	unsigned char	*CardSN;			//����
	unsigned long	OpType;				//����	
    unsigned long	TransType;			//����
	unsigned char	*ATR;				//����
	unsigned char	*CardNumber;		//����
	unsigned char	reserved[20];		//����
} ICC_ENV;
int __stdcall IC_GetData(ICC_ENV *iccenv,int datatype,char *data);
int __stdcall IC_OpenSession(ICC_ENV *iccenv);
int __stdcall IC_CloseSession(ICC_ENV *iccenv);
int __stdcall IC_SaveData(ICC_ENV *iccenv, int datatype, unsigned char *data);
int __stdcall IC_PINVerify(ICC_ENV *iccenv);
int __stdcall IC_Beep(unsigned char time);//����
//long WINAPI ICC_PosBeep(long ReaderHandle, unsigned char time);//����
#ifdef __cplusplus
}
#endif
#endif
