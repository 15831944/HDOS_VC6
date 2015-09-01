/////////////////////////////////////////////////////////////////////////
// ������CSpreadSheet
// ���ܣ�����дExcel�ļ���ָ���ָ����ָ����ı��ļ���
// ��ע�����롢����ָ�����ݵ�Excel�ļ���ָ����ı��ļ�
// �޸ģ��쾰��(jingzhou_xu@163.com)
// ��֯��Future Studio
// ���ڣ�2003.1.8
////////////////////////////////////////////////////////////////////////
#ifndef CSPREADSHEET_H
#define CSPREADSHEET_H

#include <odbcinst.h>
#include <afxdb.h>

class CSpreadSheet
{
public:
	CSpreadSheet(CString File, CString SheetOrSeparator, bool Backup = false);			// Ϊ���ж�д���������е�Ԥ������
	~CSpreadSheet();																	// ������
	bool AddHeaders(CStringArray &FieldNames, bool replace = false);					// ���������ͷ
	bool DeleteSheet();																	// ɾ���ָ����ı��ļ�����
	bool DeleteSheet(CString SheetName);												// ɾ��ָ�����ȫ�����ݣ������������ɾ��
	bool AddRow(CStringArray &RowValues, long row = 0, bool replace = false);			// ���Ż��滻һ��
	bool AddCell(CString CellValue, CString column, long row = 0, bool Auto = true);	// ʹ���кŻ���ĸ�к��滻�����һ��Ԫ��
	bool AddCell(CString CellValue, short column, long row = 0);						// ʹ���С��к��滻�����һ��Ԫ��
	bool ReplaceRows(CStringArray &NewRowValues, CStringArray &OldRowValues);			// ��Excel������滻��
	bool ReadRow(CStringArray &RowValues, long row = 0);								// ��ȡһ��
	bool ReadColumn(CStringArray &ColumnValues, CString column, bool Auto = true);		// ʹ���кš���ĸ�кŶ�ȡһ��
	bool ReadColumn(CStringArray &ColumnValues, short column);							// ʹ���кŶ�ȡһ��
	bool ReadCell (CString &CellValue, CString column, long row = 0, bool Auto = true); // ʹ���кš���ĸ�кŶ�ȡ��Ԫ��
	bool ReadCell (CString &CellValue, short column, long row = 0);						// ʹ���кŶ�ȡ��Ԫ��
	void BeginTransaction();															// ��ʼ����
	bool Commit();																		// ����ı�״̬
	bool RollBack();																	// �ع��ı�״̬
	bool Convert(CString SheetOrSeparator);
																						// ��ȡ������ͷ��
	inline void GetFieldNames (CStringArray &FieldNames) {FieldNames.RemoveAll(); FieldNames.Copy(m_aFieldNames);} 
	inline long GetTotalRows() {return m_dTotalRows;}									// ��ȡ������
	inline short GetTotalColumns() {return m_dTotalColumns;}							// ��ȡ������
	inline long GetCurrentRow() {return m_dCurrentRow;}									// ��ȡ��ǰѡ����
	inline bool GetBackupStatus() {return m_bBackup;}									// ��ȡ����״̬. True��ʾ����, False�����б���
	inline bool GetTransactionStatus() {return m_bTransaction;}							// ��ȡ����״̬. True��ʾ��ʼ, False��ʾû�п�ʼ��ʼʱ��������
	inline CString GetLastError() {return m_sLastError;}								// ��ȡ��������Ϣ

private:
	bool Open();																		// Ϊ���ж�д�򿪴���
	void GetExcelDriver();																// ��ȡExcel-ODBC��������
	short CalculateColumnNumber(CString column, bool Auto);								// ת��Excel��ĸ�к�Ϊ��Ӧ�����к�

	bool	m_bAppend;			// �½������ʹ��ԭ����ڲ���־
	bool	m_bBackup;			// ����״̬�ڲ���־
	bool	m_bExcel;			// ��Excel����ļ����Ƿָ����ı��ļ��ڲ���־
	bool	m_bTransaction;		// ����״̬�ڲ���־

	long	m_dCurrentRow;		// ��ǰ�к�����, ��ʼΪ1
	long	m_dTotalRows;		// ������
	short	m_dTotalColumns;	// Excel�ļ�ʱ���������ָ����ı��ļ����������

	CString m_sSql;				// ��Excel���ж�дSQL���
	CString m_sDsn;				// ��Excel���ж�д��DSN��
	CString m_stempSql;			// ��ʱSQL�ַ���
	CString m_stempString;		// ��ʱ�ַ���
	CString m_sSheetName;		// Excel�����
	CString m_sExcelDriver;		// Excel����������
	CString m_sFile;			// �ļ���
	CString m_sSeparator;		// �ı��ļ��ָ���
	CString m_sLastError;		// ������Ϣ

	CStringArray m_atempArray;	// ��ʱ����
	CStringArray m_aFieldNames; // �ֶ�����
	CStringArray m_aRows;		// �д洢

	CDatabase	*m_Database;	// ���ݿ����
	CRecordset	*m_rSheet;		// ��¼������
};

