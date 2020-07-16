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
#include "DBMgrPoDeployFileChkUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoDeployFileChkUnit*		t_DBMgrPoDeployFileChkUnit = NULL;

//---------------------------------------------------------------------------

CDBMgrPoDeployFileChkUnit::CDBMgrPoDeployFileChkUnit()
{
	m_strDBTName = "po_deploy_file_chk_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoDeployFileChkUnit::~CDBMgrPoDeployFileChkUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoDeployFileChkUnit::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoDeployFileChkUnit::LoadDB(TListDBPoDeployFileChkUnit& tDBPoDeployFileChkUnitList)
{
    UINT32 nReadCnt = 0;
    DB_PO_DEPLOY_FILE_CHK_UNIT dpdfcu;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", comp_type, comp_val_type, comp_op_type, comp_value"
						" FROM po_deploy_file_chk_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpdfcu.tDPH;
		tDPH						= GetDBField_PoHDR(nIndex);

		dpdfcu.nCompType			= GetDBField_UInt(nIndex++);
		dpdfcu.nCompValType		= GetDBField_UInt(nIndex++);
		dpdfcu.nCompOpType			= GetDBField_UInt(nIndex++);
		dpdfcu.strCompValue		= GetDBField_String(nIndex++);
		
        tDBPoDeployFileChkUnitList.push_back(dpdfcu);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoDeployFileChkUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoDeployFileChkUnit::InsertPoDeployFileChkUnit(DB_PO_DEPLOY_FILE_CHK_UNIT& dpdfcu)
{
	DB_PO_HEADER& tDPH = dpdfcu.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_deploy_file_chk_unit("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", comp_type, comp_val_type, comp_op_type, comp_value"
						") VALUES (%s"
                        ", %u, %u, %u, '%s'"
						");",
                        GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						dpdfcu.nCompType, dpdfcu.nCompValType, dpdfcu.nCompOpType, dpdfcu.strCompValue.c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoDeployFileChkUnit::UpdatePoDeployFileChkUnit(DB_PO_DEPLOY_FILE_CHK_UNIT& dpdfcu)
{
	DB_PO_HEADER& tDPH = dpdfcu.tDPH;

	m_strQuery = SPrintf("UPDATE po_deploy_file_chk_unit SET %s"
						", comp_type=%u, comp_val_type=%u, comp_op_type=%u, comp_value='%s'"
						"WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(), 
						dpdfcu.nCompType, dpdfcu.nCompValType, dpdfcu.nCompOpType, dpdfcu.strCompValue.c_str(),
                        tDPH.nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_UPDATE_FAIL;

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoDeployFileChkUnit::DeletePoDeployFileChkUnit(UINT32 nID)
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

INT32	CDBMgrPoDeployFileChkUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoDeployFileChkUnit* ptDBList = (TListDBPoDeployFileChkUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoDeployFileChkUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_DEPLOY_FILE_CHK_UNIT pd_t = (PDB_PO_DEPLOY_FILE_CHK_UNIT)lpTemplet;

    return InsertPoDeployFileChkUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoDeployFileChkUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_DEPLOY_FILE_CHK_UNIT pd_t = (PDB_PO_DEPLOY_FILE_CHK_UNIT)lpTemplet;

    return UpdatePoDeployFileChkUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoDeployFileChkUnit::DeleteExecute(UINT32 nID)
{
	return DeletePoDeployFileChkUnit(nID);
}
//---------------------------------------------------------------------------






