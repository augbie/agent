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

#ifndef DB_USER_POLICY_H_4D39CDDB_E289_4d56_9F98_FE42776F4467
#define DB_USER_POLICY_H_4D39CDDB_E289_4d56_9F98_FE42776F4467

typedef struct _db_user_policy
{
	_db_user_policy()
    {
    	nID					= 0;
		nUsedFlag			= USED_FLAG_TYPE_USED;
		nRegDate			= 0;
		nUserID			= 0;
    }

    UINT32		nID;
	UINT32		nUsedFlag;
	UINT32		nRegDate;
	UINT32		nUserID ;

	DB_POLICY	tDP;

}DB_USER_POLICY, *PDB_USER_POLICY;

typedef list<DB_USER_POLICY>			TListDBUserPolicy;
typedef TListDBUserPolicy::iterator		TListDBUserPolicyItor;

typedef map<UINT32, DB_USER_POLICY>		TMapDBUserPolicy;
typedef TMapDBUserPolicy::iterator		TMapDBUserPolicyItor;

#endif //DB_USER_POLICY_H_4D39CDDB_E289_4d56_9F98_FE42776F4467



