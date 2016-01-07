#ifndef HD_HDRWINTERFACE_H
#define HD_HDRWINTERFACE_H

#define HD_HDRWINTERFACE_API extern "C" __declspec(dllexport)

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

HD_HDRWINTERFACE_API BOOL __stdcall bProbe(void);
HD_HDRWINTERFACE_API int __stdcall iOpen(void);
HD_HDRWINTERFACE_API int __stdcall iClose(void);
HD_HDRWINTERFACE_API int __stdcall test(void);

#endif


