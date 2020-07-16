/*
 * Copyright (C) 2020-2025 ASHINi corp. 
 * 
 * This library is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public 
 * License as published by the Free Software Foundation; either 
 * version 2.1 of the License, or (at your option) any later version. 
 * 
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * Lesser General Public License for more details. 
 * 
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library; if not, write to the Free Software 
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA 
 * 
 */

#include "stdafx.h"
#include "as_db_class.h"
#include "as_sqlite_util.h"

CASIDBUtil* t_SqliteDbUtil = NULL;

int	init_sqlite(char *pcLogMsg)
{
	if(t_SqliteDbUtil == NULL)
	{
		t_SqliteDbUtil = new CASIDBUtil();
		if(t_SqliteDbUtil == NULL)
			return -100;
	}
	return 0;
}

void free_sqlite()
{
	if(t_SqliteDbUtil != NULL)
	{
		delete t_SqliteDbUtil;
		t_SqliteDbUtil = NULL;
	}
}

int open_database(char *pcDBName, char *pcLogMsg)
{
	if(t_SqliteDbUtil == NULL)
		return -100;

	return t_SqliteDbUtil->OpenDatabase(pcDBName, pcLogMsg);
}

int create_database(char *pcDBName, char *pcLogMsg)
{
	if(t_SqliteDbUtil == NULL)
		return -100;

	return t_SqliteDbUtil->CreateDatabase(pcDBName, pcLogMsg);
}


int close_database(char *pcLogMsg)
{
	if(t_SqliteDbUtil == NULL)
		return -100;

	return t_SqliteDbUtil->CloseDatabase(pcLogMsg);
}

int query_execute(char *pcQuery, char *pcLogMsg)
{
	if(t_SqliteDbUtil == NULL)
		return -100;

	return t_SqliteDbUtil->ExecuteQuery(pcQuery, pcLogMsg);
}

int is_table_exist(char *pcQuery, char *pcLogMsg)
{
	if(t_SqliteDbUtil == NULL)
		return -100;
	return t_SqliteDbUtil->IsTableExist(pcQuery, pcLogMsg);
}
//---------------------------------------------------------------------------------

bool query_next()
{
	if(t_SqliteDbUtil == NULL)
		return false;
	return t_SqliteDbUtil->Next();
}
//---------------------------------------------------------------------------------

int get_field_count()
{
	if(t_SqliteDbUtil == NULL)
		return 0;
	return t_SqliteDbUtil->GetDBFieldCount();
}
//---------------------------------------------------------------------------------

int get_field_type(int nIndex)
{
	if(t_SqliteDbUtil == NULL)
		return 0;
	return t_SqliteDbUtil->GetDBFieldType(nIndex);
}

int get_field_int(int nIndex)
{
	if(t_SqliteDbUtil == NULL)
		return 0;
	return t_SqliteDbUtil->GetDBFieldInt(nIndex);
}

char *get_field_string(int nIndex)
{
	if(t_SqliteDbUtil == NULL)
		return (char *)"";

	return t_SqliteDbUtil->GetDBFieldString(nIndex);

}
//---------------------------------------------------------------------------------

float get_field_float(int nIndex)
{
	if(t_SqliteDbUtil == NULL)
		return (float)0.0;
	return t_SqliteDbUtil->GetDBFieldFloat(nIndex);
}


int get_field_bytes(int nIndex)
{
	if(t_SqliteDbUtil == NULL)
		return 0;
	return t_SqliteDbUtil->GetDBFieldBytes(nIndex);
}

char *get_db_field_blob(int nIndex)
{
	if(t_SqliteDbUtil == NULL)
		return (char *)"";
	return t_SqliteDbUtil->GetDBFieldBlob(nIndex);
}


