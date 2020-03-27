#include "gtest/gtest.h"

TEST(DummyTestsuite, ShouldBePass) {
  EXPECT_EQ(1, 1);
}

TEST(DummyTestsuite, ShouldFail) {
  EXPECT_EQ(0, 1);
}