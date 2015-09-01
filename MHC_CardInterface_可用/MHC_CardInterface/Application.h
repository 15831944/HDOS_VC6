/************************************************************************/
/* ��ԿID ����                                                                     */
/************************************************************************/
#define RK_DDF1		0
#define RK_DF01		1
#define RK_DF02		2
#define RK_DF03		3

#define STK_DDF1	4
#define STK_DF01	5
#define STK_DF02	6
#define STK_DF03	7

#define UK_DDF1		8
#define UK_DF01		9
#define UK_DF02_1		10
#define UK_DF02_2		11
#define UK_DF02_3		12
#define UK_DF03_1		13
#define UK_DF03_2		14


/************************************************************************/
/*  ��������ֵ����                                                      */
/************************************************************************/
#define IRV_OK			0			//����
#define IRV_PARA_ERR	101			//���������
#define IRV_NO_FILE	    102			//�ļ�������
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

//#define 

#define IRV_DEBUGERR    1024

/************************************************************************/
/* Ӧ�ó�������                                                         */
/************************************************************************/
#define NO_style			0x00

#define AN_style			0x01
#define CN_style			0x0F
#define B_style				0xFF

#define SLOT_USER			0x01
#define SLOT_PSAM			0x11
#define SLOT_CARD			0x12	/*�����ô���*/


#include "Utils.h"
#include "Reader.h"

typedef struct st_itemselect_
{
	WORD	wItemFlag;				  // ���������
	WORD	wID;					  // ��¼�ļ�ID
	VOID	*pValue;				  // ���ݵ�ַ 
	WORD	wValueLen;				  // ���ݳ���
	DWORD	*pdwErrCode;	
}ITEMSELECT, *P_ITEMSELECT;	


static Reader rd ;
static Utils u;

void datatoTLV(char tag , IN char * data , OUT char* Output);
void tlvRespToOutput(int coding , IN char * resp , OUT char* Ouput);
void Padding(IN char * data);

int SelectFile(int slot , char * DFID , char * ADFID, char * EFID);

int AuthIRK(IN int KeyID , IN char * cardNo , IN char * cityCode);
int AuthUK(IN int KeyID , IN char * cardNo , IN char * cityCode);

int GetCNandCityCode(OUT char* Cn , OUT char* CityCode);
void loadCardNo(char * atr);
void loadCityCode(char * cityCode);

int UpdateBinEncMac(IN int keyID ,IN char * apduHead , IN char *LcData );
int UpdateRecEncMac(IN int keyID ,IN char * RecID,IN char* Lc, IN int datatag,  IN char *LcData );
int PSAMEncMac(IN int keyID ,IN char * divGene, IN char* apduHead , IN char *LcData , OUT char * compApdu);
int getUpdateACCbyADF(WORD itemID, char * cardno , char * citycode);


/************************************************************************/
/* wscӦ�ú���                                                         */
/************************************************************************/
BOOL isWorkingDFID(char * DFID);
BOOL isWorkingEFID(char * EFID);
BOOL getDFEFfromFILEMAP( IN P_ITEMSELECT item, OUT char * DFID ,OUT char * EFID);
int getReadACCbyADF(char* adfid , char * cardno , char * citycode);
int RdFileByItemStruct(P_ITEMSELECT pitem);
int UdFileByItemStruct(P_ITEMSELECT pitem);

void BinDataPadding(int coding ,char * data, int ExpLen);
void resetWorkingADF();




/************************************************************************/
/* ����tag����                                                          */
/************************************************************************/
#define TAG_KLB	    1  //����� 
#define TAG_GFBB	2  //�淶�汾
#define TAG_FKJGMC	3  //������������
#define TAG_FKJGDM	4  //������������
#define TAG_FKJGZS	5  //��������֤��
#define TAG_FKSJ	6  //����ʱ��
#define TAG_KH      8  //����
#define TAG_AQM     9  //��ȫ��
#define TAG_XPXLH	10  //�������к�
#define TAG_YYCSDM	57  //Ӧ�ó��д���

