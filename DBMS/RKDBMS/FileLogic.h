#pragma once

/**************************************************
[ClassName]	CFileLogic
[Function]	Database file logic class
**************************************************/
class CFileLogic
{
public:
	// Get the path of the database description file
	CString GetDBFile(CString path);
	// Get the path of the database folder 
	CString GetDBFolder(const CString strDBName);
	// Get the path of the database table description file
	CString GetTableFile(const CString strDBName);
	// Get the path of the table definition file
	CString GetTbDefineFile(const CString strDBName, const CString strTableName);
	// Get the path of the table record file
	CString GetTbRecordFile(const CString strDBName, const CString strTableName);

private:
	// Change relative path into an absolute path.
	CString GetAbsolutePath(const CString strRelativePath);
};
