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
#include "ManageLogRs.h"

//---------------------------------------------------------------------------

CManageLogRs*	t_ManageLogRs = NULL;

//---------------------------------------------------------------------------

CManageLogRs::CManageLogRs()
{
	t_DBMgrLogRs	= new CDBMgrLogRs();
}
//---------------------------------------------------------------------------

CManageLogRs::~CManageLogRs()
{
	if(t_DBMgrLogRs)	{	delete t_DBMgrLogRs;	t_DBMgrLogRs = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManageLogRs::LoadDBMS()
{
	UINT32 nLogMode = 0, nLogNum = 0;
	{
		PDB_ENV_LOG pdel = t_ManageEnvLog->FindItem(DEFAULT_ID);
		if(pdel)
		{
			nLogMode = t_ManageEnvLog->GetLogValue(pdel->tAgtLoadModeMap, SS_ENV_LOG_INDEX_RS);
			nLogNum = t_ManageEnvLog->GetLogValue(pdel->tAgtLoadNumMap, SS_ENV_LOG_INDEX_RS);
			if(nLogMode == SS_ENV_LOG_LOAD_MODE_TYPE_DAY && nLogNum)
			{
				nLogNum = ((GetCurrentDateTimeInt() / 86400) - nLogNum) * 86400;
			}
		}
	}

	TListDBLogRs tDBLogRsList;	
	TListDBLogRsItor begin, end;
	if(SetER(t_DBMgrLogRs->LoadDB(nLogMode, nLogNum, tDBLogRsList)))
    {
    	return g_nErrRtn;
    }

	UINT32 nShowLogDay = 0;
	{
		PDB_PO_HOST_RUN pdphr = (PDB_PO_HOST_RUN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_HOST_RUN);
		if(pdphr)	nShowLogDay = ((GetCurrentDateTimeInt() / 86400) - pdphr->nShowLogDay) * 86400;		
	}

	begin = tDBLogRsList.begin();	end = tDBLogRsList.end();
	for(begin; begin != end; begin++)
	{
		if(ISSYNCSTEP(begin->nSyncSvrStep) && (begin->nRegDate < nShowLogDay))
		{
			continue;
		}

		AddItem(*begin);
	}    
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogRs::AddLogRs(DB_LOG_RS&	data)
{
	if(SetER(t_DBMgrLogRs->InsertExecute(&data)))
    {
    	return g_nErrRtn;
    }

    AddItem(data);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogRs::EditLogRs(DB_LOG_RS&	data)
{
	PDB_LOG_RS pdata = FindItem(data.nID);
	if(!pdata)	return ERR_INFO_NOT_EDIT_BECAUSE_NOT_FIND;

	if(SetER(t_DBMgrLogRs->UpdateExecute(&data)))
    {
    	return g_nErrRtn;
    }

    *pdata = data;

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogRs::DelLogRs(UINT32 nID)
{
	PDB_LOG_RS pdata = FindItem(nID);
	if(!pdata)	return ERR_INFO_NOT_DELETE_BECAUSE_NOT_FIND;

	if(SetER(t_DBMgrLogRs->DeleteExecute(pdata->nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32			CManageLogRs::SetPktSync(TListPVOID& tIDList)
{
	{
		TMapDBLogRsItor begin, end;
		begin = m_tMap.begin();	end = m_tMap.end();
		for(begin; begin != end; begin++)
		{
			if(ISSYNCSTEP(begin->second.nSyncSvrStep) || 
				(begin->second.nSkipTarget & SS_ENV_LOG_OPTION_FLAGE_SKIP_SAVE_SERVER))	continue;

			tIDList.push_back(&(begin->second));
		}

		if(tIDList.empty())	return -1;
	}
	return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


INT32					CManageLogRs::SetPkt(MemToken& SendToken)
{
    TListPVOID tSendList;

	{
		TMapDBLogRsItor begin, end;
		begin = m_tMap.begin();	end = m_tMap.end();
		for(begin; begin != end; begin++)
		{
			if(ISSYNCSTEP(begin->second.nSyncSvrStep) || 
				(begin->second.nSkipTarget & SS_ENV_LOG_OPTION_FLAGE_SKIP_SAVE_SERVER))	continue;

			tSendList.push_back(&(begin->second));
		}

		if(tSendList.empty())	return -1;
	}
			
	SendToken.TokenAdd_32(tSendList.size());
	{
		TListPVOIDItor begin, end;
		begin = tSendList.begin();	end = tSendList.end();
		for(begin; begin != end; begin++)
		{
			SetPkt((PDB_LOG_RS)(*begin), SendToken);
		}
	}	
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogRs::SetPkt_Link(MemToken& SendToken)
{
	SendToken.TokenAdd_32(m_tMap.size());
	{
		TMapDBLogRsItor begin, end;
		begin = m_tMap.begin();	end = m_tMap.end();
		for(begin; begin != end; begin++)
		{
			SetPkt(&(begin->second), SendToken);
		}
	}	
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogRs::SetPkt(PDB_LOG_RS pdata, MemToken& SendToken)
{
	SendToken.TokenAdd_32(pdata->nID);
	SendToken.TokenAdd_32(pdata->nRegDate);
	SendToken.TokenAdd_32(pdata->nEvtTime);
	SendToken.TokenAdd_32(pdata->nEvtErrCode);

	SendToken.TokenAdd_32(pdata->nNotifyType);
	SendToken.TokenAdd_32(pdata->nNotifyID);

	SendToken.TokenAdd_32(pdata->nHostID);
	SendToken.TokenAdd_32(pdata->nPolicyType);
	SendToken.TokenAdd_32(pdata->nOpType);

	SendToken.TokenAdd_32(pdata->nRegSvrID);
	SendToken.TokenAdd_32(pdata->nSyncSvrStep);

	SendToken.TokenAdd_32(pdata->nBlockType);
	SendToken.TokenAdd_32(pdata->nObjectType);

	SendToken.TokenAdd_String(pdata->strSubjectPath);
	SendToken.TokenAdd_String(pdata->strSubjectName);
	SendToken.TokenAdd_String(pdata->strObjectPath);
	SendToken.TokenAdd_String(pdata->strObjectName);
	SendToken.TokenAdd_StringW(pdata->strObjectPathW);

	SendToken.TokenAdd_32(pdata->nUserID);

	SendToken.TokenSet_Block();

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogRs::GetPkt(MemToken& RecvToken, DB_LOG_RS& data)
{
	if (!RecvToken.TokenDel_32(data.nID))						goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nRegDate))					goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nEvtTime))					goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nEvtErrCode))				goto INVALID_PKT;

	if (!RecvToken.TokenDel_32(data.nNotifyType))				goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nNotifyID))					goto INVALID_PKT;

	if (!RecvToken.TokenDel_32(data.nHostID))					goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nPolicyType))				goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nOpType))					goto INVALID_PKT;

	if (!RecvToken.TokenDel_32(data.nRegSvrID))					goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nSyncSvrStep))				goto INVALID_PKT;

	if (!RecvToken.TokenDel_32(data.nBlockType))				goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nObjectType))				goto INVALID_PKT;

	if ( RecvToken.TokenDel_String(data.strSubjectPath) < 0)	goto INVALID_PKT;
	if ( RecvToken.TokenDel_String(data.strSubjectName) < 0)	goto INVALID_PKT;
	if ( RecvToken.TokenDel_String(data.strObjectPath) < 0)		goto INVALID_PKT;
	if ( RecvToken.TokenDel_String(data.strObjectName) < 0)		goto INVALID_PKT;
	if ( RecvToken.TokenDel_StringW(data.strObjectPathW) < 0)	goto INVALID_PKT;

	if (!RecvToken.TokenDel_32(data.nUserID))					goto INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



