
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

#define SS_PO_POWER_FASTBOOT_DISABLE						0x00000000 //���� ���� ���� ������
#define SS_PO_POWER_FASTBOOT_OFF							0x00000001 //���� ���� OFF
#define SS_PO_POWER_FASTBOOT_ON								0x00000002 //���� ���� ON


//--------------------------------------------------------------------
#endif	//COM_DEFINE_DB_PO_CTL_PANEL_H_938EF200_F60B_452A_BD30_A10E8507EDCC