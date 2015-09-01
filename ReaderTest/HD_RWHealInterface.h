#ifndef HD_CARDINTERFACE_H
#define MHC_CARDINTERFACE_H

#define MHC_CARDINTERFACE_API  extern "C" __declspec(dllexport)

#define IRV_OK			0			//����
#define IRV_PARA_ERR	101			//���������
#define IRV_NO_FILE		102			//�ļ�������
#define IRV_RD_RCDERR	103			//����¼ʧ��
#define IRV_CARD_ERR	104			//��Ƭ��Ӧ�쳣
#define IRV_PSAM_ERR	105			//PSAM��Ƭ��Ӧ�쳣
#define IRV_IRK_VERR	106			//�ڲ���֤ʧ��
#define IRV_RD_BINERR	107			//��BINʧ��
#define IRV_WR_RCDERR	108			//д��¼ʧ��
#define IRV_WR_BINERR	109			//дBINʧ��
#define IRV_W_DF03EF05ERR	110			//дDF03EF05ʧ��
#define IRV_ER_DF03EF05ERR	111			//����DF03EF05ʧ��
#define IRV_RCINVALID	112			//��¼������(ef ��Ч���Ϊ ff)
#define IRV_DDF1EF07_DATAERR	113			//��Ƭ�ļ������쳣
#define PARA_COVERT_ERR	114			//�޷�������ת��������
#define GETCARD_INFO_ERR	115      // wsc_GetCardInfo����
#define NO_style			0x00

#define AN_style			0x01
#define CN_style			0x0F
#define B_style				0xFF

#define SLOT_USER			0x01
#define SLOT_PSAM			0x11
#define SLOT_CARD			0x12	
MHC_CARDINTERFACE_API int __stdcall IDOpenPort(void);//�����豸
MHC_CARDINTERFACE_API int __stdcall IDClosePort(void);//�ر��豸
//�ϵ縴λ
// slot = SLOT_USER(0x01) �û����ϵ�
// slot = SLOT_PSAM(0x11) SAM���ϵ�
// ATR��Ҫ����40+1���ϵ��ַ��ռ�
MHC_CARDINTERFACE_API int __stdcall IPowerOn(HANDLE hDev,int slot, char * ATR) ; //slot 1  User; slot 0x11 SAM1
MHC_CARDINTERFACE_API int __stdcall IVerifyPIN(HANDLE hDev,char * PIN) ;//У��PSAM��PIN
MHC_CARDINTERFACE_API int __stdcall IChange_Pin(int hDev,char *oldPin,char *newPin); //�޸�PIN
MHC_CARDINTERFACE_API int __stdcall IR_ReadCard(char *para,char *dataOut);
MHC_CARDINTERFACE_API int __stdcall IR_WriteCard(char *para,char *dataIn);



#endif