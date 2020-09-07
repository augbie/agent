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
#include "LogicPoFaClear.h"

//---------------------------------------------------------------------------

CLogicPoFaClear*		t_LogicPoFaClear = NULL;

//---------------------------------------------------------------------------

CLogicPoFaClear::CLogicPoFaClear()
{	
	m_strLogicName		= "link po fa clear";
		
	m_nEvtSubType		= EVENT_SUBJECT_TYPE_USER;
	m_nEvtObjType		= EVENT_OBJECT_TYPE_USER;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_POLICY_FA_CLEAR;
}
//---------------------------------------------------------------------------

CLogicPoFaClear::~CLogicPoFaClear()
{

}
//---------------------------------------------------------------------------

INT32	CLogicPoFaClear::AnalyzePkt_FromLink_Ext()
{
	switch(m_nPktCode)
	{
		case G_CODE_COMMON_SCAN:		AnalyzePkt_FromLink_Ext_Scan();		break;
		default:						break;		
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32		CLogicPoFaClear::AnalyzePkt_FromLink_Ext_Scan()
{
	m_nEvtOpType = EVENT_OPERATION_TYPE_SCAN;
	PDB_PO_FA_CLEAR_UNIT pdpfcu = NULL;

	if(!RecvToken.TokenDel_32(m_nRecvID))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

	{
		pdpfcu = t_ManagePoFaClearUnit->FindItem(m_nRecvID);
		if(!pdpfcu)
		{
			WriteLogE("[%s] not find unit information : [%d][%d]", m_strLogicName.c_str(), g_nErrRtn, m_nRecvID);			
			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
		}
	}

	{
		MEM_FIND_ORDER_INFO tMFOI;
		{
			tMFOI.nPoID			= m_nRecvID;
			tMFOI.nOpType		= SS_LOG_DOC_OP_TYPE_SCHEDULE_DEMAND;
			tMFOI.nNextOp		= G_CODE_COMMON_FIND;
			tMFOI.nNotiPg		= STATUS_USED_MODE_ON;
		}
		
		t_LogicMgrPoFaClear->ApplyPolicy_Unit(pdpfcu, tMFOI);
	}

	{
		SendToken.TokenAdd_32(m_nRecvID);
		SendToken.TokenAdd_32(GetCurrentDateTimeInt());
		SendData_Link(m_nPktType, m_nPktCode, SendToken);
		SendToken.Clear();
	}
	
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicPoFaClear::AnalyzePkt_FromLink_Del_Ext()
{
	INT32 nPolicyType = 0;

	TListDBLogDoc tLogDocList;
	if(!RecvToken.TokenDel_32(m_nRecvNum))					return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_LOG_DOC dld;
		if(t_ManageLogDoc->GetPkt_Link(RecvToken, dld))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);		
		tLogDocList.push_back(dld);
		nPolicyType = dld.nPolicyType;
	}

	{
		INT32 nRtn = 0;
		TListDBLogDocItor begin, end;
		begin = tLogDocList.begin();	end = tLogDocList.end();
		for(begin; begin != end; begin++)
		{
			UINT32 nTempID = begin->nID;
			begin->nID = 0;

			nRtn = t_LogicMgrLogDoc->DeleteLogDoc(*begin);
			if(nRtn && !begin->nBackupTime)
			{
				continue;
			}
			m_tIDList.push_back(nTempID);
		}
		t_ManageDocDeleteInfo->UpdateDocDeleteInfo();
		t_LogicDocDeleteInfo->SendPkt_DocDeleteInfo_Edit();
	}

	{
		MEM_FIND_ORDER_INFO tMFOI;
		tMFOI.nPoID				= nPolicyType;
		tMFOI.nOpType			= SS_LOG_DOC_OP_TYPE_SCAN;

		if(GetUnitIDtoPolicyType(nPolicyType) < FF_START_ORDER_ID_PO_FA_CLEAR)
			tMFOI.nOpType	= SS_LOG_DOC_OP_TYPE_SCHEDULE_DEMAND;

		tMFOI.nNotiTotalFind	= m_tIDList.size();

		if(tMFOI.nNotiTotalFind > 0)
			t_LogicPoFaClear->SendPkt_Del_Last(tMFOI);
	}

	{
		SendToken.TokenAdd_IDList(m_tIDList);
		SendData_Link(m_nPktType, m_nPktCode, SendToken);
		SendToken.Clear();
	}
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS_END);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicPoFaClear::SendPkt_Init(UINT32 nID, UINT32 nLastChkTime)
{
	SendToken.TokenAdd_32(nID);
	SendToken.TokenAdd_32(nLastChkTime);
	SendData_Link(G_TYPE_PO_FA_CLEAR, G_CODE_COMMON_INIT, SendToken);
	SendToken.Clear();
	return;
}
//---------------------------------------------------------------------------

void		CLogicPoFaClear::SendPkt_Find(PDB_LOG_DOC pdld)
{
	SendToken.Set(1024);
	SendToken.TokenAdd_32(1);
	t_ManageLogDoc->SetPkt_Link(pdld, SendToken);
	SendData_Link(G_TYPE_PO_FA_CLEAR, G_CODE_COMMON_FIND, SendToken);
	SendToken.Clear();
}
//---------------------------------------------------------------------------

void		CLogicPoFaClear::SendPkt_Progress(PMEM_FIND_ORDER_INFO pMFOI)
{
	SendToken.TokenAdd_32(pMFOI->nPoID);
	SendToken.TokenAdd_32(pMFOI->nNotiPgTotal);
	SendToken.TokenAdd_32(pMFOI->nNotiPgEnd);

	SendData_Link(G_TYPE_PO_FA_CLEAR, G_CODE_COMMON_PROGRESS, SendToken);
	SendToken.Clear();
	return;
}
//---------------------------------------------------------------------------

void		CLogicPoFaClear::SendPkt_End(MEM_FIND_ORDER_INFO& tMFOI)
{
	SendToken.TokenAdd_32(tMFOI.nPoID);
	SendData_Link(G_TYPE_PO_FA_CLEAR, G_CODE_COMMON_END, SendToken);
	SendToken.Clear();
	return;
}
//---------------------------------------------------------------------------

void		CLogicPoFaClear::SendPkt_Del_Last(MEM_FIND_ORDER_INFO& tMFOI)
{
	SendPkt_Del_Last(tMFOI.nPoID, tMFOI.nOpType, tMFOI.nNotiTotalFind);
}
//---------------------------------------------------------------------------

void		CLogicPoFaClear::SendPkt_Del_Last(UINT32 nPolicyType, UINT32 nOpType, UINT32 nTotalDelCnt)
{
	SendToken.TokenAdd_32(nPolicyType);
	SendToken.TokenAdd_32(nOpType);
	SendToken.TokenAdd_32(nTotalDelCnt);
	SendData_Link(G_TYPE_PO_FA_CLEAR, G_CODE_COMMON_LAST, SendToken);
	SendToken.Clear();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
