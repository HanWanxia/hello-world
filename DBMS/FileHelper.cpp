#include "StdAfx.h"
#include "FileHelper.h"

/***************************************************************************
[FunctionName]	CreateFile
[Function]	Create file
[Argument]	strFileName: File path
[ReturnedValue]	bool: True if crates file successfully,otherwise false
***************************************************************************/
bool CFileHelper::CreateFile(const CString strFileName)
{
	try
	{
		// Create a folder
		for (int i = 0; i < strFileName.GetLength(); i++)
		{
			if ( (_T('\\') == strFileName.GetAt(i)
				|| _T('/') == strFileName.GetAt(i))
				&& 2 != i
				)
			{
				CString strDirectory;
				strDirectory = strFileName.Left(i);
				if(!CreateDirectory(strDirectory, NULL) && 183 != GetLastError())
				{
					return false;
				}
			}
		}

		// Create file
		CFile file;
		if (!file.Open(strFileName, CFile::modeCreate))
		{
			return false;
		}
		file.Close();

		return true;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to create file!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to create file!"));
	}

	return false;
}

/************************************************************************
[FunctionName]	IsValidFile
[Function]	Decide the effectiveness of the file
[Argument]	CString：File path
[ReturnedValue]	bool: True if the file is effective, otherwise false
************************************************************************/
bool CFileHelper::IsValidFile(const CString strPath)
{
	try
	{
		CFile file;
		if (file.Open(strPath, CFile::modeRead | CFile::shareDenyNone) == TRUE)
		{
			file.Close();
			return true;
		}
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to open file!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to open file!"));
	}
	return false;
}
