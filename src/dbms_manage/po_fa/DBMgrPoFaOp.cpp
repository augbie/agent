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
#include "DBMgrPoFaOp.h"

//---------------------------------------------------------------------------

CDBMgrPoFaOp*		t_DBMgrPoFaOp = NULL;

//---------------------------------------------------------------------------

CDBMgrPoFaOp::CDBMgrPoFaOp()
{
	m_strDBTName = "po_fa_op";
}
//---------------------------------------------------------------------------

CDBMgrPoFaOp::~CDBMgrPoFaOp()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoFaOp::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoFaOp::LoadDB(TListDBPoFaOp& tDBPoFaOpList)
{
    UINT32 nReadCnt = 0;
    DB_PO_FA_OP dpfp;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", sch_time, del_cnt, limit_size, limit_cnt"
						", scan_dt, chk_fdt_type, chk_fdt_value"
						", del_method"
						" FROM po_fa_op WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpfp.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);
		dpfp.nSchTime				= GetDBField_UInt(nIndex++);
		dpfp.nDelCount				= GetDBField_UInt(nIndex++);
		dpfp.nLimitSize				= GetDBField_UInt(nIndex++);
		dpfp.nLimitCnt				= GetDBField_UInt(nIndex++);

		dpfp.nScanTime				= GetDBField_UInt(nIndex++);

		dpfp.nChkFDTType			= GetDBField_UInt(nIndex++);
		dpfp.nChkFDTValue			= GetDBField_UInt(nIndex++);
		dpfp.nDelMethod				= GetDBField_UInt(nIndex++);
		
        tDBPoFaOpList.push_back(dpfp);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
		
	m_nLoadNumber = tDBPoFaOpList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoFaOp::InsertPoFaOp(DB_PO_FA_OP& dpfp)
{
	DB_PO_HEADER& tDPH = dpfp.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_fa_op("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", sch_time, del_cnt, limit_size, limit_cnt"
						", scan_dt"
						", chk_fdt_type, chk_fdt_value, del_method"
						") VALUES (%s"
						", %u, %u, %u, %u"
						", %u"
						", %u, %u, %u"
						");",
						GetPoHDRQuery_InsertValue(tDPH).c_str(),
						dpfp.nSchTime, dpfp.nDelCount, dpfp.nLimitSize, dpfp.nLimitCnt,
						dpfp.nScanTime,
						dpfp.nChkFDTType, dpfp.nChkFDTValue, dpfp.nDelMethod);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoFaOp::UpdatePoFaOp(DB_PO_FA_OP& dpfp)
{
	DB_PO_HEADER& tDPH = dpfp.tDPH;

	m_strQuery = SPrintf("UPDATE po_fa_op SET %s"
						", sch_time=%u, del_cnt=%u, limit_size=%u, limit_cnt=%u"
						", scan_dt=%u"
						", chk_fdt_type=%u, chk_fdt_value=%u, del_method=%u"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(),
						dpfp.nSchTime, dpfp.nDelCount, dpfp.nLimitSize, dpfp.nLimitCnt,
						dpfp.nScanTime,
						dpfp.nChkFDTType, dpfp.nChkFDTValue, dpfp.nDelMethod,
						tDPH.nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_UPDATE_FAIL;

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoFaOp::DeletePoFaOp(UINT32 nID)
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

INT32	CDBMgrPoFaOp::LoadExecute(PVOID lpTempletList)
{
	TListDBPoFaOp* ptDBList = (TListDBPoFaOp*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoFaOp::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_FA_OP pd_t = (PDB_PO_FA_OP)lpTemplet;

    return InsertPoFaOp(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoFaOp::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_FA_OP pd_t = (PDB_PO_FA_OP)lpTemplet;

    return UpdatePoFaOp(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoFaOp::DeleteExecute(UINT32 nID)
{
	return DeletePoFaOp(nID);
}
//---------------------------------------------------------------------------






