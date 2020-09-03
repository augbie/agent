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
#include "ManageDevOInfo.h"

//---------------------------------------------------------------------------

CManageDevOInfo*	t_ManageDevOInfo = NULL;

//---------------------------------------------------------------------------

CManageDevOInfo::CManageDevOInfo()
{

}
//---------------------------------------------------------------------------

CManageDevOInfo::~CManageDevOInfo()
{
	
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32		CManageDevOInfo::AddDevOInfo(String strDvInstanceID, String strDvPaInstanceID, UINT32 nPolType, BOOL bIsDefPol)
{

	return 0;
}
//---------------------------------------------------------------------------
INT32		CManageDevOInfo::CheckDvPolicy(BOOL bDefReset)
{
	return 0;
}
//---------------------------------------------------------------------------
UINT32		CManageDevOInfo::GetDvType(String strClassName)
{
	return 0;
}
//---------------------------------------------------------------------------
UINT32		CManageDevOInfo::GetMaxID()
{
	TMapMemDevOInfoRItor begin, end;
	begin = m_tMap.rbegin();	end = m_tMap.rend();
	if(begin == end)	return 1;

	return (begin->first + 1);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
INT32		CManageDevOInfo::SetPkt(MemToken& SendToken)
{
	SendToken.TokenAdd_32(m_tMap.size());

	TMapMemDevOInfoItor begin, end;
	begin = m_tMap.begin();	end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		SetPkt(&(begin->second), SendToken);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32		CManageDevOInfo::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PMEM_DEVO_INFO pdata = FindItem(nID);
	if(!pdata)	return -1;

	return SetPkt(pdata, SendToken);
}
//---------------------------------------------------------------------------

INT32		CManageDevOInfo::SetPkt(PMEM_DEVO_INFO pdata, MemToken& SendToken)
{
	SendToken.TokenAdd_32(pdata->nID);
	SendToken.TokenAdd_32(pdata->nPolType);
	SendToken.TokenAdd_String(pdata->strProtectInfo);

	SendToken.TokenSet_Block();
	return 0;
}

//---------------------------------------------------------------------------
