#include "paralgo/mapreduce_lite/utils.h"

#include "gtest/gtest.h"

// TODO(yiwang): We need a facility like EXPECT_FATAL before we can do
// the following test:
//
// TEST(MapReduceLiteUtils, DieOnOpenNonExistingFile) {
//   EXPECT_TRUE(OpenFileOrDie("/a-non-existing-file", "r") == NULL);
// }

TEST(MapReduceLiteUtils, CreateNonExistingFile) {
  EXPECT_TRUE(OpenFileOrDie("/tmp/a-non-existing-file", "w") != NULL);
}
