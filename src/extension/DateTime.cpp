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
#include "DateTime.h"


CTime::CTime(void)
{
	m_dt = time(NULL);
}


CTime::CTime(time_t tTime)
{
	m_dt = tTime;
}


CTime::~CTime(void)
{
}


int CTime::GetYear(void)
{
	struct tm tm_time;
	localtime_r(&m_dt, &tm_time);

	return tm_time.tm_year + 1900;
}


int CTime::GetMonth(void)
{
	struct tm tm_time;
	localtime_r(&m_dt, &tm_time);

	return tm_time.tm_mon+1;
}


int CTime::GetDay(void)
{
	struct tm tm_time;
	localtime_r(&m_dt, &tm_time);

	return tm_time.tm_mday;
}


int CTime::GetHour(void)
{
	struct tm tm_time;
	localtime_r(&m_dt, &tm_time);

	return tm_time.tm_hour;
}


int CTime::GetMinute(void)
{
	struct tm tm_time;
	localtime_r(&m_dt, &tm_time);

	return tm_time.tm_min;
}


int CTime::GetSecond(void)
{
	struct tm tm_time;
	localtime_r(&m_dt, &tm_time);

	return tm_time.tm_sec;
}


int CTime::GetDayOfWeek(void)
{
	struct tm tm_time;
	localtime_r(&m_dt, &tm_time);

	return tm_time.tm_wday;
}


int CTime::GetDayOfYear(void)
{
	struct tm tm_time;
	localtime_r(&m_dt, &tm_time);

	return tm_time.tm_yday;
}


