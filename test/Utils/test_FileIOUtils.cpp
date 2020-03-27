#include <gtest/gtest.h>
#include "Utils/FileIOUtils.h"

TEST(FileIOUtils, splitString) { 
    {
        auto values = splitString("123,456,789", ',');
        EXPECT_EQ(values.size(), size_t(3));
        EXPECT_EQ(values[0], "123");
        EXPECT_EQ(values[1], "456");
        EXPECT_EQ(values[2], "789");
    }
    {
        auto values = splitString("abc_def", '_');
        EXPECT_EQ(values.size(), size_t(2));
        EXPECT_EQ(values[0], "abc");
        EXPECT_EQ(values[1], "def");
    }
}

TEST(FileIOUtils, toString) {
    EXPECT_EQ(to_string(1), "1");
    EXPECT_EQ(to_string(1.0), "1");
    EXPECT_EQ(to_string(1.2), "1.2");
    EXPECT_EQ(to_string(1.), "1");
    EXPECT_EQ(to_string(.0), "0");
    EXPECT_EQ(to_string(.1), "0.1");
    EXPECT_EQ(to_string(1e2), "100");
    EXPECT_EQ(to_string(1E2), "100");
}

TEST(FileIOUtils, toLower) {
    EXPECT_EQ(toLower("AAA"), "aaa");
    EXPECT_EQ(toLower("AbA"), "aba");
    EXPECT_EQ(toLower("AA:"), "aa:");
}

TEST(FileIOUtils, checkStringForAllowedCharacters) {
    std::string allowedCharacters = "0123456789,";
    EXPECT_TRUE(checkStringForAllowedCharacters("12", allowedCharacters));
    EXPECT_FALSE(checkStringForAllowedCharacters("12.3", allowedCharacters));
    EXPECT_FALSE(checkStringForAllowedCharacters("12,3f", allowedCharacters));
}

TEST(FileIOUtils, trim) {
    EXPECT_EQ(trim("   aaa bbbb  cc     "), "aaa bbbb  cc");
}

TEST(FfileIOUtils, removeCharsFromString) {
    EXPECT_EQ(removeCharsFromString("abcd  11+aas- ( aoomw897 &", "+-&"), "abcd  11aas ( aoomw897 ");
}