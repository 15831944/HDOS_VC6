// HD_RWHealInterface.h : main header file for the HD_RWHEALINTERFACE DLL
//
#if !defined(AFX_HD_RWHEALINTERFACE_H__ECF36EDA_9730_46D9_8146_0BEF432004DC__INCLUDED_)
#define AFX_HD_RWHEALINTERFACE_H__ECF36EDA_9730_46D9_8146_0BEF432004DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define MHC_CARDINTERFACE_API  extern "C" __declspec(dllexport)

#define IFD_OK	0					 //ִ�гɹ�
#define IFD_ICC_TypeError	-1		 //��Ƭ���Ͳ���
#define IFD_ICC_NoExist	-2			 //�޿�
#define IFD_ICC_NoPower	-3			 //�п�δ�ϵ�
#define IFD_ICC_NoResponse	-4	     //��Ƭ��Ӧ��
#define IFD_ConnectError	-11	     //���������Ӵ�
#define IFD_UnConnected	-12	         //δ��������(û��ִ�д��豸����)
#define IFD_BadCommand	-13	         //(��̬��)��֧�ָ�����
#define IFD_ParameterError	-14	     //(������̬���)���������
#define IFD_CheckSumError	-15	     //��ϢУ��ͳ���
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
#define OPEN_FILE_ERR	116      // ����Ƭ�ļ�������
#define CANT_FINDWEB	117      // �Ҳ�����ҳ
#define HTTP_EXCEPTION	118      // http�쳣
#define PROCCESS_EXIST  119      //δ�򿪿�������
#define HTTP_EXCEPTION1 1001	//ȱ���˺Ż�Ϊ��
#define HTTP_EXCEPTION2 1002	//ȱ�������Ϊ��
#define HTTP_EXCEPTION3 1003	//�����֤ʧ��
#define HTTP_EXCEPTION4 2001	//ȱ�ٽ��������к�
#define HTTP_EXCEPTION5 2002	//��ȫ��֤��ѯ���������Ƿ�����
#define HTTP_EXCEPTION6 2003	//���Ѿ���ʧ
#define HTTP_EXCEPTION7 2004	//���Ѿ�ע��
#define HTTP_EXCEPTION8 3001	//��������
#define HTTP_EXCEPTION9 3002	//�������ʶ���ѯ���������Ƿ�����
#define HTTP_EXCEPTIONA 4001	//ȱ��SAM����
#define HTTP_EXCEPTIONB 4002	//SAM�����Ѷ���
#define HTTP_EXCEPTIONC 4003	//SAM������ע��
#define HTTP_EXCEPTIOND 4004	//SAM�����ѹ�ʧ
#define HTTP_EXCEPTIONE 4005	//SAM��������
#define HTTP_EXCEPTIONF 5001	//û�п����޸ĵ�����
#define HTTP_EXCEPTIONG 5002	//Ŀ���ʽ����ȷ
#define HTTP_EXCEPTIONH 6001	//ȱ�ٻ��ߺ�
#define HTTP_EXCEPTIONI 6002	//�����Ѷ���
#define HTTP_EXCEPTIONJ 6003	//������ע��
#define HTTP_EXCEPTIONK 6004	//�����ѹ�ʧ
#define HTTP_EXCEPTIONL 6005	//���߲�����
#define HTTP_EXCEPTIONM 7001	//������SAM����ƥ��

#define NO_style			0x00

#define AN_style			0x01
#define CN_style			0x0F
#define B_style				0xFF

#define SLOT_USER			0x01
#define SLOT_PSAM			0x11
#define SLOT_CARD			0x12	
MHC_CARDINTERFACE_API int __stdcall IChange_Pin(int hDev,char *oldPin,char *newPin); //�޸�PIN
MHC_CARDINTERFACE_API int __stdcall IR_ReadCard(char *para,char *dataOut,char *account,char *password,int doctype,char *userid,char *pin);
MHC_CARDINTERFACE_API int __stdcall IR_WriteCard(char *para,char *dataIn,char *account,char *password,int doctype,char *userid,char *pin);

#endif // !defined(AFX_HD_RWHEALINTERFACE_H__ECF36EDA_9730_46D9_8146_0BEF432004DC__INCLUDED_)
