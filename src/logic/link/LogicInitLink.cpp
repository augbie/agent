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
#include "LogicInitLink.h"

//---------------------------------------------------------------------------

CLogicInitLink*		t_LogicInitLink = NULL;

//---------------------------------------------------------------------------

CLogicInitLink::CLogicInitLink()
{
	m_strLogicName = "logic init link";
}
//---------------------------------------------------------------------------

CLogicInitLink::~CLogicInitLink()
{
}
//---------------------------------------------------------------------------

void		CLogicInitLink::AnalyzePkt_Init(PPKT_DATA m_tPktData)
{
	InitBaseMember(m_tPktData);
	switch(m_nPktCode)
    {
        case G_CODE_INIT_REQUEST:			AnalyzePkt_Init_Request();		break;
        case G_CODE_INIT_LAST:				AnalyzePkt_Init_Last();			break;
    	default:
        {
        	WriteLogE("[logic init] not define pkt code from link : [%X][%X]", m_nPktType, m_nPktCode);
            return;
        }
    }
	InitBaseMember();
    return;
}
//---------------------------------------------------------------------------

void		CLogicInitLink::AnalyzePkt_Init_Request()
{
    UINT64 	nRequestInfo;
        
    if(!RecvToken.TokenDel_64(nRequestInfo))			{	m_nDbgPos++;		goto INVALID_PKT;	}	
	
	{
		if((nRequestInfo & G_INIT_REQUEST_TYPE_COMM) != 0)					{		SendPkt_Init_Common();			}
		if((nRequestInfo & G_INIT_REQUEST_TYPE_ADMIN) != 0)					{		SendPkt_Init_Admin();			}
    	if((nRequestInfo & G_INIT_REQUEST_TYPE_HOST) != 0)					{		SendPkt_Init_Host();			}
		if((nRequestInfo & G_INIT_REQUEST_TYPE_GROUP) != 0)					{		SendPkt_Init_Group();			}  
		if((nRequestInfo & G_INIT_REQUEST_TYPE_USER) != 0)					{		SendPkt_Init_User();			}
		if((nRequestInfo & G_INIT_REQUEST_TYPE_ENV) != 0)					{		SendPkt_Init_Env();				}       
		if((nRequestInfo & G_INIT_REQUEST_TYPE_LOCAL_ENV) != 0)				{		SendPkt_Init_LocalEnv();		}       
		if((nRequestInfo & G_INIT_REQUEST_TYPE_POLICY) != 0)				{		SendPkt_Init_Policy();			}       
	}	

    SendPkt_Init_Data();
	
	m_tPktData->hdr.code = G_CODE_INIT_REQUEST;
    SendToken.TokenAdd_32(ERR_SUCCESS);

    goto SEND_PKT;

INVALID_PKT:
    WriteLogE("[logic init] recv invalid pkt from link : [%x][%x]:[%d]", m_nPktType, m_nPktCode, m_nDbgPos);
    SendToken.TokenAdd_32(ERR_SOCKET_CLT_TO_SVR_INVALID_PKT);
    goto SEND_PKT;

SEND_PKT:
	SendData_Link(m_tPktData, SendToken);
    return;
}
//---------------------------------------------------------------------------

