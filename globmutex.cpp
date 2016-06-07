/*
 * globmutex.cpp: Linux & Windows mutex class
 *
 * (C) Copyright 2010 mpperez
 * Author: mperez
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 * of the License.
 */
#include "globmutex.h"

globmutex::globmutex()
{
  initmutex();
}

globmutex::~globmutex()
{

}

int globmutex::initmutex()
{
  #if defined(__linux__)
  return pthread_mutex_init (&m_mutex, NULL);;
  #elif defined(WINDOWS)
  *m_mutex = CreateMutex(0, FALSE, 0);;
  return (*m_mutex==0);
  #endif
  return -1;
}

int globmutex::lock()
{
  #if defined(__linux__)
  return pthread_mutex_lock( &m_mutex );
  #elif defined(WINDOWS)
  return (WaitForSingleObject(*m_mutex, INFINITE)==WAIT_FAILED?1:0);
  #endif
  return -1;
}

int globmutex::unlock()
{
  #if defined(__linux__)
  return pthread_mutex_unlock( &m_mutex );
  #elif defined(WINDOWS)
  return (ReleaseMutex(*mmutex)==0);
  #endif
  return -1;
}
