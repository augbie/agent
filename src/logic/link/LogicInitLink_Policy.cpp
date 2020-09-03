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

void		CLogicInitLink::SendPkt_Init_Policy()
{
	SendPkt_Init_Policy_SA();
	SendPkt_Init_Policy_AC();
	SendPkt_Init_Policy_FA();
	SendPkt_Init_Policy_FE();
	SendPkt_Init_Policy_IN();
	SendPkt_Init_Policy_IN_VULN();
	SendPkt_Init_Policy_IN_RS();
	SendPkt_Init_Policy_PM();
	SendPkt_Init_Policy_IN_DEVO();

	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_SA()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_SVR_INFO_LGN;
		t_ManagePoSvrInfoLgn->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_svr_info_lgn][%d]", t_ManagePoSvrInfoLgn->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_SVR_INFO_UDT;
		t_ManagePoSvrInfoUdt->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_svr_info_udt][%d]", t_ManagePoSvrInfoUdt->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_HOST_RM_INFO;
		t_ManagePoHostRmInfo->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_host_rm_info][%d]", t_ManagePoHostRmInfo->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_HOST_RUN;
		t_ManagePoHostRun->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_host_run][%d]", t_ManagePoHostRun->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_SCH;
		t_ManagePoSch->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_sch][%d]", t_ManagePoSch->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_SCH_PKG;
		t_ManagePoSchPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_sch_pkg][%d]", t_ManagePoSchPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_SCH_UNIT;
		t_ManagePoSchUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_sch_unit][%d]", t_ManagePoSchUnit->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_POWER;
		t_ManagePoPower->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_power][%d]", t_ManagePoPower->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_POWER_PKG;
		t_ManagePoPowerPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_power_pkg][%d]", t_ManagePoPowerPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_POWER_UNIT;
		t_ManagePoPowerUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_power_unit][%d]", t_ManagePoPowerUnit->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_WIN_RUN;
		t_ManagePoWinRun->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_win_run][%d]", t_ManagePoWinRun->Count());
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_CTL_PANEL;
		t_ManagePoCtlPanel->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_ctl_panel][%d]", t_ManagePoCtlPanel->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_CTL_PANEL_PKG;
		t_ManagePoCtlPanelPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_ctl_panel_pkg][%d]", t_ManagePoCtlPanelPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_CTL_PANEL_UNIT;
		t_ManagePoCtlPanelUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_ctl_panel_unit][%d]", t_ManagePoCtlPanelUnit->Count());		
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE;
		t_ManagePoDeployFile->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file][%d]", t_ManagePoDeployFile->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_PKG;
		t_ManagePoDeployFilePkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_pkg][%d]", t_ManagePoDeployFilePkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_UNIT;
		t_ManagePoDeployFileUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit][%d]", t_ManagePoDeployFileUnit->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_UNIT_INFO_PKG;
		t_ManagePoDeployFileUnitInfoPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_info_pkg][%d]", t_ManagePoDeployFileUnitInfoPkg->Count());


		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_UNIT_CHK_PKG;
		t_ManagePoDeployFileUnitChkPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_chk_pkg][%d]", t_ManagePoDeployFileUnitChkPkg->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_UNIT_TAR_PKG;
		t_ManagePoDeployFileUnitTarPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_tar_pkg][%d]", t_ManagePoDeployFileUnitTarPkg->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_UNIT_SCH_PKG;
		t_ManagePoDeployFileUnitSchPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_sch_pkg][%d]", t_ManagePoDeployFileUnitSchPkg->Count());			

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_INFO_UNIT;
		t_ManagePoDeployFileInfoUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_info_unit][%d]", t_ManagePoDeployFileInfoUnit->Count());		


		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_CHK_UNIT;
		t_ManagePoDeployFileChkUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_chk_unit][%d]", t_ManagePoDeployFileChkUnit->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_TAR_UNIT;
		t_ManagePoDeployFileTarUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_tar_unit][%d]", t_ManagePoDeployFileTarUnit->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_SCH_UNIT;
		t_ManagePoDeployFileSchUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_sch_unit][%d]", t_ManagePoDeployFileSchUnit->Count());	
	}
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_AC()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_CTL_PROC;
		t_ManagePoCtlProc->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_ctl_proc][%d]", t_ManagePoCtlProc->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_CTL_PROC_PKG;
		t_ManagePoCtlProcPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_ctl_proc_pkg][%d]", t_ManagePoCtlProcPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_CTL_PROC_UNIT;
		t_ManagePoCtlProcUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_ctl_proc_unit][%d]", t_ManagePoCtlProcUnit->Count());		
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_SELF_PROTECT;
		t_ManagePoSelfProtect->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_self_protect][%d]", t_ManagePoSelfProtect->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_SELF_PROTECT_PKG;
		t_ManagePoSelfProtectPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_self_protect_pkg][%d]", t_ManagePoSelfProtectPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_SELF_PROTECT_UNIT;
		t_ManagePoSelfProtectUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_self_protect_unit][%d]", t_ManagePoSelfProtectUnit->Count());	
	}
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_FA()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP;
		t_ManagePoFaOp->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op][%d]", t_ManagePoFaOp->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_PKG;
		t_ManagePoFaOpPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_pkg][%d]", t_ManagePoFaOpPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_UNIT;
		t_ManagePoFaOpUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_unit][%d]", t_ManagePoFaOpUnit->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_UNIT_OBJ_PKG;
		t_ManagePoFaOpUnitObjPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_unit_obj_pkg][%d]", t_ManagePoFaOpUnitObjPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_UNIT_SUB_PKG;
		t_ManagePoFaOpUnitSubPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_unit_sub_pkg][%d]", t_ManagePoFaOpUnitSubPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_UNIT_SCH_PKG;
		t_ManagePoFaOpUnitSchPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_unit_sch_pkg][%d]", t_ManagePoFaOpUnitSchPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_UNIT_RUL_PKG;
		t_ManagePoFaOpUnitRulPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_unit_rul_pkg][%d]", t_ManagePoFaOpUnitRulPkg->Count());



		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_OBJ_UNIT;
		t_ManagePoFaOpObjUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_obj_unit][%d]", t_ManagePoFaOpObjUnit->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_SUB_UNIT;
		t_ManagePoFaOpSubUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_sub_unit][%d]", t_ManagePoFaOpSubUnit->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_SCH_UNIT;
		t_ManagePoFaOpSchUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_sch_unit][%d]", t_ManagePoFaOpSchUnit->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_CLEAR;
		t_ManagePoFaClear->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_clear][%d]", t_ManagePoFaClear->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_CLEAR_PKG;
		t_ManagePoFaClearPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_clear_pkg][%d]", t_ManagePoFaClearPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_CLEAR_UNIT;
		t_ManagePoFaClearUnit->SetPkt_Link(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_clear_unit][%d]", t_ManagePoFaClearUnit->Count());		
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_PROC;
		t_ManagePoFaProc->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_proc][%d]", t_ManagePoFaProc->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_PROC_PKG;
		t_ManagePoFaProcPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_proc_pkg][%d]", t_ManagePoFaProcPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_PROC_UNIT;
		t_ManagePoFaProcUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_proc_unit][%d]", t_ManagePoFaProcUnit->Count());		
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_ENV;
		t_ManagePoFaEnv->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_env][%d]", t_ManagePoFaEnv->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_ENV_PKG;
		t_ManagePoFaEnvPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_env_pkg][%d]", t_ManagePoFaEnvPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_ENV_UNIT;
		t_ManagePoFaEnvUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_env_unit][%d]", t_ManagePoFaEnvUnit->Count());		
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_BK;
		t_ManagePoFaBk->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_bk][%d]", t_ManagePoFaBk->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_NOTIFY;
		t_ManagePoFaNotify->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_notify][%d]", t_ManagePoFaNotify->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_NOTIFY_PKG;
		t_ManagePoFaNotifyPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_notify_pkg][%d]", t_ManagePoFaNotifyPkg->Count());	
	}
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_FE()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_PTN_OP;
		t_ManagePoFePtnOp->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_ptn_op][%d]", t_ManagePoFePtnOp->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_PTN_LO;
		t_ManagePoFePtnLo->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_ptn_lo][%d]", t_ManagePoFePtnLo->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_PTN_BL;
		t_ManagePoFePtnBL->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_ptn_bl][%d]", t_ManagePoFePtnBL->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_PTN_WL;
		t_ManagePoFePtnWL->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_ptn_wl][%d]", t_ManagePoFePtnWL->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_EXCLUDE;
		t_ManagePoFeExclude->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_exclude][%d]", t_ManagePoFeExclude->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_EXCLUDE_PKG;
		t_ManagePoFeExcludePkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_exclude_pkg][%d]", t_ManagePoFeExcludePkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_EXCLUDE_UNIT;
		t_ManagePoFeExcludeUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_exclude_unit][%d]", t_ManagePoFeExcludeUnit->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_NOTIFY;
		t_ManagePoFeNotify->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_notify][%d]", t_ManagePoFeNotify->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_NOTIFY_PKG;
		t_ManagePoFeNotifyPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_notify_pkg][%d]", t_ManagePoFeNotifyPkg->Count());			
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_SINGLE_PTN;
		t_ManagePoFeSinglePtn->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_single_ptn][%d]", t_ManagePoFeSinglePtn->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_SINGLE_PTN_UNIT;
		t_ManagePoFeSinglePtnUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_notify_unit][%d]", t_ManagePoFeSinglePtnUnit->Count());			
	}
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_IN()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_OP;
		t_ManagePoInPtnOp->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_op][%d]", t_ManagePoInPtnOp->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_OP_PKG;
		t_ManagePoInPtnOpPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_op_pkg][%d]", t_ManagePoInPtnOpPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_OP_UNIT;
		t_ManagePoInPtnOpUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_op_unit][%d]", t_ManagePoInPtnOpUnit->Count());		
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////
		
		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_BL;
		t_ManagePoInPtnBL->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_bl][%d]", t_ManagePoInPtnBL->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_BL_PKG;
		t_ManagePoInPtnBLPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_bl_pkg][%d]", t_ManagePoInPtnBLPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_BL_UNIT;
		t_ManagePoInPtnBLUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_bl_unit][%d]", t_ManagePoInPtnBLUnit->Count());	
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_WL;
		t_ManagePoInPtnWL->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_wl][%d]", t_ManagePoInPtnWL->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_WL_PKG;
		t_ManagePoInPtnWLPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_wl_pkg][%d]", t_ManagePoInPtnWLPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_WL_UNIT;
		t_ManagePoInPtnWLUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_wl_unit][%d]", t_ManagePoInPtnWLUnit->Count());		
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_EX;
		t_ManagePoInPtnEx->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_ex][%d]", t_ManagePoInPtnEx->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_EX_PKG;
		t_ManagePoInPtnExPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_ex_pkg][%d]", t_ManagePoInPtnExPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_EX_UNIT;
		t_ManagePoInPtnExUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_ex_unit][%d]", t_ManagePoInPtnExUnit->Count());	
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_SP;
		t_ManagePoInPtnSP->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_sp][%d]", t_ManagePoInPtnSP->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_SP_PKG;
		t_ManagePoInPtnSPPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_sp_pkg][%d]", t_ManagePoInPtnSPPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_SP_UNIT;
		t_ManagePoInPtnSPUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_sp_unit][%d]", t_ManagePoInPtnSPUnit->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_SP_RULE;
		t_ManagePoInPtnSPRule->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_sp_rule][%d]", t_ManagePoInPtnSPRule->Count());	
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_NO;
		t_ManagePoInPtnNo->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_no][%d]", t_ManagePoInPtnNo->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_NO_PKG;
		t_ManagePoInPtnNoPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_no_pkg][%d]", t_ManagePoInPtnNoPkg->Count());	
	}	
	
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_IN_RS()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_RS_OP;
		t_ManagePoInRsOp->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_rs_op][%d]", t_ManagePoInRsOp->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_RS_OP_PKG;
		t_ManagePoInRsOpPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_rs_op_pkg][%d]", t_ManagePoInRsOpPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_RS_OP_UNIT;
		t_ManagePoInRsOpUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_rs_op_unit][%d]", t_ManagePoInRsOpUnit->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_RS_OP_UNIT_SUB_PKG;
		t_ManagePoInRsOpUnitSubPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_rs_op_unit_sub_pkg][%d]", t_ManagePoInRsOpUnitSubPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_RS_OP_UNIT_OBJ_PKG;
		t_ManagePoInRsOpUnitObjPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_rs_op_unit_obj_pkg][%d]", t_ManagePoInRsOpUnitObjPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_RS_OP_SUB_UNIT;
		t_ManagePoInRsOpSubUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_rs_op_sub_unit][%d]", t_ManagePoInRsOpSubUnit->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_RS_OP_OBJ_UNIT;
		t_ManagePoInRsOpObjUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_rs_op_obj_unit][%d]", t_ManagePoInRsOpObjUnit->Count());	
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_RS_BK;
		t_ManagePoInRsBk->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_rs_bk][%d]", t_ManagePoInRsBk->Count());	
		
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_RS_NO;
		t_ManagePoInRsNo->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_rs_no][%d]", t_ManagePoInRsNo->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_RS_NO_PKG;
		t_ManagePoInRsNoPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_rs_no_pkg][%d]", t_ManagePoInRsNoPkg->Count());	

		
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_IN_VULN()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_AX;
		t_ManagePoInVulnAx->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_ax][%d]", t_ManagePoInVulnAx->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_AX_PKG;
		t_ManagePoInVulnAxPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_ax_pkg][%d]", t_ManagePoInVulnAxPkg->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_AX_UNIT;
		t_ManagePoInVulnAxUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_ax_unit][%d]", t_ManagePoInVulnAxUnit->Count());
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_EDIT_APP;
		t_ManagePoInVulnEditApp->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_edit_app][%d]", t_ManagePoInVulnEditApp->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_EDIT_APP_PKG;
		t_ManagePoInVulnEditAppPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_edit_app_pkg][%d]", t_ManagePoInVulnEditAppPkg->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_EDIT_APP_UNIT;
		t_ManagePoInVulnEditAppUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_edit_app_unit][%d]", t_ManagePoInVulnEditAppUnit->Count());
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_OP;
		t_ManagePoInVulnOp->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_op][%d]", t_ManagePoInVulnOp->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_OP_PKG;
		t_ManagePoInVulnOpPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_op_pkg][%d]", t_ManagePoInVulnOpPkg->Count());	
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_QNA;
		t_ManagePoInVulnQna->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_qna][%d]", t_ManagePoInVulnQna->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_QNA_PKG;
		t_ManagePoInVulnQnaPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_ax_qna][%d]", t_ManagePoInVulnQnaPkg->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_QNA_UNIT;
		t_ManagePoInVulnQnaUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_qna_unit][%d]", t_ManagePoInVulnQnaUnit->Count());
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_SCAN;
		t_ManagePoInVulnScan->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_scan][%d]", t_ManagePoInVulnScan->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_SCAN_PKG;
		t_ManagePoInVulnScanPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_scan_pkg][%d]", t_ManagePoInVulnScanPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_SCAN_UNIT;
		t_ManagePoInVulnScanUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_scan_unit][%d]", t_ManagePoInVulnScanUnit->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_SCAN_UNIT_PKG;
		t_ManagePoInVulnScanUnitPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_scan_unit_pkg][%d]", t_ManagePoInVulnScanUnitPkg->Count());
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_SECU_USB;
		t_ManagePoInVulnSecuUsb->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_secu_usb][%d]", t_ManagePoInVulnSecuUsb->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_SECU_USB_PKG;
		t_ManagePoInVulnSecuUsbPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_secu_usb_pkg][%d]", t_ManagePoInVulnSecuUsbPkg->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_SECU_USB_UNIT;
		t_ManagePoInVulnSecuUsbUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_secu_usb_unit][%d]", t_ManagePoInVulnSecuUsbUnit->Count());
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_SW;
		t_ManagePoInVulnSw->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_sw][%d]", t_ManagePoInVulnSw->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_SW_PKG;
		t_ManagePoInVulnSwPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_sw_pkg][%d]", t_ManagePoInVulnSwPkg->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_SW_UNIT;
		t_ManagePoInVulnSwUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_sw_unit][%d]", t_ManagePoInVulnSwUnit->Count());
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_PATCH_EXCEPTION;
		t_ManagePoInVulnPatchException->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_patch_exception][%d]", t_ManagePoInVulnPatchException->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_PATCH_EXCEPTION_PKG;
		t_ManagePoInVulnPatchExceptionPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_patch_exception_pkg][%d]", t_ManagePoInVulnPatchExceptionPkg->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_PATCH_EXCEPTION_UNIT;
		t_ManagePoInVulnPatchExceptionUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_patch_exception_unit][%d]", t_ManagePoInVulnPatchExceptionUnit->Count());
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////
	}	


	return;
}
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_IN_DEVO()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_DV_NOTIFY;
		t_ManagePoInDevONotify->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_devo_notify][%d]", t_ManagePoInDevONotify->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_DV_NOTIFY_PKG;
		t_ManagePoInDevONotifyPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_devo_notify_pkg][%d]", t_ManagePoInDevONotifyPkg->Count());	
	}
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_PM()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_PM_OP;
		t_ManagePoPmOp->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_pm_op][%d]", t_ManagePoPmOp->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_PM_DM;
		t_ManagePoPmDm->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_pm_dm][%d]", t_ManagePoPmDm->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_PM_DM_PKG;
		t_ManagePoPmDmPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_pm_dm_pkg][%d]", t_ManagePoPmDmPkg->Count());	
		
		m_tPktData->hdr.code = G_CODE_INIT_PO_PM_DM_UNIT;
		t_ManagePoPmDmUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_pm_dm_unit][%d]", t_ManagePoPmDmUnit->Count());



		m_tPktData->hdr.code = G_CODE_INIT_PO_PM_EX;
		t_ManagePoPmEx->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_pm_ex][%d]", t_ManagePoPmEx->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_PM_EX_PKG;
		t_ManagePoPmExPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_pm_ex_pkg][%d]", t_ManagePoPmExPkg->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_PM_EX_UNIT;
		t_ManagePoPmExUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_pm_ex_unit][%d]", t_ManagePoPmExUnit->Count());



		m_tPktData->hdr.code = G_CODE_INIT_PO_PM_SCAN;
		t_ManagePoPmScan->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_pm_scan][%d]", t_ManagePoPmScan->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_PM_SCAN_PKG;
		t_ManagePoPmScanPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_pm_scan_pkg][%d]", t_ManagePoPmScanPkg->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_PM_SCAN_UNIT;
		t_ManagePoPmScanUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_pm_scan_unit][%d]", t_ManagePoPmScanUnit->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_PM_NO;
		t_ManagePoPmNo->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_pm_no][%d]", t_ManagePoPmNo->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_PM_NO_PKG;
		t_ManagePoPmNoPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_pm_no_pkg][%d]", t_ManagePoPmNoPkg->Count());

	}
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



