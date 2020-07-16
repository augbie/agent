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


#ifndef COM_DEFINE_DB_PO_POWER_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_DB_PO_POWER_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//-------------------------------------------------------------------
// [HDR - nExtOption]
#define SS_PO_POWER_OPTION_MODE_SUPPORT_USER_WAIT			0x00000001 //����� ��� ���
#define	SS_PO_POWER_OPTION_MODE_SUPPORT_NOTIFY_MSG			0x00000002 //����� �˸� ���

/*
// nScPeriodType
#define SCHEDULE_PERIOD_TYPE_AUTO		0
#define SCHEDULE_PERIOD_TYPE_ONCE		1
#define SCHEDULE_PERIOD_TYPE_HOUR		2
#define SCHEDULE_PERIOD_TYPE_DAY		3	//����
#define SCHEDULE_PERIOD_TYPE_WEEK		4	//����
#define SCHEDULE_PERIOD_TYPE_MONTH		5	//�Ŵ�
*/

// nCtlMode
#define SS_PO_POWER_CONTROL_MODE_SYSTEM_TURN_ON				0x00000001 //�ý��� �ѱ�
#define	SS_PO_POWER_CONTROL_MODE_SYSTEM_TURN_OFF			0x00000002 //�ý��� ����
#define	SS_PO_POWER_CONTROL_MODE_SYSTEM_RESTART				0x00000003 //�ý��� �����

#define	SS_PO_POWER_CONTROL_MODE_MONITOR_TURN_ON			0x00000010 //����� �ѱ�
#define	SS_PO_POWER_CONTROL_MODE_MONITOR_TURN_OFF			0x00000011 //����� ����[nCtlWaitTime]

//--------------------------------------------------------------------
#endif	//COM_DEFINE_DB_PO_CTL_PANEL_H_938EF200_F60B_452A_BD30_A10E8507EDCC