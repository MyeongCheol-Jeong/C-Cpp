// Gloval Library Header

#ifndef __LIB_H__
#define __LIB_H__

#pragma warning(disable : 4996)

class CLib
{
public:
	static BOOL IsSet(BYTE Byte, int nPos);
	static BOOL IsSet(WORD Word, int nPos);
	static BOOL IsSet(UINT Int, int nPos);

	static int Power(int x, int y);
	static int HexToInt(BYTE bHex);
	static void ConvertAscToHex(char* pOrg, char* pDest);
	static int ConvertHexStr2HexValue(char *strHex, int nLen);
	static BOOL ConvertFloatStrToCustom(CString strFloat, char *pDest, int nTotalLen, int nPrecision);
	static void HexStr2Word(BYTE *bySrc, WORD *byDest);
	static void HexStr1Word(BYTE *bySrc, BYTE *byDest);
	static void HexStr1Byte(BYTE *bySrc, BYTE *byDest);
	static WORD HexStrToWORD(BYTE *bySrc);
	static BYTE HexStrToBYTE(BYTE *bySrc);
	static CString HexToString(BYTE * bySrc , int nSize);
	static void Int2HexaStr(BYTE *bySrc, BYTE *byDest);


	static CString GetSystemErrMsg(int nErrNo=0);

	static BOOL IsBitRead(BYTE Byte, BOOL bHigh);

	static CString TimeToStr (CTime Time, int Type =0);

	static CString IntToStr(int nData)
	{
		CString temp;	
		temp.Format("%d", nData);

		return temp;
	}

	static CString DoubleToStr(double dbData, int nLen=3)
	{
		CString temp;
		temp.Format("%.*lf", nLen, dbData);

		return temp;
	}
	static CString LongToStr(long dbData, int nLen=3)
	{
		CString temp;
		temp.Format("%.*d", nLen, dbData);

		return temp;
	}

	static CString FloatToStr(float fData, int nLen=3)
	{
		CString temp;
		temp.Format("%.*f", nLen, fData);

		return temp;
	}

	static CString HexaToStr(UINT32 uHexaData, int nLen=4)
	{
		CString temp;
		temp.Format("0x%0*X", nLen, uHexaData);

		return temp;
	}

	static char * IntToHexaStr(int nValue, int nLen,char *dest)
	{
		sprintf(dest, _T("%0*X"), nLen, nValue);
		return dest;
	}

	static long StrToInt(CString str)
	{
		long lRet = (long)atoi(str.operator LPCTSTR());

		return lRet;
	}

	static double StrToDouble(CString str)
	{
		double dRet = (double)atof(str.operator LPCTSTR());

		return dRet;
	}
	static double szToDouble(UCHAR *ucBuf,int nSize)
	{

		double dDest = 0;
		for (int i=0; i<nSize; i++)
		{
			if (ucBuf[i] >= '0' && ucBuf[i] <= '9')
				dDest += ucBuf[i] - '0';
			else
				dDest += ucBuf[i] - 'A' + 10;

			if(i!=nSize-1) dDest *= 16;
		}

		return dDest;
	}

	static UINT32 StrToHexa(CString str)
	{
		char strTemp[MAX_PATH];
		UINT32	uRet = 0;

		strcpy(strTemp, str.operator LPCTSTR());
		sscanf(strTemp, "%X", &uRet);
		
		return uRet;
	}

	static BOOL CompareMemory(void FAR *pSrc1, void FAR *pSrc2, long lSize)
	{
		BOOL bRet = TRUE;
			
		BYTE *pbySrc1 = (BYTE *)pSrc1;
		BYTE *pbySrc2 = (BYTE *)pSrc2;

		for ( long i = 0; i < lSize; i++ )
		{
			if ( pbySrc1[i] != pbySrc2[i] )
			{
				bRet = FALSE;
				break;
			}
		}

		return bRet;
	}

