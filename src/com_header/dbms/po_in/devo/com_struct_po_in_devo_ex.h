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

#ifndef DB_PO_IN_DEVO_EX_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_IN_DEVO_EX_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_in_devo_ex
{
	_db_po_in_devo_ex()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_DEVO_EX, *PDB_PO_IN_DEVO_EX;

typedef list<DB_PO_IN_DEVO_EX>					TListDBPoInDevOEx;
typedef TListDBPoInDevOEx::iterator				TListDBPoInDevOExItor;

typedef map<UINT32, DB_PO_IN_DEVO_EX>				TMapDBPoInDevOEx;
typedef TMapDBPoInDevOEx::iterator				TMapDBPoInDevOExItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_devo_ex_pkg
{
	_db_po_in_devo_ex_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_DEVO_EX_PKG, *PDB_PO_IN_DEVO_EX_PKG;

typedef list<DB_PO_IN_DEVO_EX_PKG>				TListDBPoInDevOExPkg;
typedef TListDBPoInDevOExPkg::iterator			TListDBPoInDevOExPkgItor;

typedef map<UINT32, DB_PO_IN_DEVO_EX_PKG>			TMapDBPoInDevOExPkg;
typedef TMapDBPoInDevOExPkg::iterator				TMapDBPoInDevOExPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_devo_ex_unit
{
	_db_po_in_devo_ex_unit()
	{
		nBlockType			= 0;
		nExPtn				= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nBlockType;
	UINT32				nExPtn;

}DB_PO_IN_DEVO_EX_UNIT, *PDB_PO_IN_DEVO_EX_UNIT;

typedef list<DB_PO_IN_DEVO_EX_UNIT>				TListDBPoInDevOExUnit;
typedef TListDBPoInDevOExUnit::iterator			TListDBPoInDevOExUnitItor;

typedef map<UINT32, DB_PO_IN_DEVO_EX_UNIT>		TMapDBPoInDevOExUnit;
typedef TMapDBPoInDevOExUnit::iterator			TMapDBPoInDevOExUnitItor;
//---------------------------------------------------------------------------


#endif //DB_PO_IN_DEVO_EX_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



