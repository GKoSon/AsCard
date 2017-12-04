#include "reader.h"
#include <QMessageBox>
#include <cstring>
char Is_AYmark=0;
Reader::Reader()
{
    DeviceAddress = 0;
    ADDA=0;
    ADDB=0;
    functionLib = new QLibrary("function.dll");

    defaultKeyA[0] = 0x41;
    defaultKeyA[1] = 0x31;
    defaultKeyA[2] = 0x53;
    defaultKeyA[3] = 0x4d;
    defaultKeyA[4] = 0x31;
    defaultKeyA[5] = 0x50;
    defaultKeyB[0] = 0xFF;
    defaultKeyB[1] = 0xFF;
    defaultKeyB[2] = 0xFF;
    defaultKeyB[3] = 0xFF;
    defaultKeyB[4] = 0xFF;
    defaultKeyB[5] = 0xFF;
}

Reader::~Reader()
{
    CloseDll();
}

bool Reader::LoadDll()
{
	if ( !functionLib->load() )
	{
		qDebug()<<"Failed to load function.dll";
		return false;
	}
	
	qDebug()<<"Succeed to load function.dll";

	//14443A-MF
	MF_Read        = (MF_Read_Func)functionLib->resolve("MF_Read");
	MF_Write       = (MF_Write_Func)functionLib->resolve("MF_Write");
	MF_InitValue   = (MF_InitValue_Func)functionLib->resolve("MF_InitValue");
	MF_Dec         = (MF_Dec_Func)functionLib->resolve("MF_Dec");
	MF_Inc         = (MF_Inc_Func)functionLib->resolve("MF_Inc");
	MF_Halt        = (MF_Halt_Func)functionLib->resolve("MF_Halt");
        MF_Getsnr      = (MF_Getsnr_Func)functionLib->resolve("MF_Getsnr");

	//System Setting
	ControlLED           = (ControlLED_Func)functionLib->resolve("ControlLED");
        ControlBuzzer        = (ControlBuzzer_Func)functionLib->resolve("ControlBuzzer");
	GetVersionNum        = (GetVersionNum_Func)functionLib->resolve("GetVersionNum");
        SetSerNum            = (SetSerNum_Func)functionLib->resolve("SetSerNum");
	GetSerNum            = (GetSerNum_Func)functionLib->resolve("GetSerNum");

	//14443 B
	TypeB_Request        = (TypeB_Request_Func)functionLib->resolve("TypeB_Request");
        TYPEB_SFZSNR         = (TYPEB_SFZSNR_Func)functionLib->resolve("TYPEB_SFZSNR");
        TypeB_TransCOS       = (TypeB_TransCOS_Func)functionLib->resolve("TypeB_TransCOS");

	//ISO15693
        ISO15693_Inventory		= (ISO15693_Inventory_Func)functionLib->resolve("ISO15693_Inventory");
        ISO15693_Read			= (ISO15693_Read_Func)functionLib->resolve("ISO15693_Read");
	ISO15693_Write			= (ISO15693_Write_Func)functionLib->resolve("ISO15693_Write");
	ISO15693_GetSysInfo		= (ISO15693_GetSysInfo_Func)functionLib->resolve("ISO15693_GetSysInfo");
	ISO15693_Lock			= (ISO15693_Lock_Func)functionLib->resolve("ISO15693_Lock");
	ISO15693_Select			= (ISO15693_Select_Func)functionLib->resolve("ISO15693_Select");
	ISO15693_WriteAFI		= (ISO15693_WriteAFI_Func)functionLib->resolve("ISO15693_WriteAFI");
	ISO15693_LockAFI		= (ISO15693_LockAFI_Func)functionLib->resolve("ISO15693_LockAFI");
	ISO15693_WriteDSFID		= (ISO15693_WriteDSFID_Func)functionLib->resolve("ISO15693_WriteDSFID");
	ISO15693_LockDSFID		= (ISO15693_LockDSFID_Func)functionLib->resolve("ISO15693_LockDSFID");
	ISO15693_GetMulSecurity = (ISO15693_GetMulSecurity_Func)functionLib->resolve("ISO15693_GetMulSecurity");

	//Ultralight
        UL_Request           = (UL_Request_Func)functionLib->resolve("UL_Request");
	UL_HLRead            = (UL_HLRead_Func)functionLib->resolve("UL_HLRead"); 
        UL_HLWrite           = (UL_HLWrite_Func)functionLib->resolve("UL_HLWrite");

        if(//14443A
            MF_Read      == NULL	||
	    MF_Write	 == NULL	||
	    MF_InitValue == NULL	||
            MF_Dec	 == NULL	||
            MF_Inc	 == NULL	||
	    MF_Getsnr	 == NULL	||
            MF_Halt	 == NULL	||

           //System Setting
	    SetSerNum		== NULL	||
	    GetSerNum		== NULL	||
            ControlLED		== NULL	||
	    ControlBuzzer	== NULL	||
	    GetVersionNum	== NULL	||

          //14443B
	    TypeB_Request	== NULL	||
	    TYPEB_SFZSNR	== NULL	||
	    TypeB_TransCOS	== NULL ||

         //ISO15693
   	    ISO15693_Inventory	== NULL ||
            ISO15693_Read	== NULL	||
            ISO15693_Write	== NULL ||
	    ISO15693_GetSysInfo == NULL ||
            ISO15693_Lock	== NULL ||
            ISO15693_Select	== NULL ||
            ISO15693_WriteAFI	== NULL ||
            ISO15693_LockAFI	== NULL ||
            ISO15693_WriteDSFID	== NULL ||
            ISO15693_LockDSFID	== NULL ||

		//Ultralight
	    UL_Request == NULL  ||
	    UL_HLRead  == NULL  ||
	    UL_HLWrite == NULL)
	{
		qDebug()<<"Failed to resolve function";
		return false;
	}
         qDebug()<<"Succeed to resolve function";
  return true;
}

