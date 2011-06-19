// Copyright 2010
// Author: yiwang@tencent.com (Yi Wang)
//
#include <vector>
#include <string>

#include "gtest/gtest.h"

#include "paralgo/base/common.h"
#include "paralgo/strutil/split_string.h"

TEST(SplitStringTest, SplitStringUsingCompoundDelim) {
  std::string full(" apple \torange ");
  std::vector<std::string> subs;
  SplitStringUsing(full, " \t", &subs);
  EXPECT_EQ(subs.size(), 2);
  EXPECT_EQ(subs[0], std::string("apple"));
  EXPECT_EQ(subs[1], std::string("orange"));
}

TEST(SplitStringTest, testSplitStringUsingSingleDelim) {
  std::string full(" apple orange ");
  std::vector<std::string> subs;
  SplitStringUsing(full, " ", &subs);
  EXPECT_EQ(subs.size(), 2);
  EXPECT_EQ(subs[0], std::string("apple"));
  EXPECT_EQ(subs[1], std::string("orange"));
}

TEST(SplitStringTest, testSplitingNoDelimString) {
  std::string full("apple");
  std::vector<std::string> subs;
  SplitStringUsing(full, " ", &subs);
  EXPECT_EQ(subs.size(), 1);
  EXPECT_EQ(subs[0], std::string("apple"));
}
