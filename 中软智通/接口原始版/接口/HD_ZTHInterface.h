#ifndef HD_HD_ZTHInterface_H
#define HD_HD_ZTHInterface_H

//#define OPEN_FAILURE	       1       //���豸ʧ��
//#define POWERON_FAILURE	       2       //��Ƭ�ϵ�ʧ��
//#define EXC_APDU_FAILURE	   3       //ִ��ָ��ʧ��
//#define ERR_CARDTYPE	       4       //���ʹ���
//#define GET_DEVN_FAILURE	   5       //��ȡ�豸���к�ʧ��
//#define SAM_ON_FAILURE	       6       //SAM���ϵ�ʧ��

#ifdef __cplusplus
extern "C" {
#endif

int __stdcall HD_OpenDevice(char *PIN,char *pErr);
int __stdcall HD_CloseDevice();
int __stdcall HD_ReadCardInfo(char *Key,char *CardType,char *CardNo,char *Name,char *Sex,char *Born,char *IDNo,char *MakeCDT,char *EffectD,char *Nation,char *pErr);

#ifdef __cplusplus
}
#endif
#endif