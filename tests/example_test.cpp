#include <gtest/gtest.h>
#include <image_processing.h>
#include <filter.h>

TEST(BeispielTest, EinfacheAssertion) {
    EXPECT_EQ(1 + 1, 2);
}

TEST(BeispielTest, Addition) {
    const int result = add(1, 2);
    EXPECT_EQ(result, 3);
}

TEST(BeispielTest, Subtraktion) {
    const int result = sub(5, 2);
    EXPECT_EQ(result, 3);
}
