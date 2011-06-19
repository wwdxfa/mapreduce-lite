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
