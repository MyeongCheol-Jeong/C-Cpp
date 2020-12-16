
#include "pch.h"
#include "Lib.h"




BOOL CLib::IsSet(BYTE Byte, int nPos)
{
    BYTE   BitFormat;

    BitFormat = (BYTE)Power(2, nPos);
    return ((Byte & BitFormat) == BitFormat) ? TRUE : FALSE;
}

//BOOL bStatus = CLib::IsSet(Word[j], i);

BOOL CLib::IsSet(WORD Word, int nPos)
{
    WORD   BitFormat;

    BitFormat = (WORD)Power(2, nPos);
    return ((Word & BitFormat) == BitFormat) ? TRUE : FALSE;
}

BOOL CLib::IsSet(UINT Int, int nPos)
{
    UINT   BitFormat;

    BitFormat = (UINT)Power(2, nPos);
    return ((Int & BitFormat) == BitFormat) ? TRUE : FALSE;
}

BOOL CLib::IsBitRead(BYTE byte, BOOL bHigh)
{
	if(bHigh)
	{
		return ( byte >= 0x10 ) ? TRUE : FALSE;
	}
	else
	{
		return ( byte == 0x11 || byte == 0x01 ) ? TRUE : FALSE;
	}
}


int CLib::Power(int x, int y)
{
    int     i, z = x;

    if (y == 0) return 1;

    for (i = 0; i < y - 1; i++) z *= x;

    return z;
}

int CLib::HexToInt(BYTE bHex)
{
	char szBuff[10];

	sprintf(szBuff, "%2x", bHex);
	return atoi(szBuff);
}

void CLib::ConvertAscToHex(char* pOrg, char* pDest)
{
	sprintf(pDest, "Rx:");
	for (int i = 0; i < 100; i++)
	{
		if (pOrg[i] == NULL) break;
		sprintf(pDest + 3 + i * 3, " %.2x", pOrg[i]);
	}
}

//
//	Number Limit  -  1000000000 이하 Double Value
//
BOOL CLib::ConvertFloatStrToCustom(CString strFloat, char *pDest, int nIntLen, int nPrecision)
{
	/*char	Format[16], DecPoint[32];

	int		nCount = 0;
	BOOL	bFound = FALSE;

	if(strFloat.IsEmpty())
	{
		sprintf(Format, "%%0%dd", nIntLen + nPrecision);
		sprintf(pDest, Format, 0);
		return TRUE;
	}

	int i;
	for (i=0; i < strFloat.GetLength(); i++ ) {
		if (strFloat[i] == '.')	{
			bFound = TRUE;	nCount = i+1;
			break;
		}
	}

	if ( nCount - 1 > nIntLen )	return FALSE;

	if (bFound) {
		int nFrontVal = atoi(strFloat.Mid(0, nCount));
		int nRange = strFloat.GetLength() - nCount;
		if (nRange > nPrecision)	nRange = nPrecision;

		sprintf(Format, "%%0%dd%%s", nIntLen);

		int rd = sprintf(DecPoint, _T("%s"), strFloat.Mid(nCount, nRange));
		if (rd < nPrecision) {
			for ( i = rd; i < nPrecision; i++)
				DecPoint[i] = '0';
			DecPoint[i]=0;
		}
		sprintf(pDest, Format, nFrontVal, DecPoint);
	}
	else {
		if ( strFloat.GetLength() > nIntLen )	return FALSE;
		int nFrontVal = atoi(strFloat.Mid(0, strFloat.GetLength()));
		sprintf(Format, "%%0%dd%%0%dd", nIntLen, nPrecision);
		sprintf(pDest, Format, nFrontVal, 0);
	}*/

	return TRUE;
}

int	CLib::ConvertHexStr2HexValue(char *strHex, int nLen)
{
	char	byCh=0;
	int		nHexVal=0, nVal;

	for(int i=0; i<nLen; i++)
	{
		byCh = strHex[i];
		if(byCh == 0x20)	continue;
		if(byCh >= 0x30 && byCh <= 0x39)
		{
			nVal = byCh - 0x30;
			nHexVal += (Power(16, (nLen - i - 1)) * nVal);
			continue;
		}
		else if(byCh >= 0x41 && byCh <= 0x46)
		{
			nVal = byCh - 0x37;
			nHexVal += (Power(16, (nLen - i - 1)) * nVal);
			continue;
		}
		else if(byCh >= 0x61 && byCh <= 0x66)
		{
			nVal = byCh - 0x57;
			nHexVal += (Power(16, (nLen - i - 1)) * nVal);
			continue;
		}
		else
		{
			nHexVal=0;
			break;
		}
	}
	return nHexVal;
}

void CLib::HexStr2Word(BYTE *bySrc, WORD *byDest)
{
	*byDest = 0;
	for (int i=0; i<4; i++)
	{
		if (bySrc[i] >= '0' && bySrc[i] <= '9')
			(*byDest) |= bySrc[i] - '0';
		else
			(*byDest) |= bySrc[i] - 'A' + 10;
		if(i!=3) (*byDest) <<= 4;
	}
}

