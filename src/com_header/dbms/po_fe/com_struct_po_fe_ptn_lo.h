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

#ifndef DB_PO_FE_PTN_LO_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_FE_PTN_LO_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_fe_ptn_lo
{
	_db_po_fe_ptn_lo()
	{	  
		nPtnRangeType			= 0;
		nPtnObjType				= 0;
		nNewFileSendType		= 0;

		nPtnUnitNum				= 0;
		nPtnChkValue			= 0;
	}

	DB_PO_HEADER		tDPH;		

	UINT32				nPtnRangeType;
	UINT32				nPtnObjType;
	UINT32				nNewFileSendType;

	String				strSavePath;
	String				strSaveName;
	String				strFileHash;
	String				strPtnVersion;
	UINT32				nPtnUnitNum;
	UINT32				nPtnChkValue;
}DB_PO_FE_PTN_LO, *PDB_PO_FE_PTN_LO;

typedef list<DB_PO_FE_PTN_LO>				TListDBPoFePtnLo;
typedef TListDBPoFePtnLo::iterator			TListDBPoFePtnLoItor;

typedef map<UINT32, DB_PO_FE_PTN_LO>		TMapDBPoFePtnLo;
typedef TMapDBPoFePtnLo::iterator			TMapDBPoFePtnLoItor;

#endif //DB_PO_FE_PTN_LO_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