	static int pre_macro_date_to_int(const char *str_pre_macro_date) 
	{     
		const int comfile_date_len = 12;
		// error check     
		if (NULL == str_pre_macro_date || comfile_date_len - 1 != strlen(str_pre_macro_date))
			return 0;
		const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
		char s_month[5] = {0,};
		int iyear = 0, iday = 0;
		sscanf_s(str_pre_macro_date, "%s %d %d", s_month, _countof(s_month) , &iday, &iyear);
		int imonth = (strstr(month_names, s_month) - month_names) / 3 + 1;
		// 2010 12 01     
		return 10000 * iyear + 100*imonth + iday; 
	}   // timeÀ» int·Î 

	static int pre_macro_time_to_int(const char *str_pre_macro_time) 
	{     
		const int comfile_time_len = 9;
		if (NULL == str_pre_macro_time || comfile_time_len -1 != strlen(str_pre_macro_time))
			return 0;
		int ihour = 0, iminute = 0, isec = 0;
		sscanf_s(str_pre_macro_time, "%d:%d:%d", &ihour, &iminute, &isec);
		// 030511
		return ihour * 10000 + iminute * 100 + isec; 
	} 


};

class CConversion
{
public:

	static CString IntToStr(int nData)
	{
		CString temp;
		temp.Format(_T("%d"), nData);

		return temp;
	}

	static CString DoubleToStr(double dbData, int nLen=3)
	{
		CString temp;
		temp.Format(_T("%.*lf"), nLen, dbData);

		return temp;
	}
	static CString LongToStr(long dbData, int nLen=3)
	{
		CString temp;
		temp.Format(_T("%.*d"), nLen, dbData);

		return temp;
	}

	static CString FloatToStr(float fData, int nLen=5)
	{
		CString temp;
		temp.Format(_T("%.*f"), nLen, fData);

		return temp;
	}

	static CString HexaToStr(UINT32 uHexaData, int nLen=4)
	{
		CString temp;
		temp.Format(_T("%0*X"), nLen, uHexaData);
		temp = temp.Right(2);

		return temp;
	}


	static long StrToInt(CString str)
	{
		long lRet = (long)atoi(str.operator LPCTSTR());

		return lRet;
	}

	static double StrToDouble(CString str)
	{
		double dRet = (double)atof(str.operator LPCTSTR());

		return dRet;
	}
	static float StrToFloat(CString str)
	{
		float dRet = (float)atof(str.operator LPCTSTR());

		return dRet;
	}

	static UINT32 StrToHexa(CString str)
	{
		char strTemp[MAX_PATH];
		UINT32	uRet = 0;

		strcpy(strTemp, str.operator LPCTSTR());
		sscanf(strTemp, "%X", &uRet);
		
		return uRet;
	}

	static BOOL CompareMemory(void FAR *pSrc1, void FAR *pSrc2, long lSize)
	{
		BOOL bRet = TRUE;
			
		BYTE *pbySrc1 = (BYTE *)pSrc1;
		BYTE *pbySrc2 = (BYTE *)pSrc2;

		for ( long i = 0; i < lSize; i++ )
		{
			if ( pbySrc1[i] != pbySrc2[i] )
			{
				bRet = FALSE;
				break;
			}
		}

		return bRet;
	}
	static BYTE * BYTE_Xor(BYTE * m_byte ,int m_size,int * totalsize)
	{
		int counter= 0;
		int i;
		for (i =0 ; i<m_size ; i++){
			if(m_byte[i]== 0x7D || m_byte[i] == 0xAA || m_byte[i]== 0x7E){
				counter++;
			}
		}
		if (counter==0){
			*totalsize = m_size;
			return m_byte;
		}
		m_size ;
		BYTE * m_tbyte = new BYTE[m_size+ counter];
		*totalsize = m_size + counter;
		int j =0;
		
		for(i=0;i<m_size;i++){
			if(m_byte[i]== 0x7D || m_byte[i] == 0xAA || m_byte[i]== 0x7E){
				m_tbyte[j++]= 0x7D;
				m_tbyte[j++] = 0x20 ^m_byte[i];
			}else {
				m_tbyte[j++] = m_byte[i];
			}

		}
		return m_tbyte;
	}

