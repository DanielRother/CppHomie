#include <gtest/gtest.h>
#include "Utils/StringUtils.h"

namespace Rovi {
    TEST(StringUtils, fullfile) { 
        EXPECT_EQ(StringUtils::fullfile("aaa", "bbb"), "aaa/bbb/");
        EXPECT_EQ(StringUtils::fullfile("aaa", "bbb/"), "aaa/bbb/");
        EXPECT_EQ(StringUtils::fullfile("aaa", "bbb/ccc"), "aaa/bbb/ccc/");
        EXPECT_EQ(StringUtils::fullfile("aaa/ccc", "bbb/ccc"), "aaa/ccc/bbb/ccc/");
        EXPECT_EQ(StringUtils::fullfile("aaa/ccc/", "bbb/ccc"), "aaa/ccc/bbb/ccc/");
    }

    TEST(StringUtils, splitString) { 
        {
            auto values = StringUtils::splitString("123,456,789", ',');
            EXPECT_EQ(values.size(), size_t(3));
            EXPECT_EQ(values[0], "123");
            EXPECT_EQ(values[1], "456");
            EXPECT_EQ(values[2], "789");
        }
        {
            auto values = StringUtils::splitString(",123,456,789,", ',');
            EXPECT_EQ(values.size(), size_t(4));
            EXPECT_EQ(values[0], "");
            EXPECT_EQ(values[1], "123");
            EXPECT_EQ(values[2], "456");
            EXPECT_EQ(values[3], "789");
        }
        {
            auto values = StringUtils::splitString("abc_def", '_');
            EXPECT_EQ(values.size(), size_t(2));
            EXPECT_EQ(values[0], "abc");
            EXPECT_EQ(values[1], "def");
        }
        {
            auto values = StringUtils::splitString("abc_def_", '_');
            EXPECT_EQ(values.size(), size_t(2));
            EXPECT_EQ(values[0], "abc");
            EXPECT_EQ(values[1], "def");
        }
        {
            auto values = StringUtils::splitString("_abc_def", '_');
            EXPECT_EQ(values.size(), size_t(3));
            EXPECT_EQ(values[0], "");
            EXPECT_EQ(values[1], "abc");
            EXPECT_EQ(values[2], "def");
        }
    }

    TEST(StringUtils, toString) {
        EXPECT_EQ(StringUtils::toString(1), "1");
        EXPECT_EQ(StringUtils::toString(1.0), "1");
        EXPECT_EQ(StringUtils::toString(1.2), "1.2");
        EXPECT_EQ(StringUtils::toString(1.), "1");
        EXPECT_EQ(StringUtils::toString(.0), "0");
        EXPECT_EQ(StringUtils::toString(.1), "0.1");
        EXPECT_EQ(StringUtils::toString(1e2), "100");
        EXPECT_EQ(StringUtils::toString(1E2), "100");
    }

    TEST(StringUtils, toLower) {
        EXPECT_EQ(StringUtils::toLower("AAA"), "aaa");
        EXPECT_EQ(StringUtils::toLower("abA"), "aba");
        EXPECT_EQ(StringUtils::toLower("aBA"), "aba");
        EXPECT_EQ(StringUtils::toLower("AbA"), "aba");
        EXPECT_EQ(StringUtils::toLower("ABa"), "aba");
        EXPECT_EQ(StringUtils::toLower("aba"), "aba");
        EXPECT_EQ(StringUtils::toLower("AA:"), "aa:");
    }

    TEST(StringUtils, checkStringForAllowedCharacters) {
        std::string allowedCharacters = "0123456789,";
        EXPECT_TRUE(StringUtils::checkStringForAllowedCharacters("12", allowedCharacters));
        EXPECT_FALSE(StringUtils::checkStringForAllowedCharacters("12.3", allowedCharacters));
        EXPECT_FALSE(StringUtils::checkStringForAllowedCharacters("12,3f", allowedCharacters));
    }

    TEST(StringUtils, trim) {
        EXPECT_EQ(StringUtils::trim("   aaa bbbb  cc     "), "aaa bbbb  cc");
    }

    TEST(FfileIOUtils, removeCharsFromString) {
        EXPECT_EQ(StringUtils::removeCharsFromString("abcd  11+aas- ( aoomw897 &", "+-&"), "abcd  11aas ( aoomw897 ");
    }
}