bool Reader::CloseDll()
{
    if(functionLib)
    {
            functionLib->unload();
            return true;
    }
    return false;
}
/*����ƶ������Կ ��ȷ����1���󷵻�0*/
bool Reader::checkKey(unsigned char blkAddr, unsigned char *key)
{
    unsigned char  mode;
    unsigned char  blkAdd;
    unsigned char  blkNum;
    unsigned char  snr[6];
    unsigned char *buffer;
    int            result;
    buffer = new unsigned char[16];

    mode   = 0x00;
    blkAdd = blkAddr;
    blkNum = 1;
    memcpy(snr, key, 6);

    qDebug() << "checkkey������Ч����Կ";
    result = MF_Read(mode,blkAdd,blkNum,snr,buffer);
    if(!result)
        {
        qDebug() << "checkkey������Ч����Կ�ɹ�";
        return true;
        }
    else
       {
        qDebug()<<"checkkey������Ч����Կʧ��";
        return false;
       }
}
/*��ȡָ��������ݣ�������ȫ����ȡ��������*/
bool Reader::readOneBlk(unsigned char blkAddr, unsigned char *dataBuffer)
{
    unsigned char  mode;
    unsigned char  blkAdd;
    unsigned char  blkNum;
    unsigned char  snr[6];
    int            result;

    mode   = 0x00;
    blkAdd = blkAddr;
    blkNum = 1;
    memcpy(snr, defaultKey, 6);

    qDebug() << "read one block";
    result = MF_Read(mode,blkAdd,blkNum,snr,dataBuffer);
    if(!result)
        return true;
    else
    {
        qDebug()<<"A key fail   Try FFFFFFFFFFFF";
     //   memcpy(snr, defaultKeyB, 6);
      //  result = MF_Read(mode,blkAdd,blkNum,snr,dataBuffer);
      //  if(!result)
     //   {
     //       qDebug()<<"B��Կ�ɹ�";
     //       return true;
     //   }
     //   else
        qDebug()<<"����A��ԿB��Կ��ʧ��";
        return false;
    }
}

/*ȫ��������*/
bool Reader::readAllBlk()
{
    bool result;

    defaultKey = defaultKeyA;

    result = readOneBlk(9, CardNumber);
    if(!result)
        return false;
        return true;
}
/*�޸��ƶ������Կ ������ȫ���޸ĺ�������*/
bool Reader::modifyKeyToDefaultOneBlk(unsigned char blkAddr)
{
    unsigned char  mode;
    unsigned char  blkAdd;
    unsigned char  blkNum;
    unsigned char *buffer;
    unsigned char  snr[6];
    int            result;
    buffer   = new unsigned char[16];

    mode   = 0x00;
    blkAdd = blkAddr;
    blkNum = 1;
    memcpy(snr, defaultKeyB, 6);

    *(buffer + 0)  = defaultKeyA[0];
    *(buffer + 1)  = defaultKeyA[1];
    *(buffer + 2)  = defaultKeyA[2];
    *(buffer + 3)  = defaultKeyA[3];
    *(buffer + 4)  = defaultKeyA[4];
    *(buffer + 5)  = defaultKeyA[5];
    *(buffer + 6)  = 0xFF;
    *(buffer + 7)  = 0x07;
    *(buffer + 8)  = 0x80;
    *(buffer + 9)  = 0x69;
    *(buffer + 10) = defaultKeyB[0];
    *(buffer + 11) = defaultKeyB[1];
    *(buffer + 12) = defaultKeyB[2];
    *(buffer + 13) = defaultKeyB[3];
    *(buffer + 14) = defaultKeyB[4];
    *(buffer + 15) = defaultKeyB[5];

    qDebug() << "׼���޸���Կ";
    result = MF_Write(mode,blkAdd,blkNum,snr,buffer);
    if(result)
    {
         qDebug() << "�޸���Կʧ��";
        return false;
    }

    qDebug() << "�޸���Կ�ɹ�";
    return true;
}
/*�޸�ȫ����Կ*/
bool Reader::modifyKeyToDefaultAllBlk()
{
    for(int i = 9; i <= 11; i+=2)
    {
        qDebug() << "�޸ĵ�һ��";
        if(!modifyKeyToDefaultOneBlk(i))//3 7 11 15
        {
            return false;
        }
    }
    return true;
}








