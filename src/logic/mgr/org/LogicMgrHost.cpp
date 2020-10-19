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
#include "LogicMgrHost.h"

//---------------------------------------------------------------------------

CLogicMgrHost*		t_LogicMgrHost = NULL;

//---------------------------------------------------------------------------

CLogicMgrHost::CLogicMgrHost()
{
	t_ManageHost		= new CManageHost();
	
	t_ManageHost->LoadDBMS();
	
	m_strLogicName = "logic mgr host";
	
	m_nControlType	= SS_CONTROL_TYPE_ORG_HOST;	
	m_nEvtObjType	= EVENT_OBJECT_TYPE_HOST;
	m_nEvtObjCode	= 0;
}
//---------------------------------------------------------------------------

CLogicMgrHost::~CLogicMgrHost()
{
	SAFE_DELETE(t_ManageHost)
}
//---------------------------------------------------------------------------

INT32		CLogicMgrHost::AnalyzePkt_FromMgr_Ext()
{
	UINT32 nRtn = AZPKT_CB_RTN_SUCCESS;
	switch(m_nPktCode)
	{
		case G_CODE_COMMON_SYNC:			nRtn = AnalyzePkt_FromMgr_Ext_Sync();		break;
		case G_CODE_HOST_SET_USED_FLAG:		nRtn = AnalyzePkt_FromMgr_Ext_Used();		break;
		case G_CODE_HOST_SET_NAME:			nRtn = AnalyzePkt_FromMgr_Ext_SetName();	break;
		default:
		{	
			nRtn = AZPKT_CB_RTN_PKT_NOT_DEFINE_CODE;
			break;
		}
	}

	return SetHdrAndRtn(nRtn);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32		CLogicMgrHost::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_HOST pdh = NULL;
	DB_HOST dh;

	if(t_ManageHost->GetPktHost(RecvToken, dh) < 0)
	{
		return AZPKT_CB_RTN_PKT_INVALID;
	}

	if( (pdh = t_ManageHost->FirstItem()) == NULL)
	{
		WriteLogE("[%s] not find host info", m_strLogicName.c_str());
		return AZPKT_CB_RTN_SUCCESS_END;
	}

	if(	pdh->strName.compare(dh.strName) ||
		pdh->strWorkGroup.compare(dh.strWorkGroup) ||
		pdh->strPriIP.compare(dh.strPriIP) ||
		pdh->strMac.compare(dh.strMac) ||
		pdh->strUserUnicode.compare(dh.strUserUnicode) ||
		CompareMapID(pdh->tPoIDMap, dh.tPoIDMap) ||
		CompareMapID(pdh->tPoSeqNoMap, dh.tPoSeqNoMap) ||
		CompareMapID(pdh->tPoTimeMap, dh.tPoTimeMap) ||
		pdh->nUserID != dh.nUserID)
	{
		pdh->strName = dh.strName;
		pdh->strWorkGroup = dh.strWorkGroup;
		pdh->strPriIP = dh.strPriIP;
		pdh->strNatIP = dh.strNatIP;
		pdh->strMac = dh.strMac;
		pdh->strUserUnicode = dh.strUserUnicode;
		pdh->nUserID		= dh.nUserID;
		
		pdh->tPoIDMap = dh.tPoIDMap;
		pdh->tPoSeqNoMap = dh.tPoSeqNoMap;
		pdh->tPoTimeMap = dh.tPoTimeMap;

		if(SetER(t_ManageHost->EditHost(*pdh)))
		{
			WriteLogE("[%s] edit host information fail : [%u]", m_strLogicName.c_str(), pdh->nID);
			return AZPKT_CB_RTN_SUCCESS_END;
		}

		{		
			t_ManageHost->SetPktHost(SendToken);
			SendData_Link(G_TYPE_HOST, G_CODE_COMMON_EDIT, SendToken);
			SendToken.Clear();
		}
	}	
	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrHost::AnalyzePkt_FromMgr_Ext_Sync()
{
	WriteLogN("[%s] sync policy host information start", m_strLogicName.c_str());

	t_LogicMgrAuth->SendMgrInitData_Polcy();
	t_LogicMgrAuth->SendMgrInitData_Sync();


	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrHost::AnalyzePkt_FromMgr_Ext_Used()
{
	UINT32	nStatus = 1;

	if (!RecvToken.TokenDel_32(nStatus))		return AZPKT_CB_RTN_PKT_INVALID;
	RecvToken.TokenSkip_Block();

	if (nStatus == USED_FLAG_TYPE_DELETE)
	{
		WriteLogN("[%s] change used mode : auto remove module", m_strLogicName.c_str());
		SetUninstallHost();
	}

	return AZPKT_CB_RTN_SUCCESS_END;
}

//---------------------------------------------------------------------------

INT32		CLogicMgrHost::AnalyzePkt_FromMgr_Ext_SetName()
{	
	DB_HOST dh;
	INT32 nRetVal = 0;
	FILE *fp = NULL;
	char acHostFile[MAX_PATH] = "/etc/hostname";
	char acHostBkFile[MAX_PATH] = "/etc/hostname.old";
	if(CheckPktResult(RecvToken))
	{
		WriteLogE("[%s] check pkt result is : [%x]", m_strLogicName.c_str(), m_nPktRst);
		return AZPKT_CB_RTN_RESULT_FAILED;
	}

	if( RecvToken.TokenDel_String(dh.strName) < 0)
	{
		WriteLogE("[%s] fail to get host name", m_strLogicName.c_str());
		return AZPKT_CB_RTN_PKT_INVALID;
	}

	if(is_file(acHostFile) == 0)
		MoveFileEx(acHostFile, acHostBkFile);

	fp = fopen(acHostFile, "w");
	if(fp == NULL)
	{
		MoveFileEx(acHostBkFile, acHostFile);
		WriteLogE("[%s] fail to open %s : [%d]", m_strLogicName.c_str(), acHostFile, errno);
		return AZPKT_CB_RTN_RESULT_FAILED;
	}
	fwrite(dh.strName.c_str(), 1, dh.strName.length(), fp);
	fclose(fp);
	
	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicMgrHost::SendPkt_Edit()
{
	INT32 nSendPkt = 1;
	DB_HOST dh;
	{
//		CHAR szBuf[CHAR_MAX_SIZE] = {0, };

		dh.strName		= t_EnvInfoOp->GetComputerName();
/*
		{
			dh.strWorkGroup = szBuf;
			ZeroMemoryExt(szBuf);
		}
*/
		dh.strPriIP = t_EnvInfoOp->m_strPriIPAddr;
		dh.strMac = t_EnvInfoOp->m_strPriMacAddr;
		dh.strUserUnicode = t_EnvInfoOp->GetUserUniCode();		
	}

	PDB_HOST pdh = t_ManageHost->FirstItem();
	if(!pdh)
	{
		WriteLogE("[%s] not find host first item..", m_strLogicName.c_str());
		goto SEND_PKT;
	}
	do 
	{
		if( pdh->strName != dh.strName ||
//			pdh->strWorkGroup != dh.strWorkGroup ||
			pdh->strPriIP != dh.strPriIP ||
			pdh->strMac != dh.strMac ||
			pdh->strUserUnicode != dh.strUserUnicode)
		{
			break;
		}
		dh.strPriIP = t_EnvInfoOp->m_strPriIPAddr;
		dh.strMac = t_EnvInfoOp->m_strPriMacAddr;
		dh.strUserUnicode = t_EnvInfoOp->GetUserUniCode();		
		nSendPkt = 0;
	} while (FALSE);

	if(!nSendPkt)	return;

SEND_PKT:
	SendToken.Clear();
	t_ManageHost->SetPktHost(&dh, SendToken);
	SendData_Mgr(G_TYPE_HOST, G_CODE_COMMON_EDIT, SendToken);
	SendToken.Clear();

	return;
}
//---------------------------------------------------------------------------

void		CLogicMgrHost::SendPkt_InIt()
{
	DB_HOST dh;
	{
		CHAR szBuf[CHAR_MAX_SIZE] = {0, };

		dh.strName		= t_EnvInfoOp->GetComputerName();
		{
			ZeroMemoryExt(szBuf);

//			t_ASINETDLLUtil->GetNetworkGroupName(szBuf, CHAR_MAX_SIZE);
			dh.strWorkGroup = szBuf;
		}
		dh.strPriIP = t_EnvInfoOp->m_strPriIPAddr;
		dh.strMac = t_EnvInfoOp->m_strPriMacAddr;
		dh.strUserUnicode = t_EnvInfoOp->GetUserUniCode();		
	}

	PDB_HOST pdh = t_ManageHost->FirstItem();
	if(!pdh)
	{
		WriteLogE("[%s] not find host first item..", m_strLogicName.c_str());
		goto SEND_PKT;
	}

SEND_PKT:
	SendToken.Clear();
	t_ManageHost->SetPktHost(&dh, SendToken);
	SendData_Mgr(G_TYPE_HOST, G_CODE_COMMON_EDIT, SendToken);
	SendToken.Clear();

	return;
}
//---------------------------------------------------------------------------

void		CLogicMgrHost::SetUninstallHost()
{
	String strSrcPath;
	String strDstPath;
	char szCmd[MAX_QBUFF] = {0,};
	strSrcPath = SPrintf("%s/inst/%s", t_EnvInfo->m_strRootPath.c_str(), STR_SH_NAME_NANNY_UNINSTALL);
	strDstPath = SPrintf("/tmp/%s", STR_SH_NAME_NANNY_UNINSTALL);
	if(CopyFile(strSrcPath.c_str(), strDstPath.c_str(), FALSE) == FALSE)
	{
		WriteLogE("[%s] fail to copy from %s to %s (%d)", m_strLogicName.c_str(), strSrcPath.c_str(), strDstPath.c_str(), errno);
		return;
	}

	if(chmod(strDstPath.c_str(), 0755) == -1)
	{
		WriteLogE("[%s] fail to chmod %s (%d)\n", m_strLogicName.c_str(), strDstPath.c_str(), errno);
		return;
	}

	snprintf(szCmd, MAX_QBUFF-1, "%s /auto_remove", strDstPath.c_str());

	if(system(szCmd) == -1)
	{
		WriteLogE("[%s] fail to start %s (%d)\n", m_strLogicName.c_str(), szCmd, errno);
	}
}
