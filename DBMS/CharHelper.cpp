#include "StdAfx.h"
#include "CharHelper.h"

/**************************************************
[FunctionName]	ToChars
[Function]	Convert CString type into char* type
[Argument]	pDim:A pointer to a character after conversion
		strSrc: Data which need to be transformed
		nSize:The length of the data which need to be transformed
[ReturnedValue] void
**************************************************/
void CCharHelper::ToChars(char* pDim, CString strSrc, const int nSize)
{
	// Initialize the pDim memory
	memset(pDim, 0, nSize);

	// Get the pointer to the strSrc string
	wchar_t* pSrc = strSrc.GetBuffer(strSrc.GetLength());
	// Get the length of the pSrc string
	int  nLen = ::WideCharToMultiByte(CP_ACP, 0, pSrc, -1, NULL, 0, NULL, NULL);
	// According to the number of bytes dynamically allocated memory
	char* pBuf = new char[nLen];

	// Convert wide byte into multibyte
	::WideCharToMultiByte( CP_ACP, 0, pSrc, -1, pBuf, nLen, NULL, NULL);

	if (nLen > nSize)
	{
		nLen = nSize;
	}

	for (int i = 0; i < nLen; i++)
	{
		*(pDim+i) = *(pBuf+i);
	}
	// Release cache
	strSrc.ReleaseBuffer();
	// Release the dynamically allocated memory
	delete[] pBuf;
}

/**************************************************
[FunctionName]	ToChars
[Function]	Convert SYSTEMTIME type into char* type
[Argument]	pDim:A pointer to a character after conversion
			strSrc: Data which need to be transformed
			nSize:The length of the data which need to be transformed
[ReturnedValue]	void
**************************************************/
void CCharHelper::ToChars(char* pDim, SYSTEMTIME tSrc, const int nSize)
{
	char* p = (char*) &tSrc;
	for (int i = 0; i < nSize; i++)
	{
		*pDim++ = *p++;
	}
}

/**************************************************
[FunctionName]	ToChars
[Function]	// Convert bool type into char* type
[Argument]	pDim:A pointer to a character after conversion
			strSrc: Data which need to be transformed
			nSize:The length of the data which need to be transformed
[ReturnedValue] void
**************************************************/
void CCharHelper::ToChars(char* pDim, bool bVal, const int nSize)
{
	char* p = (char*) &bVal;
	for (int i = 0; i < nSize; i++)
	{
		*pDim++ = *p++;
	}
}

/**************************************************
[FunctionName] ToChars
[Function]	Convert int type into char* type
[Argument]	pDim:A pointer to a character after conversion
			strSrc: Data which need to be transformed
			nSize:The length of the data which need to be transformed
[ReturnedValue] void
**************************************************/
void CCharHelper::ToChars(char* pDim, int nVal, const int nSize)
{
	char* p = (char*) &nVal;
	for (int i = 0; i < nSize; i++)
	{
		*pDim++ = *p++;
	}
}

/**************************************************
[FunctionName]	ToChars
[Function]	Convert double type into char* type
[Argument]	pDim:A pointer to a character after conversion
			strSrc: Data which need to be transformed
			nSize:The length of the data which need to be transformed
[ReturnedValue]	void
**************************************************/
void CCharHelper::ToChars(char* pDim, double dbVal, const int nSize)
{
	char* p = (char*) &dbVal;
	for (int i = 0; i < nSize; i++)
	{
		*pDim++ = *p++;
	}
}

/**************************************************
[FunctionName]	ToString
[Function]	Convert char* type into CString type
[Argument]	pDim:A pointer to a character after conversion
			strSrc: Data which need to be transformed
			nSize:The length of the data which need to be transformed
**************************************************/
CString CCharHelper::ToString(char* pSrc, const int nSize)
{
	// Copy character array
	char * pBuf = new char[nSize + 1];
	for (int i = 0; i < nSize; i++)
	{
		*(pBuf+i) = *(pSrc+i);
	}
	pBuf[nSize] = NULL;
	
	// Convert multibyte into wide byte
	int  nLen = ::MultiByteToWideChar(CP_ACP, 0, pBuf, -1,NULL,0);  
	wchar_t *  pWBuf = new  wchar_t[nLen+1];  
	memset(pWBuf, 0, (nLen+1)*sizeof(wchar_t));  
	::MultiByteToWideChar(CP_ACP, 0, pBuf, -1, (LPWSTR)pWBuf, nLen);

	// Construct a string object
	CString str(pWBuf);

	// Release the dynamically allocated memory
	delete[] pWBuf;
 	delete[] pBuf;

	return str;
}

/**************************************************
[FunctionName]	Copy
[Function]	Copy char array
[Argument]	pDim:A pointer to a character after conversion
			strSrc: Data which need to be transformed
			nSize:The length of the data which need to be transformed
[ReturnedValue] void
**************************************************/
void CCharHelper::Copy(char* pDim, char* pSrc, const int nSize)
{
	for(int i = 0; i < nSize; i++)
	{
		*(pDim + i) = *(pSrc + i);
	}
}
