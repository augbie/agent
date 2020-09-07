
#ifndef COM_DEFINE_DB_PO_HOST_RUN_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_DB_PO_HOST_RUN_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//-------------------------------------------------------------------
//host run option
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_SAFE_MODE				0x00000001 // ������� ���� ����
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_ASI_DEPLOY_SVR			0x00000002 // ASI ���� ������ ���� ���� ����(������Ʈ ����)
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_ASI_LICENSE_SVR			0x00000004 // ASI LICENSE ������ ���� Lgn ���� ���� �˻�
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_PTOP						0x00000008 // PtoP�� �̿��� �ٿ�ε� ����
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_BOOT_APPLY				0x00000010 // ���ý� ��å ����
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_ALLOW_MGR_CLOSE			0x00000020 // MGR ���� ��뿩��
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_ALLOW_MGR_LOGIN			0x00000040 // MGR �α��� ���̱� ����
#define	SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_ALLOW_MGR_MANUAL_DEL		0x00000080 // MGR_�������� ���̱� ����
#define	SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_RESTART_SVC				0x00000100 // ���� ����� �ֱ�
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_ALLOW_MGR_LOGIN_ID		0x00000200 // MGR �α��� ���̱� ���� (ID�θ� �α��� )

//-------------------------------------------------------------------
//host mgr show type
#define SS_PO_HOST_RUN_MGR_SHOW_TYPE_NOT_USED						0 // Agt Mgr ǥ�� ����
#define SS_PO_HOST_RUN_MGR_SHOW_TYPE_NORMAL							1 // Agt Mgr ǥ��
#define SS_PO_HOST_RUN_MGR_SHOW_TYPE_HIDE_START						2 // Agt Mgr ���μ��� ����

//-------------------------------------------------------------------
//system boot chk type
#define SS_PO_HOST_RUN_BOOT_CHK_TYPE_AUTO							0
#define SS_PO_HOST_RUN_BOOT_CHK_TYPE_START_SVC						1


//--------------------------------------------------------------------
#endif	//COM_DEFINE_DB_PO_HOST_RUN_H_938EF200_F60B_452A_BD30_A10E8507EDCC