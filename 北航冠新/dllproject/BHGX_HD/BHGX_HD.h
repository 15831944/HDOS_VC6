#ifndef BHGX_HD_H
#define BHGX_HD_H

#define BHGX_HD_API extern "C" __declspec(dllexport)

#define WS_OK						  0 //	�ɹ�
#define WS_ERR_UserCancle	    	 -1 //	�û�ȡ������
#define WS_ERR_PHOTOFILELarge		 -2 //	��Ƭ�ļ�����!(���֧�� 3K ��С����Ƭ)
#define WS_ERR_Empty	        	 -3//	������Ч(Ϊ��)
#define WS_ERR_KBCONNECT	    	 -4 //	������������쳣
#define WS_ERR_FileNoErr	    	 -5 //	��¼��ʶ��Ч
#define WS_ERR_DataLenErr	    	 -6 //	�������ݳ�����Ч
#define WS_ERR_PINERR	        	 -7 //	PIN ����֤ʧ��
#define WS_ERR_ItemTAG	        	 -8 //	���� TAG ��ʶ��Ч
#define WS_ERR_ItemNo	        	 -9 //	�����¼����Ч
#define WS_ERR_UnAllowWrite	    	-10 //	�����ݲ�����д��
#define WS_ERR_UNSUPPORTED	    	-11 //	���ܲ�֧��
#define WS_ERR_RCertInfos	    	-12 //	��ȡ���֤�쳣[��ſ�����!]
#define WS_ERR_CreatePhotoFile		-13 //	�������֤�ֿ�����Ƭ�ļ�ʧ��
#define WS_ERR_DEVICEUNINIT	    	-14 //	�豸δ��ʼ�����ѹر�
#define WS_ERR_DataStyleCheckErr	-15 //	�������ݸ�ʽ��Ч
#define WS_ERR_UNKNOWN	        	-16 //	δ֪����
#define WS_ERR_RLength	        	-17 //	��������ݳ��ȱ�ʶ��Ч
#define WS_ERR_ROffSET	        	-18 //	����ж�ȡƫ������ʶ��Ч

#define	WS_ERR_RDataStyle			-19 //������������ͱ�ʶ��Ч
#define	WS_ERR_CARDMISS				-20 //�޿�
#define	WS_ERR_NORESPONSE_CPU		-21 //�û�������Ӧ[������]
#define	WS_ERR_NORESPONSE_SAM		-22 //PSAM ������Ӧ[������]
#define	WS_ERR_RESET_SAM			-23 //PSAM ����λ�쳣[���忨��û�忨������Ч]
#define	WS_ERR_RESET_CPU			-24 //δѰ����,[û�ſ�������Ч],������!
#define	WS_ERR_SETSLOTID			-25 //���ÿ����쳣
#define	WS_ERR_DataItemsErr			-26 //�����������淶����
#define	WS_ERR_InputPassOutTime		-27 //�������볬ʱ,������!
#define	WS_ERR_GetPassCancel		-28 //�û�ȡ����������
#define	WS_ERR_TLVLenthErr			-29 //TLV ������ Length ��Ч
#define	WS_ERR_PORTPARAMETER		-30 //�˿ڲ�����Ч
#define	WS_ERR_GETDEVICEVER			-31 //�豸�汾��Ϣ��ȡ�쳣
#define	WS_ERR_DEVICEVer			-32 //�汾����Ч(�Ƿ��豸)
#define	WS_ERR_DEVICECONNECT		-33 //�豸�����쳣
#define	WS_ERR_UNSLOTID				-34 //����������Ч
#define	WS_ERR_APDUDataLenErr		-35 //APDU ���ݳ�����Ч
#define WS_ERR_DEVICESNR			-36 //�豸���кŶ�ȡ��У���쳣
#define	WS_ERR_CARDTYPE				-37 //�޿�
#define WS_ERR_IC					-99 //��Ƭ����Ӧ�����
#define WS_ERR_OTHER			    -999 //�����쳣����

BHGX_HD_API BOOL __stdcall bProbe(void);
BHGX_HD_API int __stdcall iOpen(void);
BHGX_HD_API int __stdcall iClose(void);
BHGX_HD_API int __stdcall iReadBin(unsigned char iCardType, unsigned char *pKey, unsigned char *pBuf, int iSizeInBytes, int iOffsetInBytes);
BHGX_HD_API int __stdcall iWriteBin(unsigned char iCardType, unsigned char *pKey, const unsigned char *pBuf, int nCtrlword, int iSizeInBytes, int iOffsetInBytes);
BHGX_HD_API int __stdcall iReadRec(unsigned char iCardType, unsigned char *pKey, unsigned char *pBuf, unsigned long buflen, int  iRecNo, int  iRecCount);
BHGX_HD_API int __stdcall iWriteRec(unsigned char iCardType, unsigned char *pKey, unsigned char *pBuf, unsigned long buflen, int  iRecNo, int  iRecCount);
BHGX_HD_API int __stdcall iAppendRec(unsigned char *pKey, const unsigned char *pBuf, unsigned long buflen);
BHGX_HD_API int __stdcall iSignRec(unsigned char *pKey, int  iRecNo, int  sign);
BHGX_HD_API int __stdcall iIOCtl(int cmd, void *data, int datasize);
BHGX_HD_API int __stdcall ICCSet(unsigned int  iCardSet, unsigned char *pCardType, unsigned char *pRet);
BHGX_HD_API int __stdcall iUCardAuthSys(int  iKeyID);
BHGX_HD_API int __stdcall iSelectFile(unsigned char  iCardType, unsigned char  *pInFID);
BHGX_HD_API int __stdcall iGetRandom(unsigned char  iCardType, unsigned char  iRndLen, unsigned char  * pOutRnd);
BHGX_HD_API int __stdcall iChangePwdEx(const unsigned char * pNewKeyA, const unsigned char * ctrlword,	const unsigned char * pNewKeyB, const unsigned char * poldPin,  unsigned char nsector, unsigned char keyA1B0, unsigned char changeflag);

#endif


