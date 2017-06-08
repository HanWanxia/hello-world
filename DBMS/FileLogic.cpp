#include "StdAfx.h"
#include "FileLogic.h"


/**************************************************
[FunctionName]	GetDBFile
[Function]	Get the path of the database file: ruanko.db file
[Argument]	void
[ReturnedValue]	CString: "ruanko.db",file's absolute path
**************************************************/
CString CFileLogic::GetDBFile(CString path)
{
	CString strPath = _T("");
	try
	{
		// Get absolute path of ruanko.db file
		strPath = GetAbsolutePath(path);
	}
	catch (CAppException* e)
	{
		throw e;
	}
	return strPath;
}

/**************************************************
[FunctionName]	GetDBFolder
[Function]	Get the path of the database folder
[Argument]	const CString strDBName: Database name
[ReturnedValue]	CString: Absolute path of the database folder
**************************************************/
CString CFileLogic::GetDBFolder(const CString strDBName)
{
	CString strFolder = _T("");
	try
	{
		// Get the path of the database folder
		strFolder.Format(_T("data\\%s"), strDBName);
		strFolder = GetAbsolutePath(strFolder);
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to get the path of the database folder!"));
	}

	return strFolder;
}

/**************************************************
[FunctionName]	GetTableFile
[Function]	Get the path of the database table description file
[Argument]	const CString strDBName: Database name
[ReturnedValue]	CString: Absolute path of the database table description file
**************************************************/
CString CFileLogic::GetTableFile(const CString strDBName)
{
	CString strPath = _T("");
	try
	{
		// Get the absolute path of the table description file(*.tb)
		strPath.Format(_T("data\\%s\\%s.tb"), strDBName, strDBName);
		strPath = GetAbsolutePath(strPath);
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to get tb file path!"));
	}
	return strPath;
}

/**************************************************
[FunctionName]	GetTbDefineFile
[Function]	Get the path of the table definition file
[Argument]	const CString strDBName: Database name
		const CString strTableName: Table name
[ReturnedValue]	CString: Absolute path of the table definition file
**************************************************/
CString CFileLogic::GetTbDefineFile(const CString strDBName, const CString strTableName)
{
	CString strPath = _T("");
	try
	{
		strPath.Format(_T("data\\%s\\%s.tdf"), strDBName, strTableName);
		strPath = GetAbsolutePath(strPath);
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to get the path of the table definition file"));
	}

	return strPath;
}

/**************************************************
[FunctionName]	GetTbRecordFile
[Function]	Get the path of the table record file
[Argument]	const CString strDBName: Database name
		const CString strTableName: Table name
[ReturnedValue]	CString: Absolute path of the record file
**************************************************/
CString CFileLogic::GetTbRecordFile(const CString strDBName, const CString strTableName)
{
	CString strPath = _T("");
	try
	{
		strPath.Format(_T("data\\%s\\%s.trd"), strDBName, strTableName);
		strPath = GetAbsolutePath(strPath);
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to get the path of the table record file!"));
	}

	return strPath;
}

/************************************************************************
[FunctionName]	GetAbsolutePath
[Function]	Change relative path into an absolute path.
[Argument]	CString：Relative paths(relative executable file in folder)
[ReturnedValue]	CString：Absolute path
************************************************************************/
CString CFileLogic::GetAbsolutePath(const CString strRelativePath)
{
	CString strFolder = _T("");
	try
	{
		// Get the absolute path of the executable file
		wchar_t acExeFullPath[MAX_PATH];
		::GetModuleFileName(NULL, acExeFullPath, MAX_PATH);
		CString strFolder = acExeFullPath;
		// Get the folder path of the executable file
		int pos = strFolder.ReverseFind('\\');
		strFolder = strFolder.Left(pos+1);
		// Return absolute path
		return strFolder + strRelativePath;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to get the path of file!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to get the path of file!"));
	}

	return strFolder;
}
