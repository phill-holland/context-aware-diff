#include <gtest/gtest.h>
#include <string>

TEST(BasicProgramExecutionWithStringOutput, BasicAssertions)
{
    EXPECT_TRUE(true);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
