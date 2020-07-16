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

//---------------------------------------------------------------------------
#include "stdafx.h"
#include "com_struct.h"
#include "DBMgrEnvSelfProtectAgt.h"

//---------------------------------------------------------------------------

CDBMgrEnvSelfProtectAgt*		t_DBMgrEnvSelfProtectAgt;

//---------------------------------------------------------------------------

CDBMgrEnvSelfProtectAgt::CDBMgrEnvSelfProtectAgt()
{
	m_strDBTName = "env_self_protect_agt";
}
//---------------------------------------------------------------------------

CDBMgrEnvSelfProtectAgt::~CDBMgrEnvSelfProtectAgt()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrEnvSelfProtectAgt::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrEnvSelfProtectAgt::LoadDB(TListDBEnvSelfProtectAgt& tDBEnvSelfProtectAgtList)
{
    UINT32 nReadCnt = 0;
    DB_ENV_SELF_PROTECT_AGT despa;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", protect_type, protect_info, apply_perm"
						" FROM env_self_protect_agt WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = despa.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);
		despa.nProtectType			= GetDBField_UInt(nIndex++);
		despa.strProtectInfo		= GetDBField_String(nIndex++);
		despa.nApplyPerm			= GetDBField_UInt(nIndex++);
		
        tDBEnvSelfProtectAgtList.push_back(despa);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
		
	m_nLoadNumber = tDBEnvSelfProtectAgtList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrEnvSelfProtectAgt::InsertEnvSelfProtectAgt(DB_ENV_SELF_PROTECT_AGT& despa)
{
	DB_PO_HEADER& tDPH = despa.tDPH;

	m_strQuery = SPrintf("INSERT INTO env_self_protect_agt("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", protect_type, protect_info, apply_perm"
						") VALUES (%s"
                        ", %u, '%s', %u"
						");",
                        GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						despa.nProtectType, despa.strProtectInfo.c_str(), despa.nApplyPerm);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrEnvSelfProtectAgt::UpdateEnvSelfProtectAgt(DB_ENV_SELF_PROTECT_AGT& despa)
{
	DB_PO_HEADER& tDPH = despa.tDPH;

	m_strQuery = SPrintf("UPDATE env_self_protect_agt SET %s"
						", protect_type=%u, protect_info='%s', apply_perm=%u"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(), 
						despa.nProtectType, despa.strProtectInfo.c_str(), despa.nApplyPerm,
                        tDPH.nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_UPDATE_FAIL;

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrEnvSelfProtectAgt::DeleteEnvSelfProtectAgt(UINT32 nID)
{
	m_strQuery = SPrintf(DBMS_DEFAULT_QUERY_TYPE_DELETE, m_strDBTName.c_str(), nID);
    
	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_DELETE_FAIL;

    return 0;
}
//---------------------------------------------------------------------------  
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32	CDBMgrEnvSelfProtectAgt::LoadExecute(PVOID lpTempletList)
{
	TListDBEnvSelfProtectAgt* ptDBList = (TListDBEnvSelfProtectAgt*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrEnvSelfProtectAgt::InsertExecute(PVOID lpTemplet)
{
	PDB_ENV_SELF_PROTECT_AGT pd_t = (PDB_ENV_SELF_PROTECT_AGT)lpTemplet;

    return InsertEnvSelfProtectAgt(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrEnvSelfProtectAgt::UpdateExecute(PVOID lpTemplet)
{
	PDB_ENV_SELF_PROTECT_AGT pd_t = (PDB_ENV_SELF_PROTECT_AGT)lpTemplet;

    return UpdateEnvSelfProtectAgt(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrEnvSelfProtectAgt::DeleteExecute(UINT32 nID)
{
	return DeleteEnvSelfProtectAgt(nID);
}
//---------------------------------------------------------------------------






