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

#ifndef DB_SITE_VULN_H_4D39CDDB_E289_4d56_9F98_FE42776F4467
#define DB_SITE_VULN_H_4D39CDDB_E289_4d56_9F98_FE42776F4467

typedef struct _db_site_vuln
{
	_db_site_vuln()
	{
		nID				= 0;
		nUsedFlag		= STATUS_USED_MODE_ON;
		nRegDate		= 0;
		nUsedMode		= 0;
		nAdminID		= 0;
		nExtOption		= 0;

		nClass			= 0;

		nSysType		= 0;
		nSysSPType		= 0;
		nSysArchType	= 0;

		nSupportOption	= 0;
		nRiskLevel		= SS_SITE_VULN_RISK_LEVEL_NONE;
		nDefScore		= 0;
	} 

	UINT32		nID ;
	UINT32		nUsedFlag;
	UINT32		nRegDate;
	UINT32		nUsedMode;
	UINT32		nAdminID;
	UINT32		nExtOption;

	UINT32		nClass;

	String		strName;
	String		strDescr;

	UINT64		nSysType;
	UINT32		nSysSPType;
	UINT32		nSysArchType;

	UINT32		    nSupportOption;
	UINT32			nRiskLevel;		// SS_SITE_VULN_RISK_LEVEL_XXX
	UINT32			nDefScore;		
	
}DB_SITE_VULN, *PDB_SITE_VULN;

typedef list<DB_SITE_VULN>				TListDBSiteVuln;
typedef TListDBSiteVuln::iterator		TListDBSiteVulnItor;

typedef map<UINT32, DB_SITE_VULN>		TMapDBSiteVuln;
typedef TMapDBSiteVuln::iterator		TMapDBSiteVulnItor;

//---------------------------------------------------------------------------------------

#endif //DB_SITE_VULN_H_4D39CDDB_E289_4d56_9F98_FE42776F4467




