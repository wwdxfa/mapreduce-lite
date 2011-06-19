// Copyright 2010 Tencent Inc.
// Author: Yi Wang (yiwang@tencent.com)
//
// This is a copy from
//   http://tc-svn.tencent.com/setech/setech_infrastructure_rep/Infra_proj/
//   trunk/src/common/system/concurrency/condition_variable_test.cpp
//
#include "gtest/gtest.h"
#include "paralgo/system/condition_variable.h"

TEST(ConditionVariable, Init) {
    ConditionVariable cond;
}

TEST(ConditionVariable, Wait) {
    ConditionVariable event;
    event.Signal();
}

TEST(ConditionVariable, Release) {
}

