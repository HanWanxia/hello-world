#pragma once

/**************************************************
[ClassName]	CCharHelper
[Function]	Character processing tool class
**************************************************/
class CCharHelper
{
public:
	// Convert CString type into char* type
	static void ToChars(char* pDim, CString strSrc, const int nSize);
	// Convert SYSTEMTIME type into char* type
	static void ToChars(char* pDim, SYSTEMTIME tSrc, const int nSize);
	// Convert bool type into char* type
	static void ToChars(char* pDim, bool bVal, const int nSize);
	// Convert int type into char* type
	static void ToChars(char* pDim, int nVal, const int nSize);
	// Convert double type into char* type
	static void ToChars(char* pDim, double dbVal, const int nSize);
	// Convert char* type into CString type
	static CString ToString(char* pSrc, const int nSize);
	// Copy char array
	static void Copy(char* pDim, char* pSrc, const int nSize);
};
