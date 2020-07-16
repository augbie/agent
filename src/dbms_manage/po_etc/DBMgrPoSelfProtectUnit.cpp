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
#include "DBMgrPoSelfProtectUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoSelfProtectUnit*		t_DBMgrPoSelfProtectUnit = NULL;

//---------------------------------------------------------------------------

CDBMgrPoSelfProtectUnit::CDBMgrPoSelfProtectUnit()
{
	m_strDBTName = "po_self_protect_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoSelfProtectUnit::~CDBMgrPoSelfProtectUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoSelfProtectUnit::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoSelfProtectUnit::LoadDB(TListDBPoSelfProtectUnit& tDBPoSelfProtectUnitList)
{
    UINT32 nReadCnt = 0;
    DB_PO_SELF_PROTECT_UNIT dpspu;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", protect_type, protect_info"
						" FROM po_self_protect_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpspu.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);
		dpspu.nProtectType			= GetDBField_UInt(nIndex++);
		dpspu.strProtectInfo		= GetDBField_String(nIndex++);
		
        tDBPoSelfProtectUnitList.push_back(dpspu);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoSelfProtectUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoSelfProtectUnit::InsertPoSelfProtectUnit(DB_PO_SELF_PROTECT_UNIT& dpspu)
{
	DB_PO_HEADER& tDPH = dpspu.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_self_protect_unit("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", protect_type"
						", protect_info"
						") VALUES (%s"
                        ", %u"
						", '%s');",
                        GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						dpspu.nProtectType, 
						dpspu.strProtectInfo.c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoSelfProtectUnit::UpdatePoSelfProtectUnit(DB_PO_SELF_PROTECT_UNIT& dpspu)
{
	DB_PO_HEADER& tDPH = dpspu.tDPH;

	m_strQuery = SPrintf("UPDATE po_self_protect_unit SET %s"
						", protect_type=%u"
						", protect_info='%s'"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(), 
						dpspu.nProtectType, 
						dpspu.strProtectInfo.c_str(),
                        tDPH.nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_UPDATE_FAIL;

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoSelfProtectUnit::DeletePoSelfProtectUnit(UINT32 nID)
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

INT32	CDBMgrPoSelfProtectUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoSelfProtectUnit* ptDBList = (TListDBPoSelfProtectUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoSelfProtectUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_SELF_PROTECT_UNIT pd_t = (PDB_PO_SELF_PROTECT_UNIT)lpTemplet;

    return InsertPoSelfProtectUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoSelfProtectUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_SELF_PROTECT_UNIT pd_t = (PDB_PO_SELF_PROTECT_UNIT)lpTemplet;

    return UpdatePoSelfProtectUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoSelfProtectUnit::DeleteExecute(UINT32 nID)
{
	return DeletePoSelfProtectUnit(nID);
}
//---------------------------------------------------------------------------






