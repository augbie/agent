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

#ifndef DB_PO_FA_CLEAR_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_FA_CLEAR_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_fa_clear
{
	_db_po_fa_clear()
	{
		nMDelDefScanID		= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nMDelDefScanID;

}DB_PO_FA_CLEAR, *PDB_PO_FA_CLEAR;

typedef list<DB_PO_FA_CLEAR>				TListDBPoFaClear;
typedef TListDBPoFaClear::iterator			TListDBPoFaClearItor;

typedef map<UINT32, DB_PO_FA_CLEAR>			TMapDBPoFaClear;
typedef TMapDBPoFaClear::iterator			TMapDBPoFaClearItor;
//---------------------------------------------------------------------------

typedef struct _db_po_fa_clear_pkg
{
	_db_po_fa_clear_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_FA_CLEAR_PKG, *PDB_PO_FA_CLEAR_PKG;

typedef list<DB_PO_FA_CLEAR_PKG>				TListDBPoFaClearPkg;
typedef TListDBPoFaClearPkg::iterator			TListDBPoFaClearPkgItor;

typedef map<UINT32, DB_PO_FA_CLEAR_PKG>			TMapDBPoFaClearPkg;
typedef TMapDBPoFaClearPkg::iterator			TMapDBPoFaClearPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_fa_clear_unit
{
	_db_po_fa_clear_unit()
	{
		nFilePtnType		= 0;
		nSchType			= 0;
		nSchTime			= 0;
		nScanType			= 0;
		nDelCount			= 0;
		nLimitSize			= 0;
		nLimitCnt			= 0;
		nChkFDTType			= 0;
		nChkFDTType			= 0;
		nChkFDTValue		= 0;
		nNetDriveMode		= 0;
		nDelMethod			= 0;

		nScanTime			= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nFilePtnType;
	String				strFilePtnLocal;
	UINT32				nSchType;
	UINT32				nSchTime;
	UINT32				nScanType;
	UINT32				nDelCount;
	UINT32				nLimitSize;
	UINT32				nLimitCnt;
	UINT32				nChkFDTType;
	UINT32				nChkFDTValue;
	String				strExPath;
	String				strInPath;
	String				strExePath;
	String				strExeCommand;
	UINT32				nNetDriveMode;
	UINT32				nDelMethod;

	UINT32				nScanTime;

}DB_PO_FA_CLEAR_UNIT, *PDB_PO_FA_CLEAR_UNIT;

typedef list<DB_PO_FA_CLEAR_UNIT>			TListDBPoFaClearUnit;
typedef TListDBPoFaClearUnit::iterator		TListDBPoFaClearUnitItor;

typedef map<UINT32, DB_PO_FA_CLEAR_UNIT>	TMapDBPoFaClearUnit;
typedef TMapDBPoFaClearUnit::iterator		TMapDBPoFaClearUnitItor;
//---------------------------------------------------------------------------

#endif //DB_PO_FA_CLEAR_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



