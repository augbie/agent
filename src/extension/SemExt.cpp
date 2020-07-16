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


#include "stdafx.h"
#include "com_struct.h"
#include "SemExt.h"

CSemExt::CSemExt()
{
	bInit = FALSE;
}


CSemExt::~CSemExt()
{
	CloseHandle();
}

BOOL CSemExt::CreateEvent()
{
	if(bInit == TRUE)
	{
		return TRUE;
	}

	if( sem_init(&m_mutex, 0, 0) != 0)
	{
		bInit = FALSE;
		return FALSE;
	}
	bInit = TRUE;
	return TRUE;
}

BOOL CSemExt::PostEvent(int *pnCount)
{
	int nCurCount = 0;
	if(bInit == FALSE)
		return FALSE;

	if(pnCount != NULL)
	{
		if(sem_getvalue(&m_mutex, &nCurCount))
			return FALSE;
		*pnCount = nCurCount;
	}
	if(sem_post(&m_mutex) != 0)
		return FALSE;
	return TRUE;
}

DWORD CSemExt::WaitForSingleObject(DWORD dwMilliseconds)
{
	struct timespec ts;
	if(bInit == FALSE)
		return WAIT_FAILED;

	if(clock_gettime(CLOCK_REALTIME, &ts) != 0)
	{
		return WAIT_FAILED;
	}
	ts.tv_sec += (dwMilliseconds / 1000);
	ts.tv_nsec += (dwMilliseconds % 1000) * 1000000;

	if( ts.tv_nsec > 1000000000 )
	{
		ts.tv_sec++;
		ts.tv_nsec -= 1000000000;
	}
	if(sem_timedwait(&m_mutex, &ts) == 0)
	{
		return WAIT_OBJECT_0;
	}
	if(ETIMEDOUT == errno)
		return WAIT_TIMEOUT;
	return WAIT_FAILED;
}

VOID CSemExt::CloseHandle()
{
	if(bInit == TRUE)
	{
		sem_destroy(&m_mutex);
		bInit = FALSE;
	}
}

