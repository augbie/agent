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

#ifndef DB_PO_FA_PROC_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_FA_PROC_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_fa_proc
{
	_db_po_fa_proc()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_FA_PROC, *PDB_PO_FA_PROC;

typedef list<DB_PO_FA_PROC>					TListDBPoFaProc;
typedef TListDBPoFaProc::iterator			TListDBPoFaProcItor;

typedef map<UINT32, DB_PO_FA_PROC>			TMapDBPoFaProc;
typedef TMapDBPoFaProc::iterator			TMapDBPoFaProcItor;
//---------------------------------------------------------------------------

typedef struct _db_po_fa_proc_pkg
{
	_db_po_fa_proc_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_FA_PROC_PKG, *PDB_PO_FA_PROC_PKG;

typedef list<DB_PO_FA_PROC_PKG>				TListDBPoFaProcPkg;
typedef TListDBPoFaProcPkg::iterator		TListDBPoFaProcPkgItor;

typedef map<UINT32, DB_PO_FA_PROC_PKG>		TMapDBPoFaProcPkg;
typedef TMapDBPoFaProcPkg::iterator			TMapDBPoFaProcPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_fa_proc_unit
{
	_db_po_fa_proc_unit()
	{
		nBlockMode		= 0;		
	}

	DB_PO_HEADER		tDPH;

	UINT32				nBlockMode;
	String				strFilePath;
	String				strFileComp;
	String				strFileDesc;
	String				strFileHash;
	String				strFileSign;
	String				strFileSignComp;

}DB_PO_FA_PROC_UNIT, *PDB_PO_FA_PROC_UNIT;

typedef list<DB_PO_FA_PROC_UNIT>			TListDBPoFaProcUnit;
typedef TListDBPoFaProcUnit::iterator		TListDBPoFaProcUnitItor;

typedef map<UINT32, DB_PO_FA_PROC_UNIT>		TMapDBPoFaProcUnit;
typedef TMapDBPoFaProcUnit::iterator		TMapDBPoFaProcUnitItor;
//---------------------------------------------------------------------------

#endif //DB_PO_FA_PROC_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



