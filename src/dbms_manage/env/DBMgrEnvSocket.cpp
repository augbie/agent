//---------------------------------------------------------------------------


#include "stdafx.h"
#include "com_struct.h"
#include "DBMgrEnvSocket.h"

//---------------------------------------------------------------------------

CDBMgrEnvSocket*		t_DBMgrEnvSocket = NULL;

//---------------------------------------------------------------------------

CDBMgrEnvSocket::CDBMgrEnvSocket()
{
	m_strDBTName = "env_socket";
}
//---------------------------------------------------------------------------

CDBMgrEnvSocket::~CDBMgrEnvSocket()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrEnvSocket::SetInitalize()
{
    {
    	
	}
	//WriteLogN("current file dbms : [env_socket][%d]", m_nDBSVer);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrEnvSocket::LoadDB(TListDBEnvSocket& tDBEnvSocketList)
{
    UINT32 nReadCnt = 0;
    DB_ENV_SOCKET des;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						" FROM env_socket WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

	do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = des.tDPH;

		tDPH					= GetDBField_PoHDR(nIndex);
		
        tDBEnvSocketList.push_back(des);
        if(m_nLoadMaxID < UINT32(tDPH.nID))	m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());

	m_nLoadNumber = tDBEnvSocketList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrEnvSocket::InsertEnvSocket(DB_ENV_SOCKET& des)
{
	DB_PO_HEADER& tDPH = des.tDPH;

	m_strQuery = SPrintf("INSERT INTO env_socket("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						") VALUES (%s);",
                        GetPoHDRQuery_InsertValue(tDPH).c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrEnvSocket::UpdateEnvSocket(DB_ENV_SOCKET& des)
{
	DB_PO_HEADER& tDPH = des.tDPH;

	m_strQuery = SPrintf("UPDATE env_socket SET %s"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(), 
                        tDPH.nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_UPDATE_FAIL;

    return 0;
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

INT32	CDBMgrEnvSocket::LoadExecute(PVOID lpTempletList)
{
	TListDBEnvSocket* ptDBList = (TListDBEnvSocket*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------


INT32	CDBMgrEnvSocket::InsertExecute(PVOID lpTemplet)
{
	PDB_ENV_SOCKET pd_t = (PDB_ENV_SOCKET)lpTemplet;

    return InsertEnvSocket(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrEnvSocket::UpdateExecute(PVOID lpTemplet)
{
	PDB_ENV_SOCKET pd_t = (PDB_ENV_SOCKET)lpTemplet;

    return UpdateEnvSocket(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrEnvSocket::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






