// Copyright 2010 Tencent Inc.
// Author: Yi Wang (yiwang@tencent.com)
//
#include <stdio.h>
#include <string>

#include "gtest/gtest.h"

#include "paralgo/base/common.h"
#include "paralgo/mapreduce_lite/protofile.h"
#include "paralgo/mapreduce_lite/protofile.pb.h"

namespace mapreduce_lite {
namespace protofile {

using std::string;

static const char* kTestKey = "a key";
static const char* kTestValue = "a value";

static void CheckWriteReadConsistency(const string& filename) {
  KeyValuePair pair;
  pair.set_key(kTestKey);
  pair.set_value(kTestValue);

  FILE* file = fopen(filename.c_str(), "w");
  CHECK(file != NULL);
  WriteRecord(file, kTestKey, kTestValue);
  WriteRecord(file, kTestKey, pair);
  fclose(file);

  CHECK((file = fopen(filename.c_str(), "r")) != NULL);
  string key, value;
  CHECK(ReadRecord(file, &key, &value));
  EXPECT_EQ(key, kTestKey);
  EXPECT_EQ(value, kTestValue);

  pair.Clear();
  CHECK(ReadRecord(file, &key, &pair));
  EXPECT_EQ(pair.key(), kTestKey);
  EXPECT_EQ(pair.value(), kTestValue);

  EXPECT_TRUE(!ReadRecord(file, &key, &value));
}

}  // namespace protofile
}  // namespace mapreduce_lite

TEST(ProtofileTest, LocalRecordIO) {
  static const char* kFilename = "/tmp/ProtofileTestLocalRecordIO";
  mapreduce_lite::protofile::CheckWriteReadConsistency(kFilename);
}
