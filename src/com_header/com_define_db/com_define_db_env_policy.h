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


#ifndef COM_DEFINE_DB_ENV_POLICY_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_DB_ENV_POLICY_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//-------------------------------------------------------------------
//env policy type
#define SS_ENV_POLICY_TYPE_OBJECT					0 // ��ü ��� ( �׷�, ȣ��Ʈ )
#define SS_ENV_POLICY_TYPE_SUBJECT					1 // ��ü ��� ( �ڿ��� �׷�, �ڿ���) 

//-------------------------------------------------------------------
//env policy target type
#define SS_ENV_POLICY_TARGET_TYPE_USER				0x00000001 // �����
#define SS_ENV_POLICY_TARGET_TYPE_USER_GROUP		0x00000002 // ����� �׷�
#define SS_ENV_POLICY_TARGET_TYPE_HOST				0x00000004 // PC
#define SS_ENV_POLICY_TARGET_TYPE_GROUP				0x00000008 // ���� �׷�
#define SS_ENV_POLICY_TARGET_TYPE_ALL				(SS_ENV_POLICY_TARGET_TYPE_HOST | SS_ENV_POLICY_TARGET_TYPE_GROUP | \
														SS_ENV_POLICY_TARGET_TYPE_USER | SS_ENV_POLICY_TARGET_TYPE_USER_GROUP)

//-------------------------------------------------------------------

//env policy option
#define SS_ENV_POLICY_OPTION_FLAG_OBJECT_SUPPORT_PERSON				0x00000001 // 
#define SS_ENV_POLICY_OPTION_FLAG_SUBJECT_REGISTER_BY_USER			0x00010000 //  

//-------------------------------------------------------------------


#endif	//COM_DEFINE_DB_ENV_POLICY_H_938EF200_F60B_452A_BD30_A10E8507EDCC