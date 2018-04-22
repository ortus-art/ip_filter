#include <common.h>

#include <gtest/gtest.h>

using namespace testing;

TEST(main_case, test_version_valid) { ASSERT_STRNE(version(), "0"); }

int main(int argc, char **argv) {
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
