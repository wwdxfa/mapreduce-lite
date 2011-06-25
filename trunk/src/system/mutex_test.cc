/*
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301, USA.
*/
// Copyright 2010 Tencent Inc.
// Author: Yi Wang (yiwang@tencent.com)
//
// This is a copy from
//   http://tc-svn.tencent.com/setech/setech_infrastructure_rep/Infra_proj/
//   trunk/src/common/system/concurrency/mutex_test.cpp
//
#include "gtest/gtest.h"
#include "paralgo/system/mutex.h"

TEST(Mutex, Lock) {
  Mutex mutex;
  ASSERT_FALSE(mutex.IsLocked());
  mutex.Lock();
  ASSERT_TRUE(mutex.IsLocked());
  mutex.Unlock();
  ASSERT_FALSE(mutex.IsLocked());
}

TEST(Mutex, Locker) {
  Mutex mutex;
  {
    ASSERT_FALSE(mutex.IsLocked());
    MutexLocker locker(&mutex);
    ASSERT_TRUE(mutex.IsLocked());
  }
  ASSERT_FALSE(mutex.IsLocked());
}

TEST(Mutex, LockerWithException) {
  Mutex mutex;
  try {
    ASSERT_FALSE(mutex.IsLocked());
    MutexLocker locker(&mutex);
    ASSERT_TRUE(mutex.IsLocked()) << "after locked constructed";
    throw 0;
  } catch(...) {
    // ignore
  }
  ASSERT_FALSE(mutex.IsLocked()) << "after exception thrown";
}
