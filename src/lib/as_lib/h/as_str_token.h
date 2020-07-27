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

#ifndef _AS_STR_TOKEN_H_
#define _AS_STR_TOKEN_H_

typedef struct str_token {
	int   alloc_size;		/* 실제 문자열을 저장할 수 있는 공간 */
	int   data_len;			/* NULL 문자를 제외한 실제 문자열 길이 */
	char  data[0];
} str_token_t;


void add_token_str(str_token_t **token, char *str, char *sep);
void add_token_int(str_token_t **token, int num, char *sep);
int count_token(char *pSrc, int ch);
char *copy_token(char *pDst, int nDstMax, char *pSrc, int ch);

int HexStringToInt(char *pHexString);
int StringToInt(char *pString);
UINT64 StringToUInt64(const char *pString);

#endif /* _AS_STR_TOKEN_H_ */