#define TAG_KYXQ	07  //����Ч�� 
#define TAG_XM		11  //���� 
#define TAG_XB		12  //�Ա� 
#define TAG_MZDM	13  //������� 
#define TAG_CSRQ	14  //�������� 
#define TAG_JMSFZH	15  //�������֤���� 
#define TAG_BRDH1	16  //���˵绰 1 
#define TAG_BRDH2	17  //���˵绰 2 
#define TAG_YLFYZF1	18  //ҽ�Ʒ���֧����ʽ 
#define TAG_YLFYZF2	19  //ҽ�Ʒ���֧����ʽ 
#define TAG_YLFYZF3	20  //ҽ�Ʒ���֧����ʽ 
#define TAG_DZLB1	21  //��ַ��� 1 
#define TAG_DZ1		22  //��ַ 1 
#define TAG_DZLB2	23  //��ַ��� 2 
#define TAG_DZ2		24  //��ַ 2 
#define TAG_LXRXM1	25  //��ϵ������1
#define TAG_LXRGX1	26  //��ϵ�˹�ϵ1 
#define TAG_LXRDH1	27  //��ϵ�˵绰1 
#define TAG_LXRXM2	28  //��ϵ������2 
#define TAG_LXRGX2	29  //��ϵ�˹�ϵ2 
#define TAG_LXRDH2	30  //��ϵ�˵绰2 
#define TAG_LXRXM3	31  //��ϵ������3 
#define TAG_LXRGX3	32  //��ϵ�˹�ϵ3 
#define TAG_LXRDH3	33  //��ϵ�˵绰3 
#define TAG_WHCD	34  //�Ļ��̶ȴ��� 
#define TAG_HYZK	35  //����״������ 
#define TAG_ZYDM	36  //ְҵ���� 
#define TAG_ZJLB	37  //֤����� 
#define TAG_ZJHM	38  //֤������ 
#define TAG_JKDABH	39  //����������� 
#define TAG_XNHZH	40  //��ũ��֤�������� 
#define TAG_ABOXX	41  //ABOѪ�ʹ��� 
#define TAG_RHXX	42  //RH Ѫ�ʹ��� 
#define TAG_XCBZ	43  //������־ 
#define TAG_XZBBZ	44  //���ಡ��־ 
#define TAG_XNXGBBZ	45  //����Ѫ�ܲ���־ 
#define TAG_DXBBZ	46  //��ﲡ��־ 
#define TAG_NXWLBZ	47  //��Ѫ���ұ�־ 
#define TAG_TNBBZ	48  //���򲡱�־ 
#define TAG_QGYBZ	49  //����۱�־ 
#define TAG_TXBZ	50  //͸����־ 
#define TAG_QGYZBZ	51  //������ֲ��־ 
#define TAG_QGQSBZ	52  //����ȱʧ��־ 
#define TAG_KZXYZBZ	53  //��װж����֫��־ 
#define TAG_XZQBQBZ	54  //����������־ 
#define TAG_QTYXJS	55  //����ҽѧ��ʾ���� 
#define TAG_JSBBZ	56  //���񲡱�־ 


/*����ṹ��struct ����tcl*/
struct _DATATCL 
{
	char tag;	/*tag*/
	UINT  coding; /*����*/
	UINT  length; /*����*/
}static _stTCL[]={
{01,10,1},
{TAG_KLB,  AN_style,1},
{TAG_GFBB,  AN_style,4},
{TAG_FKJGMC,  AN_style,30},
{TAG_FKJGDM,  CN_style,11},
{TAG_FKJGZS,  B_style,180},
{TAG_FKSJ,  CN_style,4},/*0~6*/
{TAG_KYXQ ,  CN_style, 4},
{TAG_KH,  AN_style,18},
{TAG_AQM,  AN_style,3},
{TAG_XPXLH,  AN_style,10},/*8~10*/
{TAG_XM ,  AN_style , 30},
{TAG_XB ,  B_style , 1},
{TAG_MZDM	  ,CN_style, 1},
{TAG_CSRQ	  ,CN_style, 4},
{TAG_JMSFZH ,AN_style, 18},
{TAG_BRDH1	,AN_style, 20},
{TAG_BRDH2	,AN_style, 20},
{TAG_YLFYZF1 ,CN_style, 1},
{TAG_YLFYZF2 ,CN_style, 1},
{TAG_YLFYZF3 ,CN_style, 1},
{TAG_DZLB1	,CN_style, 1},
{TAG_DZ1	,AN_style, 100},
{TAG_DZLB2	,CN_style, 1},
{TAG_DZ2	,AN_style, 100},//��ַ2                        
{TAG_LXRXM1 ,AN_style, 30},
{TAG_LXRGX1 ,CN_style, 1},
{TAG_LXRDH1 ,AN_style, 20},
{TAG_LXRXM2 ,AN_style, 30},
{TAG_LXRGX2 ,CN_style, 1},
{TAG_LXRDH2 ,AN_style, 20},
{TAG_LXRXM3 ,AN_style, 30},
{TAG_LXRGX3 ,CN_style, 1},
{TAG_LXRDH3 ,AN_style, 20},
{TAG_WHCD	  ,CN_style, 1},
{TAG_HYZK	  ,CN_style, 1},
{TAG_ZYDM	  ,AN_style, 3},
{TAG_ZJLB	  ,CN_style, 1},
{TAG_ZJHM	  ,AN_style, 18},
{TAG_JKDABH ,AN_style, 17},
{TAG_XNHZH	,AN_style, 18},
{TAG_ABOXX	,B_style, 1},
{TAG_RHXX	  ,CN_style, 1},
{TAG_XCBZ	  ,B_style, 1},
{TAG_XZBBZ	,B_style, 1},
{TAG_XNXGBBZ ,B_style,1 },
{TAG_DXBBZ	,B_style, 1},
{TAG_NXWLBZ ,B_style, 1},
{TAG_TNBBZ	,B_style, 1},
{TAG_QGYBZ	,B_style, 1},
{TAG_TXBZ	  ,B_style, 1},
{TAG_QGYZBZ ,B_style, 1},
{TAG_QGQSBZ ,B_style, 1},
{TAG_KZXYZBZ ,B_style, 1},
{TAG_XZQBQBZ ,B_style, 1},
{TAG_QTYXJS ,AN_style, 40},
{TAG_JSBBZ	,B_style, 1},
{TAG_YYCSDM	,CN_style, 3}
};
