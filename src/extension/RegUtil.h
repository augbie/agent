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

#ifndef _REG_UTIL_H__

#define _REG_UTIL_H__
            
#include "stdafx.h"

typedef struct _reg_value_info
{
    string  strKey;
    string  strValue;
}REG_VALUE_INFO, *PREG_VALUE_INFO;

typedef list<REG_VALUE_INFO>            TListRegValueInfo;
typedef TListRegValueInfo::iterator     TListRegValueInfoItor;


class CRegUtil  
{
public:
	CRegUtil();
	virtual ~CRegUtil();

public:
	INT32 RegIsExistsKey(HKEY hKey, LPCTSTR lpKey);
	INT32 SetRootPath(LPCSTR lpRootPath);
	INT32 GetEnumSubKeyName(HKEY hKey, LPCTSTR lpKey, TListStr& tSubKeyNameList, INT32 nLevel = 0);
    INT32 GetEnumSubValueName(HKEY hKey, LPCTSTR lpKey, TListRegValueInfo& tRegValueInfoList, INT32 nLevel = 0);
	INT32 RegDeleteKeyExt(HKEY hKey, LPCTSTR lpKey);
	INT32 RegDeleteKeySubAll(HKEY hKey, LPCTSTR lpKey);
	INT32 RegDeleteValueExt(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue);
    INT32 RegDeleteValueSubAll(HKEY hKey, LPCTSTR lpKey);
	INT32 RegNotOverWriteString( HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpData );
	INT32 RegNotOverWriteInt(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, unsigned int nData);
	INT32 RegReadInt( HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, INT32& nRtn );
	INT32 RegReadInt64( HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, INT64& nRtn );
	INT32 RegReadString( HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPSTR pcData, DWORD dwSize = CHAR_MAX_SIZE );
	INT32 RegWriteInt(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, INT32 nValue);
	INT32 RegWriteInt64( HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, INT64 nData );
	INT32 RegWriteString( HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpData );
    INT32 RegWriteExtString( HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpData );
	INT32 RegWriteBinary( HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpData, INT32 nLen );
	INT32 RegFullReadInt( HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, INT32& nRtn );
	INT32 RegFullReadString( HKEY hKey, LPCSTR lpKey, LPCSTR lpValue, LPSTR lpData, DWORD dwDataLen  = CHAR_MAX_SIZE);
private:
	CHAR m_lpRootPath[CHAR_MAX_SIZE];
};

#endif // !_REG_UTIL_H__