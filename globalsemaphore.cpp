/*
 * globalsemaphore.cpp: Linux & Windows semaphore class
 *
 * (C) Copyright 2010 mpperez
 * Author: mperez
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 * of the License.
 */
#include "globalsemaphore.h"
#include <time.h>
#include <stdio.h>

globalsemaphore::globalsemaphore()
{
#if defined(__linux__)
#elif defined(WINDOWS)
   m_semaphore= CreateSemaphore(NULL, 0, 256000, NULL);
  if( m_semaphore == (HANDLE) NULL)
      printf("semaphore not created !!!\n");
#endif
  init();
}
globalsemaphore::~globalsemaphore()
{
#if defined(__linux__)
 // sem_unlink(m_semaphore);
  sem_destroy(&m_semaphore);
#elif defined(WINDOWS)
CloseHandle(m_semaphore);
#endif
}
int globalsemaphore::init()
{
#if defined(__linux__)
  if (sem_init(&m_semaphore, 0, 1) == -1)
	{
		printf("error when globalsem initiation\n");
		return -1;
	}

#elif defined(WINDOWS)

#endif
	return 0;
}
int globalsemaphore::get(int ms)
{
#	if defined(__linux__)
	struct timespec tms;
	if (clock_gettime(CLOCK_REALTIME, &tms) == -1)
		printf("Error globalsemaphore get clock_gettime\n");
	tms.tv_sec+=ms/1000;
	tms.tv_nsec+=(long)ms%1000*1e6;
	if(tms.tv_nsec>1e9)
	{
		tms.tv_nsec=0;
		tms.tv_sec++;
	}
	 return sem_timedwait(&m_semaphore,&tms);
#	elif defined(WINDOWS)
	WaitForSingleObject(m_semaphore,ms);
#	endif
}
int globalsemaphore::unget()
{
#if defined(__linux__)
 return !sem_post(&m_semaphore);
#elif defined(WINDOWS)
  long * prev;
  ReleaseSemaphore(m_semaphore,1,&prev);
#endif
}
int globalsemaphore::tryget()
{
#if defined(__linux__)
  return !sem_trywait(&m_semaphore);
#elif defined(WINDOWS)

#endif
}

