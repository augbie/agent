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

// SecurityUtil.h: interface for the CSecurityUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SECURITYUTIL_H__863101C1_5B8F_43F3_BA18_D4E6C7706337__INCLUDED_)
#define AFX_SECURITYUTIL_H__863101C1_5B8F_43F3_BA18_D4E6C7706337__INCLUDED_

//-----------------------------------------------------------------------------------------------
#include "StrEncrypt.h"
#include "SeedUtil.h"
#include "SHA2Util.h"
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
#define		ASI_BUFFER_ENC_TYPE_NONE				0
#define		ASI_BUFFER_ENC_TYPE_STRING				1
#define		ASI_BUFFER_ENC_TYPE_SEED				2
#define		ASI_BUFFER_ENC_TYPE_TLS1				3

class CSecurityUtil  
{
private:
	UINT32	m_nEncryptType;
	UINT32	m_nSessionKey;

private:
	CStrEncrypt		m_tStrEncrypt;
	CSHA2Util		m_tSha2Util;
	CSeedUtil		m_tSeedUtil;

private:
	BYTE	m_pDstHash[32];

public:
	void	SetMode(UINT32 nEncryptType);
	void	SetSessionKey(UINT32 nSKey);

public:
	void	Encrypt(UINT8* lpPlanText, UINT32 nPlanLen, UINT8** lpEncText, UINT32& nEncLen);
	INT32	Decrypt(UINT8* lpEncText, UINT32 nEncLen, UINT8** lpPlanText, UINT32& nPlanLen);
	UINT32	Encrypt_Len(UINT32 nPlanLen);
	
public:
	void	GetSha256(UINT8* lpSrc, DWORD dwSrcLen, UINT8* lpDst, DWORD dwDstLen);
	INT32	CompareSha256(UINT8* lpSrc, UINT32 nSrcLen, UINT8* lpChkSHA);
	void	ConvertSha256(UINT8* pHash, LPSTR lpHashBuffer, DWORD dwMaxLen);
	void	ConvertSha256Last(LPSTR lpHashBuffer, DWORD dwMaxLen);
public:
	CSecurityUtil();
	virtual ~CSecurityUtil();

};

#endif // !defined(AFX_SECURITYUTIL_H__863101C1_5B8F_43F3_BA18_D4E6C7706337__INCLUDED_)