// Ϊ��д���д򿪴���(File -- �ļ�����SheetOrSeparator -- Excel�������ı��ָ�����Backup -- �Ƿ񴴽����ݱ�)
CSpreadSheet::CSpreadSheet(CString File, CString SheetOrSeparator, bool Backup /* = false */) :
m_Database(NULL), m_rSheet(NULL), m_sFile(File),
m_dTotalRows(0), m_dTotalColumns(0), m_dCurrentRow(1),
m_bAppend(false), m_bBackup(Backup), m_bTransaction(false)
{
	// ����ļ���Excel����Ƿָ����ı��ļ�
	m_stempString		= m_sFile.Right(4);
	m_stempString.MakeLower();
	if (m_stempString == ".xls") // ����Excel����ļ�ʱ
	{
		m_bExcel		= true;
		m_sSheetName	= SheetOrSeparator;
		m_sSeparator	= " ,;.?";
	}
	else						// ���Ƿָ����ı��ļ�ʱ
	{
		m_bExcel		= false;
		m_sSeparator	= SheetOrSeparator;
	}

	// ���ļ���Excel�ļ�ʱ
	if (m_bExcel) 
	{
		m_Database = new CDatabase;
		GetExcelDriver();
		m_sDsn.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s", m_sExcelDriver, m_sFile, m_sFile);

		if (Open())				// �Ƿ��Ѵ���Excel�ļ�������Դ�
		{
			if (m_bBackup)		// Excel�б���ڲ����Դ򿪵Ļ����Ƿ���ԭʼ���ݱ�
			{
				if ((m_bBackup) && (m_bAppend))
				{
					CString tempSheetName	= m_sSheetName;
					m_sSheetName			= m_sSheetName + "����";
					m_bAppend				= false;

					// �ڴ˴������ݱ�
					if (!Commit())
					{
						m_bBackup			= false;
					}
					m_bAppend				= true;
					m_sSheetName			= tempSheetName;
					m_dCurrentRow			= 1;
				}
			}
		}
	}
	else // ���ļ���ָ���ָ����ָ����ı��ļ�ʱ
	{
		if (Open())
		{
			if ((m_bBackup) && (m_bAppend))
			{
				m_stempString	= m_sFile;
				m_stempSql.Format("%s.bak", m_sFile);
				m_sFile			= m_stempSql;
				if (!Commit())
				{
					m_bBackup	= false;
				}
				m_sFile			= m_stempString;
			}
		}
	}
}

// ������
CSpreadSheet::~CSpreadSheet()
{
	if (NULL != m_Database)
	{
		m_Database->Close();
		delete m_Database;
	}
}

