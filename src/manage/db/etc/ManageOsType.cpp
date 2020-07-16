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
#include "ManageOsType.h"

//---------------------------------------------------------------------------

CManageOsType*	t_ManageOsType = NULL;

//---------------------------------------------------------------------------

CManageOsType::CManageOsType()
{
	t_DBMgrOsType	= new CDBMgrOsType();
}
//---------------------------------------------------------------------------

CManageOsType::~CManageOsType()
{
	if(t_DBMgrOsType)		{	delete t_DBMgrOsType;		t_DBMgrOsType = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManageOsType::LoadDBMS()
{
	TListDBOsType tDBOsTypeList;
    TListDBOsTypeItor begin, end;
	if(SetER(t_DBMgrOsType->LoadExecute(&tDBOsTypeList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBOsTypeList.begin();	end = tDBOsTypeList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32				CManageOsType::IsServerType(UINT32 nID)
{
	PDB_OS_TYPE pdot = FindItem(nID);
    if(!pdot)	return 0;
    return pdot->nType;
}
//---------------------------------------------------------------------------   

String				CManageOsType::GetOsName(UINT32 nID)
{
	PDB_OS_TYPE pdot = FindItem(nID);
	if(!pdot)	return 0;

	return pdot->strName;
}
//---------------------------------------------------------------------------

String				CManageOsType::GetOsNameSP(UINT32 nID, UINT32 nSP)
{
	String strName;
	if(nSP)		strName = SPrintf("%s[%d]", GetOsName(nID).c_str(), nSP);
	else		strName = GetOsName(nID);
	return strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32				CManageOsType::SetPkt(MemToken& SendToken)
{
	SendToken.TokenAdd_32(m_tMap.size());

	TMapDBOsTypeItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32				CManageOsType::SetPkt(PDB_OS_TYPE pdot, MemToken& SendToken)
{
	SendToken.TokenAdd_32(pdot->nID);
    SendToken.TokenAdd_String(pdot->strName);
	SendToken.TokenAdd_32(pdot->nType);

	SendToken.TokenSet_Block();
    
    return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
