// AI Was used to get a template for testing. Specific fixes were done by me. Comments were also added for clarity. AI Used to help with google test process on VS 2022

#include <gtest/gtest.h>
#include "mathUtils.h"
#include "pch.h"

// Test for sumRange method
TEST(MathUtilsTest, SumRange) {
    EXPECT_EQ(MathUtils::sumRange(1, 5), 15); // 1 + 2 + 3 + 4 + 5 = 15
    EXPECT_EQ(MathUtils::sumRange(0, 3), 6); // 0 + 1 + 2 + 3 = 6
    EXPECT_EQ(MathUtils::sumRange(-2, 2), 0); // -2 + -1 + 0 + 1 + 2 = 0
    EXPECT_EQ(MathUtils::sumRange(5, 5), 5); // start == end
    EXPECT_EQ(MathUtils::sumRange(-3, -1), -6); // -3 + -2 + -1 = -6
}

// Test for containsNegative method
TEST(MathUtilsTest, ContainsNegative) {
    std::vector<int> values1 = { 3, -1, 5, 7 };
    std::vector<int> values2 = { 3, 1, 5, 7 };
    std::vector<int> values3 = { -3, -1, -5, -7 };
    std::vector<int> values4 = {};
    EXPECT_TRUE(MathUtils::containsNegative(values1));
    EXPECT_FALSE(MathUtils::containsNegative(values2));
    EXPECT_TRUE(MathUtils::containsNegative(values3));
    EXPECT_FALSE(MathUtils::containsNegative(values4)); // empty list
}

// Test for findMax method
TEST(MathUtilsTest, FindMax) {
    std::vector<int> values1 = { 3, -1, 5, 7 };
    std::vector<int> values2 = { 3, 1, 5, 7 };
    std::vector<int> values3 = { -3, -1, -5, -7 };
    std::vector<int> values4 = {};
    std::vector<int> values5 = { 5, 5, 5, 5 }; // all values are equal
    EXPECT_EQ(MathUtils::findMax(values1), 7);
    EXPECT_EQ(MathUtils::findMax(values2), 7);
    EXPECT_EQ(MathUtils::findMax(values3), -1);
    EXPECT_THROW(MathUtils::findMax(values4), std::invalid_argument); // Expect exception for empty list
    EXPECT_EQ(MathUtils::findMax(values5), 5); // all values are equal
}

// Main function to run all tests
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}