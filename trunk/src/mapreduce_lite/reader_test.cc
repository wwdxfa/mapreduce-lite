#include "paralgo/mapreduce_lite/reader.h"

#include "paralgo/base/common.h"
#include "gtest/gtest.h"

namespace mapreduce_lite {
Reader* CreateReader(const char* format_name) {
  return CREATE_READER(format_name);
}
}

TEST(ReaderTest, ReaderCreationByName) {
  EXPECT_TRUE(mapreduce_lite::CreateReader("text") != NULL);
  EXPECT_TRUE(mapreduce_lite::CreateReader("protofile") != NULL);

  EXPECT_TRUE(mapreduce_lite::CreateReader("") == NULL);
  EXPECT_TRUE(mapreduce_lite::CreateReader("something_without_name") == NULL);
}
