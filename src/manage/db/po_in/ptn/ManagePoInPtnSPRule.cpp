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
#include "ManagePoInPtnSPRule.h"

//---------------------------------------------------------------------------

CManagePoInPtnSPRule*	t_ManagePoInPtnSPRule = NULL;

//---------------------------------------------------------------------------

CManagePoInPtnSPRule::CManagePoInPtnSPRule()
{
	t_DBMgrPoInPtnSPRule	= new CDBMgrPoInPtnSPRule();
}
//---------------------------------------------------------------------------

CManagePoInPtnSPRule::~CManagePoInPtnSPRule()
{
	if(t_DBMgrPoInPtnSPRule)	{	delete t_DBMgrPoInPtnSPRule;	t_DBMgrPoInPtnSPRule = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInPtnSPRule::LoadDBMS()
{
	TListDBPoInPtnSPRule tDBPoInPtnSPRuleList;
    TListDBPoInPtnSPRuleItor begin, end;
	if(SetER(t_DBMgrPoInPtnSPRule->LoadExecute(&tDBPoInPtnSPRuleList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInPtnSPRuleList.begin();	end = tDBPoInPtnSPRuleList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInPtnSPRule::InitHash()
{
	String strOrgValue;
	m_strFullHash = "";

	TListID tIDList;
	TListIDItor begin, end;
	GetItemIDList(tIDList);

	begin = tIDList.begin();		end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_PTN_SP_RULE pdata 			= NULL;
		{
			if( (pdata = FindItem(*begin)) == NULL)
			{
				WriteLogE("not find po_in_ptn_sp_rule by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
				return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
			}
		}

		{
			String strOrgValueItem;
			strOrgValueItem = SPrintf("%s,"
									"%u,%u,%u,"
									"%u,%u,"
									"%u,%u,%u,"
									"%u,%s,"
									"%u,%u,",
									GetHdrHashInfo(pdata).c_str(),
									pdata->nTargetType, pdata->nTargetID, pdata->nFileID,
									pdata->nReqLevel, pdata->nReqDay,
									pdata->nConfirmType, pdata->nConfirmID, pdata->nConfirmRst,
									pdata->nUseDay, pdata->strFileKey.c_str(),
									pdata->nEvtDate, pdata->nEndDate);

			strOrgValue += strOrgValueItem;
		}
	}	
	
	if(strOrgValue.empty() == FALSE)
	{
		char pszHashValue[CHAR_MAX_SIZE] = {0, };
		SHAString(ASIHASH_SHA_LEN_TYPE_128, strOrgValue.c_str(), strOrgValue.length(), pszHashValue, CHAR_MAX_SIZE);
		m_strFullHash = pszHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

String					CManagePoInPtnSPRule::GetHash()
{
	return m_strFullHash;
}
//---------------------------------------------------------------------------

INT32					CManagePoInPtnSPRule::AddPoInPtnSPRule(DB_PO_IN_PTN_SP_RULE&	data)
{
	if(SetER(t_DBMgrPoInPtnSPRule->InsertExecute(&data)))
    {
    	return g_nErrRtn;
    }

    AddItem(data.tDPH.nID, data);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInPtnSPRule::EditPoInPtnSPRule(DB_PO_IN_PTN_SP_RULE&	data)
{
	PDB_PO_IN_PTN_SP_RULE pdata = FindItem(data.tDPH.nID);
	if(!pdata)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInPtnSPRule->UpdateExecute(&data)))
    {
    	return g_nErrRtn;
    }

    EditItem(data.tDPH.nID, data);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInPtnSPRule::DelPoInPtnSPRule(UINT32 nID)
{
	PDB_PO_IN_PTN_SP_RULE pdata = FindItem(nID);
	if(!pdata)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInPtnSPRule->DeleteExecute(pdata->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInPtnSPRule::ApplyPoInPtnSPRule(DB_PO_IN_PTN_SP_RULE&	data)
{
	if(FindItem(data.tDPH.nID))
	{
		return EditPoInPtnSPRule(data);
	}
	return AddPoInPtnSPRule(data);
}
//---------------------------------------------------------------------------

String					CManagePoInPtnSPRule::GetName(UINT32 nID)
{
	PDB_PO_IN_PTN_SP_RULE pdata = FindItem(nID);
    if(!pdata)	return "";
    return pdata->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInPtnSPRule::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInPtnSPRuleItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInPtnSPRule::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_PTN_SP_RULE pdata = FindItem(nID);
	if(!pdata)	return -1;

	return SetPkt(pdata, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInPtnSPRule::SetPkt(PDB_PO_IN_PTN_SP_RULE pdata, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdata->tDPH);

	SendToken.TokenAdd_32(pdata->nTargetID);
	SendToken.TokenAdd_32(pdata->nTargetType);
	SendToken.TokenAdd_32(pdata->nFileID);

	SendToken.TokenAdd_32(pdata->nReqLevel);
	SendToken.TokenAdd_32(pdata->nReqDay);

	SendToken.TokenAdd_32(pdata->nConfirmType);
	SendToken.TokenAdd_32(pdata->nConfirmID);
	SendToken.TokenAdd_32(pdata->nConfirmRst);

	SendToken.TokenAdd_32(pdata->nUseDay);
	SendToken.TokenAdd_String(pdata->strFileKey);

	SendToken.TokenAdd_32(pdata->nEvtDate);
	SendToken.TokenAdd_32(pdata->nEndDate);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInPtnSPRule::GetPkt(MemToken& RecvToken, DB_PO_IN_PTN_SP_RULE& data)
{
	if (!RecvToken.TokenDel_DPH(data.tDPH))						goto INVALID_PKT;

	if(!RecvToken.TokenDel_32(data.nTargetID))					goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nTargetType))				goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nFileID))					goto INVALID_PKT;

	if(!RecvToken.TokenDel_32(data.nReqLevel))					goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nReqDay))					goto INVALID_PKT;

	if(!RecvToken.TokenDel_32(data.nConfirmType))				goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nConfirmID))					goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nConfirmRst))				goto INVALID_PKT;

	if(!RecvToken.TokenDel_32(data.nUseDay))					goto INVALID_PKT;
	if( RecvToken.TokenDel_String(data.strFileKey) < 0)			goto INVALID_PKT;

	if(!RecvToken.TokenDel_32(data.nEvtDate))					goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nEndDate))					goto INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



