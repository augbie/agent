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

#ifndef DB_PO_FA_ENV_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_FA_ENV_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_fa_env
{
	_db_po_fa_env()
	{	  
	}

	DB_PO_HEADER		tDPH;	

}DB_PO_FA_ENV, *PDB_PO_FA_ENV;

typedef list<DB_PO_FA_ENV>					TListDBPoFaEnv;
typedef TListDBPoFaEnv::iterator			TListDBPoFaEnvItor;

typedef map<UINT32, DB_PO_FA_ENV>			TMapDBPoFaEnv;
typedef TMapDBPoFaEnv::iterator				TMapDBPoFaEnvItor;
//---------------------------------------------------------------------------

typedef struct _db_po_fa_env_pkg
{
	_db_po_fa_env_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_FA_ENV_PKG, *PDB_PO_FA_ENV_PKG;

typedef list<DB_PO_FA_ENV_PKG>				TListDBPoFaEnvPkg;
typedef TListDBPoFaEnvPkg::iterator			TListDBPoFaEnvPkgItor;

typedef map<UINT32, DB_PO_FA_ENV_PKG>		TMapDBPoFaEnvPkg;
typedef TMapDBPoFaEnvPkg::iterator			TMapDBPoFaEnvPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_fa_env_unit
{
	_db_po_fa_env_unit()
	{
		nFilePtnType			= 0;
	}

	DB_PO_HEADER		tDPH;	

	UINT32				nFilePtnType;
	String				strFilePtnGlobal;

}DB_PO_FA_ENV_UNIT, *PDB_PO_FA_ENV_UNIT;

typedef list<DB_PO_FA_ENV_UNIT>				TListDBPoFaEnvUnit;
typedef TListDBPoFaEnvUnit::iterator		TListDBPoFaEnvUnitItor;

typedef map<UINT32, DB_PO_FA_ENV_UNIT>		TMapDBPoFaEnvUnit;
typedef TMapDBPoFaEnvUnit::iterator			TMapDBPoFaEnvUnitItor;
//---------------------------------------------------------------------------

#endif //DB_PO_FA_ENV_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



