#include <gtest/gtest.h>
#include <string>
#include "blocks.h"
#include "parser.h"

TEST(ComparisonAddFunctionAndUpdateLine, BasicAssertions)
{
   // GTEST_SKIP();
std::string program1 = R"(#include <iostream>

using namespace std;

void main()
{
    cout << "hello! \" world!";
    int c = 145;
})";

std::string program2 = R"(#include <iostream>

using namespace std;

void main()
{
    cout << "hellfo! \" world!";
    int c = 145;
    int g = 444;
}

int func(int a)
{
    int b = a;
    return b + 5;
})";

std::string expected = R"(#include <iostream>
using namespace std;
void main()
{
- cout << "hello! \" world!";
+ cout << "hellfo! \" world!";
int c = 145;
+ int g = 444;
}
+ int func(int a)
{
+ int b = a;
+ return b + 5;
})";

    diff::parsers::parser p1;
    diff::blocks::block a = p1.parse(program1);

    diff::parsers::parser p2;
    diff::blocks::block b = p2.parse(program2);

    diff::blocks::block c = a.compare(b);
    std::string result = c.output();

    expected.erase(std::remove(expected.begin(), expected.end(), '\n'), expected.cend());
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.cend());

    EXPECT_TRUE(result == expected);
}

TEST(ComparisonRemoveSingleLine, BasicAssertions)
{
std::string program1 = R"(#include <iostream>

using namespace std;

void main()
{
    cout << "hello! \" world!";
    int c = 145;
})";

std::string program2 = R"(#include <iostream>

using namespace std;

void main()
{
    cout << "hello! \" world!";
})";

std::string expected = R"(#include <iostream>
using namespace std;
void main()
{
cout << "hello! \" world!";
- int c = 145;
})";

    diff::parsers::parser p1;
    diff::blocks::block a = p1.parse(program1);

    diff::parsers::parser p2;
    diff::blocks::block b = p2.parse(program2);

    diff::blocks::block c = a.compare(b);
    std::string result = c.output();

    expected.erase(std::remove(expected.begin(), expected.end(), '\n'), expected.cend());
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.cend());

    EXPECT_TRUE(result == expected);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}