// ���������ͷ�������
bool CSpreadSheet::AddHeaders(CStringArray &FieldNames, bool replace)
{
	if (m_bAppend)		// ԭ����׷��
	{
		if (replace)	// �滻���ж������������
		{
			if (!AddRow(FieldNames, 1, true))
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		if (ReadRow(m_atempArray, 1)) // �������
		{
			if (m_bExcel)
			{
				// ���������ͷ�ֶ��Ƿ��ظ�
				for (int i = 0; i < FieldNames.GetSize(); i++)
				{
					for (int j = 0; j < m_atempArray.GetSize(); j++)
					{
						if (FieldNames.GetAt(i) == m_atempArray.GetAt(j))
						{
							m_sLastError.Format("������ͷ�ֶ��ظ�:%s\n", FieldNames.GetAt(i));
							return false;
						}
					}
				}	
			}

			m_atempArray.Append(FieldNames);
			if (!AddRow(m_atempArray, 1, true))
			{
				m_sLastError = "�����ͷʱ��������\n";
				return false;
			}

			// ����������
			if (m_atempArray.GetSize() > m_dTotalColumns)
			{
				m_dTotalColumns = m_atempArray.GetSize();
			}
			return true;
		}
		return false;				
	}
	else // �±��
	{
		m_dTotalColumns = FieldNames.GetSize();
		if (!AddRow(FieldNames, 1, true))
		{
			return false;
		}
		else
		{
			m_dTotalRows = 1;
			return true;
		}
	}
}

// ɾ���ָ����ı��ļ�����
bool CSpreadSheet::DeleteSheet()
{
	if (m_bExcel)
	{
		if (DeleteSheet(m_sSheetName))
		{
			return true;
		}
		else
		{
			m_sLastError = "ɾ�����ʱ��������\n";
			return false;
		}
	}
	else
	{
		m_aRows.RemoveAll();
		m_aFieldNames.RemoveAll();
		m_dTotalColumns = 0;
		m_dTotalRows = 0;
		if (!m_bTransaction)
		{
			Commit();			
		}
		m_bAppend = false; // �����±���־

		return true;		
	}
}

// ɾ��ָ��Excel������ݣ����������ɾ��
bool CSpreadSheet::DeleteSheet(CString SheetName)
{
	if (m_bExcel)	// ����Excel���ʱ
	{
		// ɾ�����
		m_Database->OpenEx(m_sDsn, CDatabase::noOdbcDialog);
		SheetName = "[" + SheetName + "$A1:IV65536]";
		m_stempSql.Format ("DROP TABLE %s", SheetName);
		try
		{
			m_Database->ExecuteSQL(m_stempSql);
			m_Database->Close();
			m_aRows.RemoveAll();
			m_aFieldNames.RemoveAll();
			m_dTotalColumns = 0;
			m_dTotalRows = 0;
		}
		catch(CDBException *pEx)
		{
			m_sLastError = pEx->m_strError;
			m_Database->Close();
			pEx->Delete();

			return false;
		}
		return true;
	}
	else			// ���Ƿָ����ı��ļ�ʱ
	{
		return DeleteSheet();
	}
}

// ���Ż��滻һ�е�����У�Ĭ��Ϊ���һ���� 
bool CSpreadSheet::AddRow(CStringArray &RowValues, long row, bool replace)
{
	long tempRow;
	
	if (row == 1)
	{
		if (m_bExcel) 
		{
			// ���Excel���������ͷ�ֶ��Ƿ��ظ�
			for (int i = 0; i < RowValues.GetSize(); i++)
			{
				for (int j = 0; j < RowValues.GetSize(); j++)
				{
					if ((i != j) && (RowValues.GetAt(i) == RowValues.GetAt(j)))
					{
						m_sLastError.Format("������ͷ�ֶ��ظ�:%s\n", RowValues.GetAt(i));
						return false;
					}
				}
			}
			
			// ���������ͷ���Ƿ��С
			if (RowValues.GetSize() < m_dTotalColumns)
			{
				m_sLastError = "����ͷ������С��ԭ��ͷ��";
				return false;
			}
			m_dTotalColumns = RowValues.GetSize();
		}

		// ��������(��ͷ)
		m_aFieldNames.RemoveAll();
		m_aFieldNames.Copy(RowValues);
	}
	else
	{
		if (m_bExcel)
		{
			if (m_dTotalColumns == 0)
			{
				m_sLastError = "û����ͷ������Ҫ������ͷ\n";
				return false;
			}
		}
	}

	if (m_bExcel)	// Excel����ļ�ʱ
	{
		if (RowValues.GetSize() > m_aFieldNames.GetSize())
		{
			m_sLastError = "�������ڱ����������\n";
			return false;
		}
	}
	else			// �ָ����ı��ļ�ʱ
	{
		// �����������
		if (RowValues.GetSize() > m_dTotalColumns)
		{
			m_dTotalColumns = RowValues.GetSize();
		}
	}

	// ת����ֵ
	m_stempString.Empty();
	for (int i = 0; i < RowValues.GetSize(); i++)
	{
		if (i != RowValues.GetSize()-1) // �������һ��
		{
			m_stempSql.Format("\"%s\"%s", RowValues.GetAt(i), m_sSeparator);
			m_stempString += m_stempSql;
		}
		else							// ���һ��
		{
			m_stempSql.Format("\"%s\"", RowValues.GetAt(i));
			m_stempString += m_stempSql;
		}
	}
	
	if (row)
	{
		if (row <= m_dTotalRows)	// �����������
		{
			if (replace)			// �滻��
			{
				m_aRows.SetAt(row-1, m_stempString);
			}
			else					// ������
			{
				m_aRows.InsertAt(row-1, m_stempString);
				m_dTotalRows++;
			}

			if (!m_bTransaction)
			{
				Commit();
			}
			return true;
		}
		else						// �������
		{
			// �������ֱ��ָ���к�
			m_dCurrentRow = m_dTotalRows;
			m_stempSql.Empty();
			CString nullString;
			for (int i = 1; i <= m_dTotalColumns; i++)
			{
				if (i != m_dTotalColumns)
				{
					if (m_bExcel)
					{
						nullString.Format("\" \"%s", m_sSeparator);
					}
					else
					{
						nullString.Format("\"\"%s", m_sSeparator);
					}
					m_stempSql += nullString;
				}
				else
				{
					if (m_bExcel)
					{
						m_stempSql += "\" \"";
					}
					else
					{
						m_stempSql += "\"\"";
					}
				}
			}
			for (int j = m_dTotalRows + 1; j < row; j++)
			{
				m_dCurrentRow++;
				m_aRows.Add(m_stempSql);
			}
		}
	}
	else
	{
		tempRow = m_dCurrentRow;
		m_dCurrentRow = m_dTotalRows;
	}

	// ����һ����
	m_dCurrentRow++;
	m_aRows.Add(m_stempString);
	
	if (row > m_dTotalRows)
	{
		m_dTotalRows	= row;
	}
	else if (!row)
	{
		m_dTotalRows	= m_dCurrentRow;
		m_dCurrentRow	= tempRow;
	}
	if (!m_bTransaction)
	{
		Commit();
	}

	return true;
}

// ʹ���кš���ĸ�к��滻�����һ��Ԫ��Excel����У�Ĭ��Ϊ��ӵ�Ԫ��һ�����У�
// �������ʹ����ĸ�к���Ϊ��ͷ���ɽ�Auto��Ϊfalse
bool CSpreadSheet::AddCell(CString CellValue, CString column, long row, bool Auto)
{
	short columnIndex = CalculateColumnNumber(column, Auto);
	if (0 == columnIndex)
	{
		return false;
	}

	if (AddCell(CellValue, columnIndex, row))
	{
		return true;
	}

	return false;
}

// ʹ�������кš��к��滻�����һ����Ԫ�񵽱���У�Ĭ��Ϊ��ӵ�Ԫ��һ����
bool CSpreadSheet::AddCell(CString CellValue, short column, long row)
{
	if (0 == column)
	{
		m_sLastError = "��������Ϊ0\n";
		return false;
	}

	long tempRow;

	if (m_bExcel)	// ����Excel����ļ�ʱ
	{
		if (column > m_aFieldNames.GetSize() + 1)
		{
			m_sLastError = "ָ���кŴ��ڱ���д��ڵ�������\n";
			return false;
		}
	}
	else			// ���Ƿָ����ı��ļ�ʱ
	{
		// �����������
		if (column > m_dTotalColumns)
		{
			m_dTotalColumns = column;
		}
	}

	if (row)
	{
		if (row <= m_dTotalRows)
		{
			ReadRow(m_atempArray, row);
	
			// �ı�ָ����
			m_atempArray.SetAtGrow(column-1, CellValue);

			if (row == 1)
			{
				if (m_bExcel) // �����ͷ�ֶ��Ƿ��ظ�
				{										
					for (int i = 0; i < m_atempArray.GetSize(); i++)
					{
						for (int j = 0; j < m_atempArray.GetSize(); j++)
						{
							if ((i != j) && (m_atempArray.GetAt(i) == m_atempArray.GetAt(j)))
							{
								m_sLastError.Format("�����ֶ��ظ�(��ͷ):%s\n", m_atempArray.GetAt(i));
								return false;
							}
						}
					}
				}

				// ��������(��ͷ)
				m_aFieldNames.RemoveAll();
				m_aFieldNames.Copy(m_atempArray);
			}	

			if (!AddRow(m_atempArray, row, true))
			{
				return false;
			}

			if (!m_bTransaction)
			{
				Commit();
			}
			return true;
		}
		else
		{
			// �������ֱ��ָ���к�
			m_dCurrentRow = m_dTotalRows;
			m_stempSql.Empty();
			CString nullString;
			for (int i = 1; i <= m_dTotalColumns; i++)
			{
				if (i != m_dTotalColumns)
				{
					if (m_bExcel)
					{
						nullString.Format("\" \"%s", m_sSeparator);
					}
					else
					{
						nullString.Format("\"\"%s", m_sSeparator);
					}
					m_stempSql		+= nullString;
				}
				else
				{
					if (m_bExcel)
					{
						m_stempSql	+= "\" \"";
					}
					else
					{
						m_stempSql	+= "\"\"";
					}
				}
			}
			for (int j = m_dTotalRows + 1; j < row; j++)
			{
				m_dCurrentRow++;
				m_aRows.Add(m_stempSql);
			}
		}
	}
	else
	{
		tempRow = m_dCurrentRow;
		m_dCurrentRow = m_dTotalRows;
	}

	// ���뵥Ԫ��
	m_dCurrentRow++;
	m_stempString.Empty();
	for (int j = 1; j <= m_dTotalColumns; j++)
	{
		if (j != m_dTotalColumns) // û�����һ��
		{
			if (j != column)
			{
				if (m_bExcel)
				{
					m_stempSql.Format("\" \"%s", m_sSeparator);
				}
				else
				{
					m_stempSql.Format("\"\"%s", m_sSeparator);
				}
				m_stempString += m_stempSql;
			}
			else
			{
				m_stempSql.Format("\"%s\"%s", CellValue, m_sSeparator);
				m_stempString += m_stempSql;
			}
		}
		else					// ���һ��
		{
			if (j != column)
			{
				if (m_bExcel)
				{
					m_stempString += "\" \"";
				}
				else
				{
					m_stempString += "\"\"";
				}
			}
			else
			{
				m_stempSql.Format("\"%s\"", CellValue);
				m_stempString += m_stempSql;
			}
		}
	}	

	m_aRows.Add(m_stempString);
	
	if (row > m_dTotalRows)
	{
		m_dTotalRows	= row;
	}
	else if (!row)
	{
		m_dTotalRows	= m_dCurrentRow;
		m_dCurrentRow	= tempRow;
	}
	if (!m_bTransaction)
	{
		Commit();
	}
	return true;
}

// �������滻Excel�����������
bool CSpreadSheet::ReplaceRows(CStringArray &NewRowValues, CStringArray &OldRowValues)
{
	if (m_bExcel) // ����Excel����ļ�ʱ
	{
		// �򿪻򴴽�Excel�ļ�
		m_Database->OpenEx(m_sDsn, CDatabase::noOdbcDialog);
		m_stempSql.Format("UPDATE [%s] SET ", m_sSheetName);
		for (int i = 0; i < NewRowValues.GetSize(); i++)
		{
			m_stempString.Format("[%s]='%s', ", m_aFieldNames.GetAt(i), NewRowValues.GetAt(i));
			m_stempSql = m_stempSql + m_stempString;
		}
		m_stempSql.Delete(m_stempSql.GetLength()-2, 2);
		m_stempSql = m_stempSql + " WHERE (";
		for (int j = 0; j < OldRowValues.GetSize()-1; j++)
		{
			m_stempString.Format("[%s]='%s' AND ", m_aFieldNames.GetAt(j), OldRowValues.GetAt(j));
			m_stempSql = m_stempSql + m_stempString;
		}
		m_stempSql.Delete(m_stempSql.GetLength()-4, 5);
		m_stempSql += ")";

		try
		{
			m_Database->ExecuteSQL(m_stempSql);
			m_Database->Close();
			Open();
			return true;
		}
		catch(CDBException *pEx)
		{
			m_sLastError = pEx->m_strError;
			m_Database->Close();
			pEx->Delete();
			return false;
		}
	}
	else		// ���Ƿָ������ı��ļ�ʱ
	{
		m_sLastError = "��������Էָ����ı��ļ���Ч\n";
		return false;
	}
}

// ��ȡ�����һ�У�Ĭ��Ϊ��ȡ��һ��
bool CSpreadSheet::ReadRow(CStringArray &RowValues, long row)
{
	// ���ָ���к��Ƿ���ڱ����������
	if (row <= m_aRows.GetSize())
	{
		if (0 != row)
		{
			m_dCurrentRow = row;
		}
		else if (m_dCurrentRow > m_aRows.GetSize())
		{
			return false;
		}

		// ��ȡָ����
		RowValues.RemoveAll();
		m_stempString = m_aRows.GetAt(m_dCurrentRow-1);
		m_dCurrentRow++;

		// �����ָ��еķָ���
		int separatorPosition;
		m_stempSql.Format("\"%s\"", m_sSeparator);
		separatorPosition = m_stempString.Find(m_stempSql); // ����ָ������ַ�"?"
		if (separatorPosition != -1)
		{
			// ������
			int nCount = 0;
			int stringStartingPosition = 0;
			while (separatorPosition != -1)
			{
				nCount = separatorPosition - stringStartingPosition;
				RowValues.Add(m_stempString.Mid(stringStartingPosition, nCount));
				stringStartingPosition = separatorPosition + m_stempSql.GetLength();
				separatorPosition = m_stempString.Find(m_stempSql, stringStartingPosition);
			}
			nCount = m_stempString.GetLength() - stringStartingPosition;
			RowValues.Add(m_stempString.Mid(stringStartingPosition, nCount));

			// ɾ����һ�����÷���
			m_stempString = RowValues.GetAt(0);
			m_stempString.Delete(0, 1);
			RowValues.SetAt(0, m_stempString);
			
			// ɾ����������÷���
			m_stempString = RowValues.GetAt(RowValues.GetSize()-1);
			m_stempString.Delete(m_stempString.GetLength()-1, 1);
			RowValues.SetAt(RowValues.GetSize()-1, m_stempString);

			return true;
		}
		else
		{
			// ������
			separatorPosition = m_stempString.Find(m_sSeparator); // ���ָ������ַ�"?"
			if (separatorPosition != -1)
			{
				int nCount = 0;
				int stringStartingPosition = 0;
				while (separatorPosition != -1)
				{
					nCount = separatorPosition - stringStartingPosition;
					RowValues.Add(m_stempString.Mid(stringStartingPosition, nCount));
					stringStartingPosition = separatorPosition + m_sSeparator.GetLength();
					separatorPosition = m_stempString.Find(m_sSeparator, stringStartingPosition);
				}
				nCount = m_stempString.GetLength() - stringStartingPosition;
				RowValues.Add(m_stempString.Mid(stringStartingPosition, nCount));
				return true;
			}
			else	// ���ֻ��һ��ʱ
			{
				// ��������ڣ�ɾ����ʼ�ͽ���ʱ�����÷���
				int quoteBegPos = m_stempString.Find('\"');
				int quoteEndPos = m_stempString.ReverseFind('\"');
				if ((quoteBegPos == 0) && (quoteEndPos == m_stempString.GetLength()-1))
				{
					m_stempString.Delete(0, 1);
					m_stempString.Delete(m_stempString.GetLength()-1, 1);
				}

				RowValues.Add(m_stempString);
			}
		}
	}

	m_sLastError = "ָ���д��ڱ����������\n";

	return false;
}

// ʹ����ĸ�кŴ�Excel����ж�ȡһ�У�����뽫��ĸ����Ϊ�кŵĻ���Auto��Ϊfalse
bool CSpreadSheet::ReadColumn(CStringArray &ColumnValues, CString column, bool Auto)
{
	short columnIndex = CalculateColumnNumber(column, Auto);
	if (0 == columnIndex)
	{
		return false;
	}

	if (ReadColumn(ColumnValues, columnIndex))
	{
		return true;
	}
	return false;
}

// ʹ�������кŴӱ���ж�ȡһ��
bool CSpreadSheet::ReadColumn(CStringArray &ColumnValues, short column)
{
	if (0 == column)
	{
		m_sLastError = "��������Ϊ0\n";
		return false;
	}

	int tempRow = m_dCurrentRow;
	m_dCurrentRow = 1;
	ColumnValues.RemoveAll();
	for (int i = 1; i <= m_aRows.GetSize(); i++)
	{
		// ��ȡÿһ��
		if (ReadRow(m_atempArray, i))
		{
			// ��ָ�����л�ȡ��Ԫ������
			if (column <= m_atempArray.GetSize())
			{
				ColumnValues.Add(m_atempArray.GetAt(column-1));
			}
			else
			{
				ColumnValues.Add("");
			}
		}
		else
		{
			m_dCurrentRow = tempRow;
			m_sLastError = "��ȡ��ʱ��������\n";
			return false;
		}
	}
	m_dCurrentRow = tempRow;
	return true;
}

// ��Excel�����ʹ������(��ͷ)����ĸ�кŶ�ȡ��Ԫ�����ݣ�Ĭ��Ϊ����һ���ж�ȡ��һ����Ԫ������
// ������뽫��ĸ����Ϊ��ͷ���Ļ��ɽ�Auto��Ϊfalse 
bool CSpreadSheet::ReadCell (CString &CellValue, CString column, long row, bool Auto)
{
	short columnIndex = CalculateColumnNumber(column, Auto);
	if (0 == columnIndex)
	{
		return false;
	}

	if (ReadCell(CellValue, columnIndex, row))
	{
		return true;
	}
	return false;
}

// �ڱ���ļ���ʹ���С��кŶ�ȡ��Ԫ�����ݣ�Ĭ��(row��Ч)Ϊ��һ���ж�ȡ��һ����Ԫ��
bool CSpreadSheet::ReadCell (CString &CellValue, short column, long row)
{
	if (0 == column)
	{
		m_sLastError		= "�в���Ϊ0\n";
		return false;
	}

	int tempRow				= m_dCurrentRow;
	if (row)
	{
		m_dCurrentRow		= row;
	}
	if (ReadRow(m_atempArray, m_dCurrentRow))
	{
		// ��ȡָ�����е�Ԫ������
		if (column <= m_atempArray.GetSize())
		{
			CellValue		= m_atempArray.GetAt(column-1);
		}
		else
		{
			CellValue.Empty();
			m_dCurrentRow	= tempRow;
			return false;
		}
		m_dCurrentRow		= tempRow;
		return true;
	}
	m_dCurrentRow			= tempRow;
	m_sLastError			= "��ȡ��ʱ��������\n";

	return false;
}

// ����ʼ
void CSpreadSheet::BeginTransaction()
{
	m_bTransaction = true;
}

// �ύ�ı�����ݵ������ı��ļ��У��ڴ˴���Excel�б�
bool CSpreadSheet::Commit()
{
	if (m_bExcel) // ����Excel����ļ�ʱ
	{
		// �򿪻򴴽�Excel�ļ�
		m_Database->OpenEx(m_sDsn, CDatabase::noOdbcDialog);

		if (m_bAppend)
		{
			// ����Ѿ����ڱ����ɾ����
			m_stempString= "[" + m_sSheetName + "$A1:IV65536]";
			m_stempSql.Format ("DROP TABLE %s", m_stempString);
			try
			{
				m_Database->ExecuteSQL(m_stempSql);
			}
			catch(CDBException *pEx)
			{
				m_sLastError = pEx->m_strError;
				m_Database->Close();
				pEx->Delete();
				return false;
			}
			
			// ����һ���µı��
			m_stempSql.Format("CREATE TABLE [%s$A1:IV65536] (", m_sSheetName);
			for (int j = 0; j < m_aFieldNames.GetSize(); j++)
			{
				m_stempSql = m_stempSql + "[" + m_aFieldNames.GetAt(j) +"]" + " char(255), ";
			}
			m_stempSql.Delete(m_stempSql.GetLength()-2, 2);
			m_stempSql += ")";
		}
		else
		{
			// ����һ���µı��
			m_stempSql.Format("CREATE TABLE [%s] (", m_sSheetName);
			for (int i = 0; i < m_aFieldNames.GetSize(); i++)
			{
				m_stempSql = m_stempSql + "[" + m_aFieldNames.GetAt(i) +"]" + " char(255), ";
			}
			m_stempSql.Delete(m_stempSql.GetLength()-2, 2);
			m_stempSql += ")";
		}

		try
		{
			m_Database->ExecuteSQL(m_stempSql);
			if (!m_bAppend)
			{
				m_dTotalColumns = m_aFieldNames.GetSize();
				m_bAppend		= true;
			}
		}
		catch(CDBException *pEx)
		{
			m_sLastError		= pEx->m_strError;
			m_Database->Close();
			pEx->Delete();

			return false;
		}

		// �����Ѹı������
		for (int k = 1; k < m_dTotalRows; k++)
		{
			ReadRow(m_atempArray, k+1);

			// ����������SQL���
			m_stempSql.Format("INSERT INTO [%s$A1:IV%d] (", m_sSheetName, k);
			for (int i = 0; i < m_atempArray.GetSize(); i++)
			{
				m_stempString.Format("[%s], ", m_aFieldNames.GetAt(i));
				m_stempSql = m_stempSql + m_stempString;
			}
			m_stempSql.Delete(m_stempSql.GetLength()-2, 2);
			m_stempSql += ") VALUES (";
			for (int j = 0; j < m_atempArray.GetSize(); j++)
			{
				m_stempString.Format("'%s', ", m_atempArray.GetAt(j));
				m_stempSql = m_stempSql + m_stempString;
			}
			m_stempSql.Delete(m_stempSql.GetLength()-2, 2);
			m_stempSql += ")";

			// ������
			try
			{
				m_Database->ExecuteSQL(m_stempSql);
			}
			catch(CDBException *pEx)
			{
				m_sLastError = pEx->m_strError;
				m_Database->Close();
				pEx->Delete();
				return false;
			}
		}
		m_Database->Close();
		m_bTransaction = false;
		return true;
	}
	else // ���ļ��Ƿָ����ָ����ı��ļ�ʱ
	{
		try
		{
			CFile *File = NULL;
			File = new CFile(m_sFile, CFile::modeCreate | CFile::modeWrite  | CFile::shareDenyNone);
			if (File != NULL)
			{
				CArchive *Archive = NULL;
				Archive = new CArchive(File, CArchive::store);
				if (Archive != NULL)
				{
					for (int i = 0; i < m_aRows.GetSize(); i++)
					{
						Archive->WriteString(m_aRows.GetAt(i));
						Archive->WriteString("\r\n");
					}
					delete Archive;
					delete File;
					m_bTransaction = false;
					return true;
				}
				delete File;
			}
		}
		catch(...)
		{
		}
		m_sLastError = "д�ļ�ʱ��������\n";
		return false;
	}
}

// �ع��ļ��ı�Ϊ�ı�ǰ״̬
bool CSpreadSheet::RollBack()
{
	if (Open())
	{
		m_bTransaction = false;
		return true;
	}

	m_sLastError = "�ڻع���ǰ״̬ʱ��������\n";

	return false;
}

// ת��Ϊָ���ָ������ı������ļ�
bool CSpreadSheet::Convert(CString SheetOrSeparator)
{
	// �ļ���
	m_stempString = m_sFile;
	m_stempString.Delete(m_stempString.GetLength()-4, 4);
	if (m_bExcel) // ���ļ���Excel�ļ�ʱ
	{
		m_stempString += ".csv";
		CSpreadSheet tempSheet(m_stempString, SheetOrSeparator, false);
		
		// ���ָ���ı��ļ��Ѵ��ڣ��治ת��ֱ�ӷ���
		if (0 != tempSheet.GetTotalColumns())
		{
			return false;
		}

		tempSheet.BeginTransaction();

		for (int i = 1; i <= m_dTotalRows; i++)
		{
			if (!ReadRow(m_atempArray, i))
			{
				return false;
			}
			if (!tempSheet.AddRow(m_atempArray, i))
			{
				return false;
			}
		}
		if (!tempSheet.Commit())
		{
			return false;
		}
		return true;
	}
	else		// ���ļ��Ƿָ����ָ����ı��ļ�ʱ
	{
		m_stempString += ".xls";
		CSpreadSheet tempSheet(m_stempString, SheetOrSeparator, false);

		// ���ָ��Excel�ļ��Ѵ��ڣ���ֱ�ӷ���
		if (0 != tempSheet.GetTotalColumns())
		{
			return false;
		}

		GetFieldNames(m_atempArray);

		// �������(��ͷ)�ֶ��Ƿ��ظ�
		bool duplicate = false;
		for (int i = 0; i < m_atempArray.GetSize(); i++)
		{
			for (int j = 0; j < m_atempArray.GetSize(); j++)
			{
				if ((i != j) && (m_atempArray.GetAt(i) == m_atempArray.GetAt(j)))
				{
					m_sLastError.Format("����(��ͷ)�ֶ��ظ�:%s\n", m_atempArray.GetAt(i));
					duplicate = true;
				}
			}
		}

		if (duplicate) // �ظ�ʱ������Ԫ����(��ͷ)
		{
			m_atempArray.RemoveAll();
			for (int k = 1; k <= m_dTotalColumns; k++)
			{
				m_stempString.Format("%d", k);
				m_atempArray.Add(m_stempString);
			}

			if (!tempSheet.AddHeaders(m_atempArray))
			{
				return false;
			}

			for (int l = 1; l <= m_dTotalRows; l++)
			{
				if (!ReadRow(m_atempArray, l))
				{
					return false;
				}
				if (!tempSheet.AddRow(m_atempArray, l+1))
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			if (!tempSheet.AddHeaders(m_atempArray))
			{
				return false;
			}

			for (int l = 2; l <= m_dTotalRows; l++)
			{
				if (!ReadRow(m_atempArray, l))
				{
					return false;
				}
				if (!tempSheet.AddRow(m_atempArray, l))
				{
					return false;
				}
			}
			return true;
		}
	}
}

// Ϊ���ж�д��Excel��ָ����ָ��ı��ļ�
bool CSpreadSheet::Open()
{
	if (m_bExcel)	// ���ļ���Excel���ӱ���ļ�ʱ
	{
		// �򿪻򴴽�Excel�ļ�
		m_Database->OpenEx(m_sDsn, CDatabase::noOdbcDialog);

		// ������¼������ѯ��
		m_rSheet = new CRecordset( m_Database );
		m_sSql.Format("SELECT * FROM [%s$A1:IV65536]", m_sSheetName);
		try
		{
			// ��ѯ��
			m_rSheet->Open(CRecordset::forwardOnly, m_sSql, CRecordset::readOnly);
		}
		catch(...)
		{
			// ������
			delete m_rSheet;
			m_rSheet = NULL;
			m_Database->Close();
			return false;
		}

		// �õ�����
		m_dTotalColumns = m_rSheet->m_nResultCols;

		if (m_dTotalColumns != 0)
		{
			m_aRows.RemoveAll();
			m_stempString.Empty();
			m_bAppend = true;
			m_dTotalRows++;					// ������
			
			// ��ȡ����(��ͷ)�ֶ���
			for (int i = 0; i < m_dTotalColumns; i++)
			{
				m_stempSql = m_rSheet->m_rgODBCFieldInfos[i].m_strName;
				m_aFieldNames.Add(m_stempSql);

				// �������кϲ���һ���ַ�����
				if (i != m_dTotalColumns-1) // �������һ��
				{
					m_stempString = m_stempString + "\"" + m_stempSql + "\"" + m_sSeparator;
				}
				else						// ���һ��
				{	
					m_stempString = m_stempString + "\"" + m_stempSql + "\"";
				}				
			}
			
			// �洢�ڴ�������(��ͷ)
			m_aRows.Add(m_stempString);

			// ��ȡ���洢�ڴ���������
			while (!m_rSheet->IsEOF())
			{
				m_dTotalRows++;							// ������

				try
				{
					// ��ȡһ����������
					m_stempString.Empty();
					for (short column = 0; column < m_dTotalColumns; column++)
					{
						m_rSheet->GetFieldValue(column, m_stempSql);

						// �������кϲ���һ���ַ�����
						if (column != m_dTotalColumns-1) // ���������ʱ
						{
							m_stempString = m_stempString + "\"" + m_stempSql + "\"" + m_sSeparator;
						}
						else							// ���һ��ʱ
						{	
							m_stempString = m_stempString + "\"" + m_stempSql + "\"";
						}
					}

					// �洢�ڴ����Ѱ�������
					m_aRows.Add(m_stempString);
					m_rSheet->MoveNext();
				}
				catch (...)
				{
					m_sLastError = "��ȡ��ʱ��������\n";
					delete m_rSheet;
					m_rSheet = NULL;
					m_Database->Close();

					return false;
				}
			}		
		}
		
		m_rSheet->Close();
		delete m_rSheet;
		m_rSheet = NULL;
		m_Database->Close();
		m_dCurrentRow = 1;

		return true;
	}
	else			// ���ļ���ָ���ָ����ָ����ı��ļ�ʱ
	{
		try
		{
			CFile *File = NULL;
			File = new CFile(m_sFile, CFile::modeRead | CFile::shareDenyNone);
			if (File != NULL)
			{
				CArchive *Archive = NULL;
				Archive = new CArchive(File, CArchive::load);
				if (Archive != NULL)
				{
					m_aRows.RemoveAll();
					// ��ȡ���洢�ڴ���������
					while(Archive->ReadString(m_stempString))
					{
						m_aRows.Add(m_stempString);
					}
					ReadRow(m_aFieldNames, 1); // �õ����е��ֶ���(��ͷ)
					delete Archive;
					delete File;

					// �õ�������
					m_dTotalRows = m_aRows.GetSize();

					// ��ȡ���������
					for (int i = 0; i < m_aRows.GetSize(); i++)
					{
						ReadRow(m_atempArray, i);
						if (m_atempArray.GetSize() > m_dTotalColumns)
						{
							m_dTotalColumns = m_atempArray.GetSize();
						}
					}

					if (m_dTotalColumns != 0)
					{
						m_bAppend = true;
					}
					return true;
				}
				delete File;
			}
		}
		catch(...)
		{
		}

		m_sLastError = "���ļ�ʱ��������\n";

		return false;
	}
}

// ת��Excle����ĸ�к�Ϊ��Ӧ�����к�
short CSpreadSheet::CalculateColumnNumber(CString column, bool Auto)
{
	if (Auto)
	{	
		column.MakeUpper();

		int firstLetter, secondLetter;
		if (1 == column.GetLength())
		{
			firstLetter = column.GetAt(0);
			return (firstLetter - 65 + 1);									// ASCII���д�д��ĸAΪ65
		}
		else if (2 == column.GetLength())
		{
			firstLetter		= column.GetAt(0);
			secondLetter	= column.GetAt(1);
			return ((firstLetter - 65 + 1)*26 + (secondLetter - 65 + 1));	// ASCII���д�д��ĸAΪ65
		}
	}

	// ����Ƿ�����Ч���ֶ�������Чֱ�ӷ���
	for (int i = 0; i < m_aFieldNames.GetSize(); i++)
	{
		if (!column.Compare(m_aFieldNames.GetAt(i)))
		{
			return (i + 1);
		}
	}

	m_sLastError = "��Ч�ֶ�������ĸ�к�\n";

	return 0;	
}

// ��ȡExcel-ODBC������������
void CSpreadSheet::GetExcelDriver()
{
	char szBuf[2001];
	WORD cbBufMax = 2000;
	WORD cbBufOut;
	char *pszBuf = szBuf;

	// ��ȡ�Ѱ�װ������������� (��Ҫ����ͷ�ļ�"odbcinst.h")
	if(!SQLGetInstalledDrivers(szBuf,cbBufMax,& cbBufOut))
	{
		m_sExcelDriver = "";
	}
	
	// Ѱ��Excel��������...
	do
	{
		if( NULL != strstr( pszBuf, "Excel" ) )
		{
			// �ҵ�!
			m_sExcelDriver = CString( pszBuf );
			break;
		}
		pszBuf = strchr( pszBuf, '\0' ) + 1;
	}
	while( '\0' != pszBuf[1] );
}

#endif