void		CLogicInitLink::AnalyzePkt_Init_Last()
{
	WriteLogN("init link last.");
	return;

// INVALID_PKT:
// 	WriteLogE("[logic init] recv invalid pkt from link : [%x][%x]:[%d]", m_nPktType, m_nPktCode, m_nDbgPos);
// 	return;
}
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Data()
{
	{	
		t_ManageLogEvent->SetPkt(SendToken);
		SendData_Link(m_nSessionID, G_TYPE_INIT, G_CODE_INIT_LOG_EVENT, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [log_event]");
	}
	
	{	
		t_ManageLogDoc->SetPkt_Link(SendToken);
		SendData_Link(m_nSessionID, G_TYPE_INIT, G_CODE_INIT_LOG_DOC, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [log_doc]");
	}

	{	
		t_ManageLogSecu->SetPkt_Link(SendToken);
		SendData_Link(m_nSessionID, G_TYPE_INIT, G_CODE_INIT_LOG_SECU, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [log_secu]");
	}

	{	
		t_ManageLogDeployFile->SetPkt_Link(SendToken);
		SendData_Link(m_nSessionID, G_TYPE_INIT, G_CODE_INIT_LOG_DEPLOY_FILE, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [log_deploy_file]");
	}

	{
		t_ManageLogDocDScan->SetPkt_Link(SendToken);
		SendData_Link(m_nSessionID, G_TYPE_INIT, G_CODE_INIT_LOG_DOC_DSCAN, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [log_doc_dscan]");
	}

	return;
}
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Common()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_ERR_CODE;
		t_ManageErrorCode->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [error_code][%d]", t_ManageErrorCode->Count());
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_SITE_FILE;
		t_ManageSiteFile->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [site_file][%d]", t_ManageSiteFile->Count());
	}


	{
		m_tPktData->hdr.code = G_CODE_INIT_SITE_VULN;
		t_ManageSiteVuln->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [site_vuln][%d]", t_ManageSiteVuln->Count());
	}
	{
		m_tPktData->hdr.code = G_CODE_INIT_SITE_VULN_SCAN;
		t_ManageSiteVulnScan->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [site_vuln_scan][%d]", t_ManageSiteVulnScan->Count());
	}
	{
		m_tPktData->hdr.code = G_CODE_INIT_SITE_VULN_REPAIR;
		t_ManageSiteVulnRepair->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [site_vuln_repair][%d]", t_ManageSiteVulnRepair->Count());
	}
	{
		m_tPktData->hdr.code = G_CODE_INIT_SITE_VULN_LOCK;
		t_ManageSiteVulnLock->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [site_vuln_lock][%d]", t_ManageSiteVulnLock->Count());
	}
	return;
}
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Host()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_HOST;
        t_ManageHost->SetPktHost(SendToken);
        SendData_Link(m_tPktData, SendToken);
        SendToken.Clear();
        WriteLogN("[logic init] send init link data [host][%d]", t_ManageHost->Count());
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_HOST_POLICY;
		t_ManageHostPolicy->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();                         
		WriteLogN("[logic init] send init link data [host_policy][%d]", t_ManageHostPolicy->Count());
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_HOST_SYS;
		t_ManageHostSys->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [host_sys][%d]", t_ManageHostSys->Count());
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_HOST_SW;
		t_ManageHostSw->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [host_sw][%d]", t_ManageHostSw->Count());
	}
	
    return;
}
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Group()
{	
	return;
}
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_User()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_USER;
		t_ManageUser->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [user][%d]", t_ManageUser->Count());
	}
	return;
}
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Admin()
{
	return;
}
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Env()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_ENV_LICENSE;
		t_ManageEnvLicense->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [env_license][%d]", t_ManageEnvLicense->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_ENV_POLICY;
		t_ManageEnvPolicy->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [env_policy][%d]", t_ManageEnvPolicy->Count());	
	}
		
	{
		m_tPktData->hdr.code = G_CODE_INIT_ENV_NOTIFY_INFO;
		t_ManageEnvNotifyInfo->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [env_notify_info][%d]", t_ManageEnvNotifyInfo->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_ENV_LOG;
		t_ManageEnvLog->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [env_log_event][%d]", t_ManageEnvLog->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_ENV_LOG_UNIT;
		t_ManageEnvLogUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [env_log_event_unit][%d]", t_ManageEnvLogUnit->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_ENV_SELF_PROTECT_AGT;
		t_ManageEnvSelfProtectAgt->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [env_self_protect_agt][%d]", t_ManageEnvSelfProtectAgt->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_ENV_TRUST_SUBJECT;
		t_ManageEnvTrustSubject->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [env_trust_subject][%d]", t_ManageEnvTrustSubject->Count());	
	}

	return;
}
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_LocalEnv()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_LOCAL_ENV_AUTH;
		t_ManageLocalEnvAuth->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [local_env_auth][%d]", t_ManageLocalEnvAuth->Count());	
	}
	return;
}
//---------------------------------------------------------------------------


