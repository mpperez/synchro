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

//
/*!\file
  \brief Linux & Windows mutex class.
  \date 05-2010
*/
#ifndef GLOBMUTEX_H
#define GLOBMUTEX_H

#if defined(__linux__)
#include <pthread.h>
#elif defined(WINDOWS)
#include <windows.h>
#include <process.h>
#endif

class globmutex
{
public:
  globmutex();
  ~globmutex();
  int initmutex();
  int lock();
  int unlock();
private:
#if defined(__linux__)
  pthread_mutex_t m_mutex;
#elif defined(WINDOWS)
  MUTEX HANDLE m_mutex;
#endif
};

#endif // GLOBMUTEX_H
