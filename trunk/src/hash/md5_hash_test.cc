// Copyright 2010 Tencent Inc.
// Author: Yi Wang (yiwang@tencet.com)
//
// This unittest uses grouth-truth MD5 results from Wikipedia:
// http://en.wikipedia.org/wiki/MD5#MD5_hashes.

#include <stdio.h>

#include "gtest/gtest.h"

#include "paralgo/base/common.h"
#include "paralgo/hash/md5_hash.h"

TEST(MD5Test, AsGroundTruthOnWikipedia) {
  EXPECT_EQ(MD5Hash("The quick brown fox jumps over the lazy dog"),
            0x82b62b379d7d109eLLU);
  EXPECT_EQ(MD5Hash("The quick brown fox jumps over the lazy dog."),
            0x1cfbd090c209d9e4LLU);
  EXPECT_EQ(MD5Hash(""), 0x04b2008fd98c1dd4LLU);
}
