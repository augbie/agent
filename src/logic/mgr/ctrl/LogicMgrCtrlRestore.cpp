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
#include "LogicMgrCtrlRestore.h"
//---------------------------------------------------------------------------

CLogicMgrCtrlRestore*		t_LogicMgrCtrlRestore = NULL;

//---------------------------------------------------------------------------

CLogicMgrCtrlRestore::CLogicMgrCtrlRestore()
{
	m_strLogicName		= "ctrl restore";

	m_nControlType		= SS_CONTROL_TYPE_CONTROL_RESTORE_CTRL;
	m_nEvtSubType		= EVENT_SUBJECT_TYPE_ADMIN;
	m_nEvtObjType		= EVENT_OBJECT_TYPE_HOST;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_HOST_CTRL_RESTORE;
}
//---------------------------------------------------------------------------

CLogicMgrCtrlRestore::~CLogicMgrCtrlRestore()
{
}
//---------------------------------------------------------------------------

INT32		CLogicMgrCtrlRestore::AnalyzePkt_FromMgr_Ext()
{
	UINT32 nRtn = AZPKT_CB_RTN_SUCCESS;
	switch(m_nPktCode)
	{
		case G_CODE_COMMON_INFO:		nRtn = AnalyzePkt_FromMgr_Ext_GetRestoreList();				break;
		case G_CODE_COMMON_PROGRESS:	nRtn = AnalyzePkt_FromMgr_Ext_ExcuteRestore();				break;
		default:
		{
			nRtn = AZPKT_CB_RTN_PKT_NOT_DEFINE_CODE;
			break;
		}
	}

	return SetHdrAndRtn(nRtn);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrCtrlRestore::AnalyzePkt_FromMgr_Add_Ext()
{
	INT32	nConSessionID = 0;
//	ASIWINRESTORE_POINT_INFO stRestoreInfo;
	String strDescription;

	if (!RecvToken.TokenDel_32(nConSessionID))		return AZPKT_CB_RTN_PKT_INVALID;
	if (!RecvToken.TokenDel_32(m_nHostID))		return AZPKT_CB_RTN_PKT_INVALID;
//	if (RecvToken.TokenDel_String(stRestoreInfo.strDescription) < 0)		return AZPKT_CB_RTN_PKT_INVALID;
	if (RecvToken.TokenDel_String(strDescription) < 0)		return AZPKT_CB_RTN_PKT_INVALID;
	RecvToken.TokenSkip_Block();

	SendToken.TokenAdd_32(nConSessionID);
	SendToken.TokenAdd_32(m_nHostID);
	SendToken.TokenAdd_32(0);

	SendData(G_TYPE_CTL_RESTORE, G_CODE_COMMON_INFO, SendToken);
	SendToken.Clear();

	return AZPKT_CB_RTN_SUCCESS;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrCtrlRestore::AnalyzePkt_FromMgr_Del_Ext()
{
	INT32	nConSessionID = 0, nSequenceNumber = 0;

	if (!RecvToken.TokenDel_32(nConSessionID))		return AZPKT_CB_RTN_PKT_INVALID;
	if (!RecvToken.TokenDel_32(m_nHostID))		return AZPKT_CB_RTN_PKT_INVALID;
	if (!RecvToken.TokenDel_32(nSequenceNumber))		return AZPKT_CB_RTN_PKT_INVALID;
	RecvToken.TokenSkip_Block();

	SendToken.TokenAdd_32(nConSessionID);
	SendToken.TokenAdd_32(m_nHostID);
	SendToken.TokenAdd_32(nSequenceNumber);

	SendData(G_TYPE_CTL_RESTORE, m_nPktCode, SendToken);
	SendToken.Clear();

	return AZPKT_CB_RTN_SUCCESS;
}
//---------------------------------------------------------------------------   
INT32		CLogicMgrCtrlRestore::AnalyzePkt_FromMgr_Ext_ExcuteRestore()
{
	INT32	nConSessionID = 0, nSequenceNumber = 0;

	if (!RecvToken.TokenDel_32(nConSessionID))		return AZPKT_CB_RTN_PKT_INVALID;
	if (!RecvToken.TokenDel_32(m_nHostID))		return AZPKT_CB_RTN_PKT_INVALID;
	if (!RecvToken.TokenDel_32(nSequenceNumber))		return AZPKT_CB_RTN_PKT_INVALID;
	RecvToken.TokenSkip_Block();

	return AZPKT_CB_RTN_SUCCESS;
}
//---------------------------------------------------------------------------   
INT32		CLogicMgrCtrlRestore::AnalyzePkt_FromMgr_Ext_GetRestoreList()
{
	INT32 nConSessionID = 0;

	if( RecvToken.TokenDel_32(nConSessionID) < 0)		return AZPKT_CB_RTN_PKT_INVALID;
	if( RecvToken.TokenDel_32(m_nHostID) < 0)		return AZPKT_CB_RTN_PKT_INVALID;

	SendToken.TokenAdd_32(nConSessionID);
	SendToken.TokenAdd_32(m_nHostID);

	SendToken.TokenAdd_32(0);

	SendData(G_TYPE_CTL_RESTORE, m_nPktCode, SendToken);
	SendToken.Clear();

	return AZPKT_CB_RTN_SUCCESS;
}