/*
 * globalsemaphore.h: Linux & Windows semaphore class
 *
 * (C) Copyright 2010 mpperez
 * Author: mperez
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 * of the License.
 * /
//
 /*\file
  \brief Linux & Windows semaphore class.
	\date 05-2010
*/
#ifndef GLOBALSEMAPHORE_H
#define GLOBALSEMAPHORE_H

#if defined(__linux__)
#include <semaphore.h>//API must be compiled with cc -pthread to link against the real-time library, librt.
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>
#elif defined(WINDOWS)
#include <stdlib.h>
#include <windows.h>
#endif
class globalsemaphore
{
public:
  globalsemaphore();
  ~globalsemaphore();
  int init();
  int get(int ms);
  int unget();
  int tryget();
#if defined(__linux__)
  sem_t m_semaphore;
#elif defined(WINDOWS)
  HANDLE  m_semaphore;
#endif
};

#endif // GLOBALSEMAPHORE_H
