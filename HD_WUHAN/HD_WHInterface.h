#ifndef HD_WHInterface_H
#define HD_WHInterface_H

//#define OPEN_FAILURE	       1       //���豸ʧ��
//#define POWERON_FAILURE	       2       //��Ƭ�ϵ�ʧ��
//#define EXC_APDU_FAILURE	   3       //ִ��ָ��ʧ��
//#define ERR_CARDTYPE	       4       //���ʹ���
//#define GET_DEVN_FAILURE	   5       //��ȡ�豸���к�ʧ��
//#define SAM_ON_FAILURE	       6       //SAM���ϵ�ʧ��

#ifdef __cplusplus
extern "C" {
#endif

int __stdcall IC_GetMagneData(char *dataOut,int TimeOut);
int __stdcall IC_GetData(char *dataOut,char *pErr,int TimeOut);

#ifdef __cplusplus
}
#endif
#endif
