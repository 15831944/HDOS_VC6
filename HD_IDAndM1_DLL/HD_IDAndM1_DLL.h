#ifndef ICCInter_H
#define ICCInter_H
/////////////////////// M1 Error Code ////////////////////////
#define REQUEST_FAILURE	       -1       //����Ƭʧ��
#define ANTICOL_FAILURE	       -2       //����ײʧ��
#define SELECT_FAILURE	       -3       //ѡ��ʧ��
#define AUTH_FAILURE	       -4       //��֤����ʧ��
#define READ_FAILURE	       -5       //��M1������ʧ��
#define WRITE_FAILURE	       -6       //дM1��ʧ��
/////////////////////// ID Error Code ////////////////////////
#define SHD_OK					  0		 //ִ�гɹ�
#define SHD_Connect_Error		 -1	     //�豸���Ӵ�
#define SHD_UnConnected		 	 -2	     //�豸δ��������(û��ִ�д��豸����)
#define SHD_BadLoadDLL_Error	 -3	     //(��̬��)����ʧ��
#define SHD_Parameter_Error		 -4	     //(������̬���)������
#define SHD_Request_Error		 -5		 //Ѱ��ʧ��
#define SHD_Select_Error		 -6		 //ѡ��ʧ��
#define SHD_ReadBase_Error	     -7		 //����ʧ��
#define SHD_ReadBaseFP_Error     -8	     //��ȡ׷����Ϣʧ��
#define SHD_ReadADD_Error	     -9	     //��ȡ׷����Ϣʧ��
#define SHD_Sam_Error	        -10      //����ͨ��ʧ��
#define SHD_CheckSam_Error	    -11      //����ͨ��ʧ��
#define SHD_SamToFinger_Error	-12      //����ͨ��ģ�鲻֧�ֻ�ȡָ��
#define SHD_OTHER_ERROR	        -999	 //�����쳣����
#ifdef __cplusplus
extern "C" {
#endif


//////////////////////  M1   ///////////////////
long __stdcall Reader_Open();
long __stdcall Reader_Close(long ReaderHandle);
int __stdcall Find_M1Card(long ReaderHandle,unsigned char *uid);
long __stdcall Authentication_Pass(long ReaderHandle,unsigned char Mode, unsigned char SecNr,unsigned char *PassWord);
long __stdcall Reader_Read(long  ReaderHandle,unsigned char Addr,unsigned  char *Data);
long __stdcall Reader_Write(long ReaderHandle,unsigned char Addr,unsigned char *Data);
//////////////////////  ���֤   ///////////////////
int __stdcall Reader_ReadIdCard(const char* pBmpFile, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData, char *pExpire);
#ifdef __cplusplus
}
#endif
#endif
