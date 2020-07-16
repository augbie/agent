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
#include "LogicMgrAuth.h"

//---------------------------------------------------------------------------

CLogicMgrAuth*		t_LogicMgrAuth = NULL;

//---------------------------------------------------------------------------

CLogicMgrAuth::CLogicMgrAuth()
{
	m_strLogicName = "logic mgr svr";
}
//---------------------------------------------------------------------------

CLogicMgrAuth::~CLogicMgrAuth()
{
}
//---------------------------------------------------------------------------

void		CLogicMgrAuth::AnalyzePkt_Auth(PPKT_DATA pkt_data)
{
	InitBaseMember(pkt_data);
	switch(m_nPktCode)
    {
		case AM_CODE_AUTH_LOGIN:		AnalyzePkt_Auth_Login();		break;
		case AM_CODE_AUTH_LAST:			AnalyzePkt_Auth_Last();			break;
		default:
        {
        	WriteLogE("[%s] not define pkt code : [%d][%d]", m_strLogicName.c_str(), m_nPktType, m_nPktCode);
			break;
        }
    }
	InitBaseMember();
    return;
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

void		CLogicMgrAuth::AnalyzePkt_Auth_Login()
{
	UINT32 nEnableTimerID = 0;
	UINT32 nLogoffOption = 0;
	BOOL bValidPkt = TRUE;
	
	if(!RecvToken.TokenDel_32(m_nRecvValue))
	{
		bValidPkt = FALSE; 
	}
	else
	{
		switch(m_nRecvValue)
		{
			case HOST_AUTH_RESULT_NO_ERROR:
			{
				if(!RecvToken.TokenDel_32(nLogoffOption))
				{
					bValidPkt = FALSE;
				}
				else
				{
					if((nLogoffOption | SS_HOST_OPTION_TYPE_LOGOFF_NOT_USED) != 0)
					{
						t_LogicMgrUser->SetUserLogout(nLogoffOption);
						t_LogicUser->SendPkt_Logout(nLogoffOption);
					}
					WriteLogN("[%s] login success", m_strLogicName.c_str());
					SendMgrInitData();
					t_EnvInfoOp->m_nMgrSvrAuthStatus = CLIENT_CON_STATUS_CONNECTED;
					bValidPkt = TRUE;
				}
				break;
			}
			case HOST_AUTH_RESULT_FAIL_RETRY_REGISTER:
			{
				WriteLogN("[%s] login fail : retry register on svr", m_strLogicName.c_str());
				nEnableTimerID = TIMER_ID_LOGIN_SVR_AUTH;
				t_EnvInfo->SetReg_HostRegTime(0);
				bValidPkt = TRUE;
				break;
			}
			case HOST_AUTH_RESULT_INVALID_PKT:
			{
				WriteLogN("[%s] login fail : retry connect on svr.. becault invalid pkt", m_strLogicName.c_str());
				nEnableTimerID = TIMER_ID_LOGIN_SVR_AUTH;
				bValidPkt = TRUE;
				break;
			}
			default:
			{
				WriteLogE("[%s] fail login on mgr svr : [%d]", m_strLogicName.c_str(), m_nRecvValue);
				bValidPkt = TRUE;
				break;
			}
		}	
	}

	if(bValidPkt == TRUE)
	{
		t_ThreadTimer->t_TimerUtil.DisableTimer(TIMER_ID_MANAGER_SVR_AUTH_LAST);
		t_ThreadTimer->t_TimerUtil.EnableTimer(nEnableTimerID);
	}
	else
	{
		WriteLogE("[%s] recv invalid pkt : [%d][%d]:[%d]", m_strLogicName.c_str(), m_nPktType, m_nPktCode, m_nDbgPos);
		m_tPktData->sock_evt.nErrorCode = ERR_SOCKET_SVR_TO_CLT_INVALID_PKT;
		t_ThreadTimer->t_TimerUtil.DisableTimer(TIMER_ID_MANAGER_SVR_AUTH_LAST);
		t_ThreadTimer->t_TimerUtil.EnableTimer(TIMER_ID_LOGIN_SVR_AUTH);
	}
}
//--------------------------------------------------------------------------- 

void		CLogicMgrAuth::AnalyzePkt_Auth_Last()
{
	UINT32 nEnableTimerID = 0;
	BOOL bValidPkt = TRUE;

	if(!RecvToken.TokenDel_32(m_nRecvValue))
	{
		bValidPkt = FALSE;
	}
	else
	{
		switch(m_nRecvValue)
		{
			case HOST_AUTH_RESULT_NO_ERROR:
			{
				if(!RecvToken.TokenDel_32(m_nRecvValue))
				{
					bValidPkt = FALSE;
				}
				else
				{
					WriteLogN("[%s] login auth last success : [%u]", m_strLogicName.c_str(), m_nRecvValue);
					t_ValidTimeUtil->InitValidTime(m_nRecvValue);
					t_EnvInfoOp->m_nApplyPolicyStatus = STATUS_USED_MODE_ON;
					t_LogicApplyPolicy->CheckRunEnv();
					t_LogicApplyPolicy->ApplyPolicy();
					bValidPkt = TRUE;
				}
				break;
			}
			case HOST_AUTH_RESULT_SERVER_ERROR:
			{
				WriteLogN("[%s] login fail : retry connect on svr.. becault svr system error", m_strLogicName.c_str());
				nEnableTimerID = TIMER_ID_LOGIN_SVR_AUTH;
				bValidPkt = TRUE;
				break;
			}
			default:
			{
				WriteLogE("[%s] fail login on mgr svr : [%d]", m_strLogicName.c_str(), m_nRecvValue);
				nEnableTimerID = TIMER_ID_LOGIN_SVR_AUTH;
				bValidPkt = TRUE;
				break;
			}
		}	
	}
	if(bValidPkt == TRUE)
	{
		t_ThreadTimer->t_TimerUtil.EnableTimer(nEnableTimerID);
	}
	else
	{
		m_tPktData->sock_evt.nErrorCode = ERR_SOCKET_SVR_TO_CLT_INVALID_PKT;
		WriteLogE("[%s] recv invalid pkt : [%d][%d]:[%d]", m_strLogicName.c_str(), m_nPktType, m_nPktCode, m_nDbgPos);
		t_ThreadTimer->t_TimerUtil.EnableTimer(TIMER_ID_LOGIN_SVR_AUTH);
	}
}
//--------------------------------------------------------------------------- 
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicMgrAuth::SendAuthLogin()
{
	SendToken.Clear();

	String strCurIP = GetConnectAddr_Mgr();

	WriteLogN("[%s] mgr current net hardware info : [%s]", m_strLogicName.c_str(), strCurIP.c_str());

	SendToken.TokenAdd_String(t_EnvInfo->m_strHostKey);
	SendToken.TokenAdd_String(strCurIP);

	SendData(AM_TYPE_AUTH, AM_CODE_AUTH_LOGIN, SendToken);

	return;
}
//---------------------------------------------------------------------------

void		CLogicMgrAuth::SendMgrInitData()
{
	SendToken.Clear();

	{
		t_LogicMgrHost->SendPkt_Edit();
		t_LogicMgrHostSys->SendPkt_Edit();
		t_LogicMgrHostHw->SendPkt_HostHw();
		t_LogicMgrHostSw->SendPkt_HostSw();
		t_LogicMgrHostStatusPo->SendPkt_HostStatusPo();
		t_LogicMgrHostKey->SendPkt_Hash();
	}

	{
		{		
			SendToken.TokenAdd_String(t_ManageEnvLicense->GetHash());

			SendData(G_TYPE_ENV_LICENSE, G_CODE_COMMON_HASH, SendToken);
			SendToken.Clear();
		}

		{		
			SendToken.TokenAdd_String(t_ManageEnvLog->GetHash());

			SendData(G_TYPE_ENV_LOG, G_CODE_COMMON_HASH, SendToken);
			SendToken.Clear();
		}
		{		
			SendToken.TokenAdd_String(t_ManageEnvLogUnit->GetHash());

			SendData(G_TYPE_ENV_LOG_UNIT, G_CODE_COMMON_HASH, SendToken);
			SendToken.Clear();
		}

		{		
			SendToken.TokenAdd_String(t_ManageEnvNotifyInfo->GetHash());

			SendData(G_TYPE_ENV_NOTIFY_INFO, G_CODE_COMMON_HASH, SendToken);
			SendToken.Clear();
		}

		{		
			SendToken.TokenAdd_String(t_ManageEnvSelfProtectAgt->GetHash());

			SendData(G_TYPE_ENV_SELF_PROTECT_AGT, G_CODE_COMMON_HASH, SendToken);
			SendToken.Clear();
		}

		{		
			SendToken.TokenAdd_String(t_ManageEnvTrustSubject->GetHash());

			SendData(G_TYPE_ENV_TRUST_SUBJECT, G_CODE_COMMON_HASH, SendToken);
			SendToken.Clear();
		}

		{		
			SendToken.TokenAdd_String(t_ManageEnvSOrgLink->GetHash());

			SendData(G_TYPE_ENV_SORG_LINK, G_CODE_COMMON_HASH, SendToken);
			SendToken.Clear();
		}

		{
			{
				SendToken.TokenAdd_String(t_ManageSiteVuln->GetHash());
				SendData(G_TYPE_SITE_VULN, G_CODE_COMMON_HASH, SendToken);
				SendToken.Clear();
			}
			{
				SendToken.TokenAdd_String(t_ManageSiteVulnScan->GetHash());
				SendData(G_TYPE_SITE_VULN_SCAN, G_CODE_COMMON_HASH, SendToken);
				SendToken.Clear();
			}
			{
				SendToken.TokenAdd_String(t_ManageSiteVulnRepair->GetHash());
				SendData(G_TYPE_SITE_VULN_REPAIR, G_CODE_COMMON_HASH, SendToken);
				SendToken.Clear();
			}
			{
				SendToken.TokenAdd_String(t_ManageSiteVulnLock->GetHash());
				SendData(G_TYPE_SITE_VULN_LOCK, G_CODE_COMMON_HASH, SendToken);
				SendToken.Clear();
			}
		}
	}

	//-----------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------
	SendMgrInitData_Polcy();
	
	// send last echo pkt
	SendToken.TokenAdd_32(1);
	SendData(AM_TYPE_AUTH, AM_CODE_AUTH_LAST, SendToken);	
	return;
}
//---------------------------------------------------------------------------

void		CLogicMgrAuth::SendMgrInitData_Polcy()
{
	SendToken.Clear();
	//-----------------------------------------------------------------------------------

	{
		t_ManageUser->SetPktMgr(SendToken);
		SendData(G_TYPE_USER, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_HOST_RM_INFO pCurPolicy = (PDB_PO_HOST_RM_INFO)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_HOST_RM_INFO);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_HOST_RM_INFO, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_HOST_RUN pCurPolicy = (PDB_PO_HOST_RUN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_HOST_RUN);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_HOST_RUN, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		DB_PO_SVR_INFO_LGN tCurPolicy;
		PDB_PO_SVR_INFO_LGN pCurPolicy = (PDB_PO_SVR_INFO_LGN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_SVR_INFO_LGN);
		if(pCurPolicy)	tCurPolicy = *pCurPolicy;

		if(tCurPolicy.tDPH.nUsedMode != STATUS_USED_MODE_ON || 
			tCurPolicy.strSvrInfoList.empty())	
		{
			SendToken.TokenAdd_String(t_EnvInfo->m_strLgnSvrInfoList);
		}
		else
		{
			SendToken.TokenAdd_String(tCurPolicy.tDPH.strHash);
		}
		SendToken.TokenAdd_32(tCurPolicy.tDPH.nID);
		SendToken.TokenAdd_32(tCurPolicy.tDPH.nSeqNo);

		SendData(G_TYPE_PO_SVR_INFO_LGN, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		DB_PO_SVR_INFO_UDT tCurPolicy;
		PDB_PO_SVR_INFO_UDT pCurPolicy = (PDB_PO_SVR_INFO_UDT)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_SVR_INFO_UDT);
		if(pCurPolicy)		tCurPolicy = *pCurPolicy;

		SendToken.TokenAdd_String(tCurPolicy.tDPH.strHash);
		SendToken.TokenAdd_32(tCurPolicy.tDPH.nID);
		SendToken.TokenAdd_32(tCurPolicy.tDPH.nSeqNo);

		SendData(G_TYPE_PO_SVR_INFO_UDT, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------

	{
		PDB_PO_CTL_PROC pCurPolicy = (PDB_PO_CTL_PROC)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_CTL_PROC);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_CTL_PROC, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_SELF_PROTECT pCurPolicy = (PDB_PO_SELF_PROTECT)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_SELF_PROTECT);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_SELF_PROTECT, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------

	{
		PDB_PO_POWER pCurPolicy = (PDB_PO_POWER)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_POWER);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_POWER, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_WIN_RUN pCurPolicy = (PDB_PO_WIN_RUN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_WIN_RUN);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_WIN_RUN, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_DEPLOY_FILE pCurPolicy = (PDB_PO_DEPLOY_FILE)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_DEPLOY_FILE);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_DEPLOY_FILE, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_CTL_PANEL pCurPolicy = (PDB_PO_CTL_PANEL)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_CTL_PANEL);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_CTL_PANEL, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------

	{
		PDB_PO_FA_OP pCurPolicy = (PDB_PO_FA_OP)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FA_OP);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_FA_OP, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_FA_CLEAR pCurPolicy = (PDB_PO_FA_CLEAR)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FA_CLEAR);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_FA_CLEAR, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_FA_ENV pCurPolicy = (PDB_PO_FA_ENV)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FA_ENV);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_FA_ENV, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_FA_PROC pCurPolicy = (PDB_PO_FA_PROC)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FA_PROC);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_FA_PROC, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_FA_BK pCurPolicy = (PDB_PO_FA_BK)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FA_BK);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_FA_BK, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_FA_NOTIFY pCurPolicy = (PDB_PO_FA_NOTIFY)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FA_NOTIFY);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_FA_NOTIFY, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------

	{
		PDB_PO_FE_PTN_OP pCurPolicy = (PDB_PO_FE_PTN_OP)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FE_PTN_OP);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_FE_PTN_OP, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}
	
	{
		PDB_PO_FE_PTN_LO pCurPolicy = (PDB_PO_FE_PTN_LO)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FE_PTN_LO);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_FE_PTN_LO, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_FE_PTN_BL pCurPolicy = (PDB_PO_FE_PTN_BL)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FE_PTN_BL);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_FE_PTN_BL, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_FE_PTN_WL pCurPolicy = (PDB_PO_FE_PTN_WL)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FE_PTN_WL);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_FE_PTN_WL, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_FE_EXCLUDE pCurPolicy = (PDB_PO_FE_EXCLUDE)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FE_EXCLUDE);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_FE_EXCLUDE, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_FE_NOTIFY pCurPolicy = (PDB_PO_FE_NOTIFY)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FE_NOTIFY);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_FE_NOTIFY, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_FE_SINGLE_PTN pCurPolicy = (PDB_PO_FE_SINGLE_PTN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FE_SINGLE_PTN);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_FE_SINGLE_PTN, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	{
		PDB_PO_IN_PTN_OP pCurPolicy = (PDB_PO_IN_PTN_OP)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_PTN_OP);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_IN_PTN_OP, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_IN_PTN_BL pCurPolicy = (PDB_PO_IN_PTN_BL)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_PTN_BL);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_IN_PTN_BL, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_IN_PTN_WL pCurPolicy = (PDB_PO_IN_PTN_WL)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_PTN_WL);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_IN_PTN_WL, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_IN_PTN_EX pCurPolicy = (PDB_PO_IN_PTN_EX)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_PTN_EX);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_IN_PTN_EX, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_IN_PTN_SP pCurPolicy = (PDB_PO_IN_PTN_SP)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_PTN_SP);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_IN_PTN_SP, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		String strHash = t_ManagePoInPtnSPRule->GetHash();		
		SendToken.TokenAdd_String(strHash);

		SendData(G_TYPE_PO_IN_PTN_SP_RULE, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_IN_PTN_NO pCurPolicy = (PDB_PO_IN_PTN_NO)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_PTN_NO);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_IN_PTN_NO, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	{
		PDB_PO_IN_AC_DOC pCurPolicy = (PDB_PO_IN_AC_DOC)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_AC_DOC);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_IN_AC_DOC, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_IN_AC_SF pCurPolicy = (PDB_PO_IN_AC_SF)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_AC_SF);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_IN_AC_SF, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	{
		PDB_PO_IN_AC_FILE pCurPolicy = (PDB_PO_IN_AC_FILE)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_AC_FILE);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_IN_AC_FILE, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------

	{
		PDB_PO_IN_VULN_OP pCurPolicy = (PDB_PO_IN_VULN_OP)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_VULN_OP);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_IN_VULN_OP, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}
	{
		PDB_PO_IN_VULN_SCAN pCurPolicy = (PDB_PO_IN_VULN_SCAN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_VULN_SCAN);
		if(pCurPolicy)	SendToken.TokenAdd_String(pCurPolicy->tDPH.strHash);
		else			SendToken.TokenAdd_String("empty");

		SendData(G_TYPE_PO_IN_VULN_SCAN, G_CODE_COMMON_HASH, SendToken);
		SendToken.Clear();
	}

	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	
	{
		if(!t_ManageLogSecu->SetPkt(SendToken))			SendData(G_TYPE_LOG_SECU, G_CODE_COMMON_SYNC, SendToken);
		SendToken.Clear();
	}

	{
		if(!t_ManageLogDoc->SetPkt(SendToken))			SendData(G_TYPE_LOG_DOC, G_CODE_COMMON_SYNC, SendToken);
		SendToken.Clear();
	}

	{
		if(!t_ManageLogDeployFile->SetPkt(SendToken))	SendData(G_TYPE_LOG_DEPLOY_FILE, G_CODE_COMMON_SYNC, SendToken);
		SendToken.Clear();
	}

	{
		t_LogicMgrSiteFile->SendPkt_Sync();
		SendToken.Clear();
	}
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
