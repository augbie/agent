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

#ifndef DB_PTN_DEPLOY_H_5DBB6BFC_032B_42a5_81C6_C86A909331BE
#define DB_PTN_DEPLOY_H_5DBB6BFC_032B_42a5_81C6_C86A909331BE


typedef struct _db_ptn_deploy
{
	_db_ptn_deploy()
	{
		nID					= 0;
		nUsedMode			= 1;

		nType				= 0;

		nSysType			= 0;
		nSysSPType			= 0;
		nSysArchType		= 0;

		nMatchPackage		= 0;
		nMatchPolicy		= 0;
		nMatchControl		= 0;

		nDnFileType			= 0;	
	}

	UINT32		nID;
	UINT32		nUsedMode;

	UINT32		nType;

	UINT64		nSysType;
	UINT32		nSysSPType;
	UINT32		nSysArchType;

	UINT64		nMatchPackage;
	UINT64		nMatchPolicy;
	UINT64		nMatchControl;

	String		strSvFileName;
	String		strSvFileHash;

	UINT32		nDnFileType;
	String		strDnFilePath;
	String		strDnFileName;
	String		strDnFileHash;

}DB_PTN_DEPLOY, *PDB_PTN_DEPLOY;

typedef list<DB_PTN_DEPLOY>			TListDBPtnDeploy;
typedef TListDBPtnDeploy::iterator	TListDBPtnDeployItor;

typedef map<UINT32, DB_PTN_DEPLOY>	TMapDBPtnDeploy;
typedef TMapDBPtnDeploy::iterator	TMapDBPtnDeployItor;

#endif /*DB_PTN_DEPLOY_H_5DBB6BFC_032B_42a5_81C6_C86A909331BE*/