	static BYTE * Xor_BYTE(BYTE * s_buf , int s_size , int * d_size)
	{
		int i =0;
		int j =0;
		int coun=0;
		BYTE * d_buf;
		d_buf = new BYTE[s_size];
		unsigned  char temp;
		for (i=0;i<s_size;i++){
			if(s_buf[i]!=0x7d){
				coun ++;
			}
		}
		for (i=0;i<coun;i++)
		{
			if(s_buf[j]==0x7d){
				temp =s_buf[j+1];
				temp = temp ^ 0x20;
				d_buf[i]=temp;
				j++;
				j++;
			}else{
				d_buf[i] = s_buf[j++];
			}
		}

		*d_size = coun;
		return d_buf;
	}

	static BYTE ChkSum(BYTE * buf,int m_size){
		int i=0;
		BYTE chk=0;
		for(i=1;i<(m_size-2);i++){
			chk = chk + buf[i];
		}
		return chk;		
	}

	static void  HtoA (unsigned Hex,unsigned char *Ascii)
	{
	   char  Table[] = "0123456789ABCDEF";

	   *Ascii++ = Table[(Hex & 0xf0000000) >> 28];
	   *Ascii++ = Table[(Hex & 0xf000000) >> 24];
	   *Ascii++ = Table[(Hex & 0xf00000) >> 20];
	   *Ascii++ = Table[(Hex & 0xf0000) >> 16];
	   *Ascii++ = Table[(Hex & 0xf000) >> 12];
	   *Ascii++ = Table[(Hex & 0xf00) >> 8];
	   *Ascii++ = Table[(Hex & 0xf0) >> 4];
	   *Ascii = Table[Hex & 0xf];
	}

	static void  HtoA (int Hex, unsigned char *Ascii)
	{
	   char  Table[] = "0123456789ABCDEF";

	   *Ascii++ = Table[(Hex & 0xf000) >> 12];
	   *Ascii++ = Table[(Hex & 0xf00) >> 8];
	   *Ascii++ = Table[(Hex & 0xf0) >> 4];
	   *Ascii = Table[Hex & 0xf];
	}

	static void  HtoA (int Hex, unsigned char *Ascii, int Count)
	{
	   char  Table[] = "0123456789ABCDEF";

	   if(Count == 0)
	   {
		   *Ascii++ = Table[(Hex & 0xf000) >> 12];
		   *Ascii++ = Table[(Hex & 0xf00) >> 8];
		   *Ascii++ = Table[(Hex & 0xf0) >> 4];
		   *Ascii = Table[Hex & 0xf];
	   }
	   else if(Count == 3)
	   {
		   *Ascii++ = Table[(Hex & 0xf00) >> 8];
		   *Ascii++ = Table[(Hex & 0xf0) >> 4];
		   *Ascii = Table[Hex & 0xf];
	   }
	   else if(Count == 5)
	   {
		   *Ascii++ = Table[(Hex & 0xf0000) >> 16];
		   *Ascii++ = Table[(Hex & 0xf000) >> 12];
		   *Ascii++ = Table[(Hex & 0xf00) >> 8];
		   *Ascii++ = Table[(Hex & 0xf0) >> 4];
		   *Ascii = Table[Hex & 0xf];
	   }

	}


	static void HtoA (unsigned char Hex, unsigned char *Ascii)
	{
	   char  Table[] = "0123456789ABCDEF";

	   *Ascii++ = Table[Hex >> 4];
	   *Ascii   = Table[Hex & 0x0f];
	}

	static unsigned   AtoH (unsigned char* Buff, unsigned Count)
	{
	   char *Table = "0123456789ABCDEF";
	   unsigned i, j, Out = 0;

	   for (j = 0; j < Count; j++)
	   {
		  for (i = 0; i < 16; i++)
		  {
			if (Table[i] == toupper (Buff[j]))
			   break;
		  }

		  if (i == 16)
			 return -1;

		  Out += (i << 4*(Count - 1 - j));
	   }

	   return Out;
	}
	static void IntToAscii (unsigned Int, char* AsciiBuff, int Cnt)
	{
		for (int i = 0; i < Cnt; i++)
		{
			int Hex = (Int >> 4*i) & 0x000f;

			if (Hex < 10)
				AsciiBuff[Cnt - 1 - i] = (char)(Hex + 0x30);
			else
				AsciiBuff[Cnt - 1 - i] = (char)(Hex + 0x37);
		}
	}

	
};

#endif // __LIB_H__