/*дһ��ָ���� ������ȫ��д��������*/
bool Reader::writeOneBlk(unsigned char blkAddr, unsigned char *dataBuffer)
{
    unsigned char  mode;
    unsigned char  blkAdd;
    unsigned char  blkNum;
    unsigned char  snr[6];
    int            result;

    mode   = 0x00;
    blkAdd = blkAddr;
    blkNum = 1;
    memcpy(snr, defaultKey, 6);

    qDebug()<<"write one block";
    result = MF_Write(mode,blkAdd,blkNum,snr,dataBuffer);

    if(!result)
    {
        qDebug() << "Write a block successfully!";
        return true;
    }
    else
    {
        qDebug()<<"д��A��Կ���󣬳�����ԿB";
        memcpy(snr, defaultKeyB, 6);
        result = MF_Write(mode,blkAdd,blkNum,snr,dataBuffer);
        if(!result)
        {
            qDebug()<<"B��Կ�ɹ�";
            return true;
        }
        else
        qDebug()<<"д��A��ԿB��Կ��ʧ��";
        return false;
    }
}


/*ȫ��д���� �Ǿ����ڽ����׮�����������鸳ֵ��*/
bool Reader::writeAllBlk()
{
    bool result;
    qDebug() << "׼��ȥcheckkey����Ч��ģʽ�ǲ���41 31 53 4d 31 50";

   unsigned char defaultKeyAY[6]={0x01,0x0e,0x19,0x23,0x1a,0x1b};/*01 0e 19 23 1a 1b*/
	result = checkKey(7,defaultKeyAY);
	if(result)
		{
	           qDebug() << "AY card";
		   Is_AYmark=1;
                   return false;
	         }
    result = checkKey(11, defaultKeyA);
    if(result)
    {
        qDebug() << "checkkey���������������41 31 53 4d 31 50";
        defaultKey = defaultKeyA;
    }
    else
    {
        qDebug() << "׼��ȥcheckkey����Ч��ģʽ�ǲ���FF FF FF FF FF FF";
        result = checkKey(11, defaultKeyB);
        if(result)
        {
            qDebug() << "checkkey��������������FF FF FF FF FF FF���ڿ�ʼ�޸���Կ";
            defaultKey = defaultKeyB;
            result = modifyKeyToDefaultAllBlk();
            if(!result)
                return false;
            else
                defaultKey = defaultKeyA;
        }
        else
        {
            qDebug() << "checkkey�����������벻��41 31 53 4d 31 50Ҳ����FF FF FF FF FF FF";
            return false;
        }
    }
    if(CardNumber[0]==0x12&&
       CardNumber[1]==0x34&&
       CardNumber[2]==0x56&&
       CardNumber[3]==0x78&&
       CardNumber[4]==0xED&&
       CardNumber[5]==0xCB)
    result = writeOneBlk(9, CardNumber);
    else
    {
        PtoC_Conversion();/*׮��ת����*/
        result = writeOneBlk(9, CardNumber);/*��ʵд�뿨*/
    }
    if(!result)
        return false;
    return true;
}

void Reader::PtoC_Conversion(void)
{
    memset(CardNumber,0,13);
    memcpy(CardNumber,PileNumber,13);
    CardNumber[13]='0'+ADDA;
    CardNumber[14]='0'+ADDB;
    CardNumber[15]=0;/*'0'�Ļ���ʵ��ʵ������0  ���ھ���0  ��Ҫ����0*/

}
void Reader::CtoP_Conversion(void)
{
    memset(PileNumber,0,13);
    memcpy(PileNumber,CardNumber,13);
}