WORD CLib::HexStrToWORD(BYTE *bySrc)
{
	WORD wDest = 0;
	for (int i=0; i<4; i++)
	{
		if (bySrc[i] >= '0' && bySrc[i] <= '9')
			wDest |= bySrc[i] - '0';
		else
			wDest |= bySrc[i] - 'A' + 10;
		if(i!=3) wDest <<= 4;
	}

	return wDest;
}

void CLib::HexStr1Word(BYTE *bySrc, BYTE *byDest)
{
	*byDest = 0;
	for (int i=0; i<2; i++)
	{
		if (bySrc[i] >= '0' && bySrc[i] <= '9')
			(*byDest) |= bySrc[i] - '0';
		else
			(*byDest) |= bySrc[i] - 'A' + 10;
		if(i!=1) (*byDest) <<= 4;
	}
}

void CLib::Int2HexaStr(BYTE *bySrc, BYTE *byDest)
{
	*byDest = 0;
	for (int i=0; i<2; i++)
	{
		if (bySrc[i] <= 9)
			byDest[i] = bySrc[i] +  '0';
		else
			byDest[i] = bySrc[i] + 'A' - 10;
	}
}

BYTE CLib::HexStrToBYTE(BYTE *bySrc)
{
	BYTE byDest = 0;
	for(int i = 0; i < 2; i++)
	{
		if( bySrc[i] >= '0' && bySrc[i] <= '9')
			byDest |= bySrc[i] - '0';
		else
			byDest |= bySrc[i] - 'A' + 10;
		if(i == 0)		byDest <<= 4;
	}

	return byDest;
}


void CLib::HexStr1Byte(BYTE *bySrc, BYTE *byDest)
{
	*byDest = 0;
	for (int i=0; i<1; i++)
	{
		if (bySrc[i] >= '0' && bySrc[i] <= '9')
			(*byDest) |= bySrc[i] - '0';
		else
			(*byDest) |= bySrc[i] - 'A' + 10;
	}
}
CString CLib::HexToString(BYTE * bySrc , int nSize)
{
	CString m_str;
	CString m_Format;
	for (int i =0; i<nSize;i++){
		m_Format.Format("%.2X",bySrc[i]);
		m_str += m_Format;		
	}
	return m_str;
}

CString CLib::GetSystemErrMsg(int nErrNo)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
	    FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
	    NULL,
		nErrNo ? nErrNo : ::GetLastError(),
	    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
	    0,
		NULL 
	);

	CString str;
	str.Format("%s", (LPCTSTR)lpMsgBuf);
	LocalFree( lpMsgBuf );

	str.TrimRight();

	return str; 
}

CString CLib::TimeToStr (CTime Time, int Type /*=0*/)
{
	CString Str;
	
	switch (Type)
	{
		case 0:
			Str.Format ("%04d%02d%02d%02d%02d%02d",
				Time.GetYear (),
				Time.GetMonth (),
				Time.GetDay (),
				Time.GetHour (),
				Time.GetMinute (),
				Time.GetSecond ()
				);
		break;
		case 1:
			Str.Format ("%02d년%02d월%02d일%02d시%02d분%02d초",
				Time.GetYear (),
				Time.GetMonth (),
				Time.GetDay (),
				Time.GetHour (),
				Time.GetMinute (),
				Time.GetSecond ()
				);
		break;
		case 2:
			Str.Format ("%02d%02d%02d%02d%02d",
				Time.GetMonth (),
				Time.GetDay (),
				Time.GetHour (),
				Time.GetMinute (),
				Time.GetSecond ()
				);
		break;
		case 3:        //16char
			Str.Format ("%04d%02d%02d%02d%02d%02d00",
				Time.GetYear (),
				Time.GetMonth (),
				Time.GetDay (),
				Time.GetHour (),
				Time.GetMinute (),
				Time.GetSecond ()
				);
		break;
		case 4:        
			Str.Format ("%04d/%02d/%02d/%02d/%02d/%02d",
				Time.GetYear (),
				Time.GetMonth (),
				Time.GetDay (),
				Time.GetHour (),
				Time.GetMinute (),
				Time.GetSecond ()
				);
		break;
		case 5:        
			Str.Format ("%04d/%02d/%02d",
				Time.GetYear (),
				Time.GetMonth (),
				Time.GetDay ()
				);
		break;
		case 6:
			Str.Format ("  %02d년%02d월%02d일",
				Time.GetYear (),
				Time.GetMonth (),
				Time.GetDay ()
				);
		break;
		case 7:
			Str.Format (" %02d시%02d분%02d초",
				Time.GetHour (),
				Time.GetMinute (),
				Time.GetSecond ()
				);
		break;








	}

	if (Time == CTime (1980, 1, 1, 1, 1, 1))
		Str = "";

	return Str;
}


