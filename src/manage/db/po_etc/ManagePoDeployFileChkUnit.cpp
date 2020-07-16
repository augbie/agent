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
#include "ManagePoDeployFileChkUnit.h"

//---------------------------------------------------------------------------

CManagePoDeployFileChkUnit*	t_ManagePoDeployFileChkUnit = NULL;

//---------------------------------------------------------------------------

CManagePoDeployFileChkUnit::CManagePoDeployFileChkUnit()
{
	t_DBMgrPoDeployFileChkUnit	= new CDBMgrPoDeployFileChkUnit();
}
//---------------------------------------------------------------------------

CManagePoDeployFileChkUnit::~CManagePoDeployFileChkUnit()
{
	if(t_DBMgrPoDeployFileChkUnit)	{	delete t_DBMgrPoDeployFileChkUnit;	t_DBMgrPoDeployFileChkUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoDeployFileChkUnit::LoadDBMS()
{
	TListDBPoDeployFileChkUnit tDBPoDeployFileChkUnitList;
    TListDBPoDeployFileChkUnitItor begin, end;
	if(SetER(t_DBMgrPoDeployFileChkUnit->LoadExecute(&tDBPoDeployFileChkUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoDeployFileChkUnitList.begin();	end = tDBPoDeployFileChkUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoDeployFileChkUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_DEPLOY_FILE_CHK_UNIT pdpdfcu 			= NULL;
	{
		if( (pdpdfcu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_deploy_file_chk_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		m_strHashValue = SPrintf("%s,"
							"%u,%u,%u,%s,", 
							GetHdrHashInfo(pdpdfcu).c_str(),
							pdpdfcu->nCompType, pdpdfcu->nCompValType, pdpdfcu->nCompOpType, pdpdfcu->strCompValue.c_str());

		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoDeployFileChkUnit::AddPoDeployFileChkUnit(DB_PO_DEPLOY_FILE_CHK_UNIT&	dpdfcu)
{
	if(SetER(t_DBMgrPoDeployFileChkUnit->InsertExecute(&dpdfcu)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpdfcu.tDPH.nID, dpdfcu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoDeployFileChkUnit::EditPoDeployFileChkUnit(DB_PO_DEPLOY_FILE_CHK_UNIT&	dpdfcu)
{
	PDB_PO_DEPLOY_FILE_CHK_UNIT pdpdfcu = FindItem(dpdfcu.tDPH.nID);
	if(!pdpdfcu)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoDeployFileChkUnit->UpdateExecute(&dpdfcu)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpdfcu.tDPH.nID, dpdfcu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoDeployFileChkUnit::DelPoDeployFileChkUnit(UINT32 nID)
{
	PDB_PO_DEPLOY_FILE_CHK_UNIT pdpdfcu = FindItem(nID);
	if(!pdpdfcu)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoDeployFileChkUnit->DeleteExecute(pdpdfcu->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoDeployFileChkUnit::ApplyPoDeployFileChkUnit(DB_PO_DEPLOY_FILE_CHK_UNIT&	dpdfcu)
{
	if(FindItem(dpdfcu.tDPH.nID))
	{
		return EditPoDeployFileChkUnit(dpdfcu);
	}
	return AddPoDeployFileChkUnit(dpdfcu);
}
//---------------------------------------------------------------------------


String					CManagePoDeployFileChkUnit::GetName(UINT32 nID)
{
	PDB_PO_DEPLOY_FILE_CHK_UNIT pdpdfcu = FindItem(nID);
    if(!pdpdfcu)	return "";
    return pdpdfcu->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoDeployFileChkUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoDeployFileChkUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoDeployFileChkUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_DEPLOY_FILE_CHK_UNIT pdpdfcu = FindItem(nID);
	if(!pdpdfcu)	return -1;

	return SetPkt(pdpdfcu, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoDeployFileChkUnit::SetPkt(PDB_PO_DEPLOY_FILE_CHK_UNIT pdpdfcu, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpdfcu->tDPH);

	SendToken.TokenAdd_32(pdpdfcu->nCompType);
	SendToken.TokenAdd_32(pdpdfcu->nCompValType);
	SendToken.TokenAdd_32(pdpdfcu->nCompOpType);
	SendToken.TokenAdd_String(pdpdfcu->strCompValue);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoDeployFileChkUnit::GetPkt(MemToken& RecvToken, DB_PO_DEPLOY_FILE_CHK_UNIT& dpdfcu)
{
	if (!RecvToken.TokenDel_DPH(dpdfcu.tDPH))						goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dpdfcu.nCompType))					goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dpdfcu.nCompValType))				goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dpdfcu.nCompOpType))					goto	INVALID_PKT;
	if ( RecvToken.TokenDel_String(dpdfcu.strCompValue) < 0)		goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



