#include <gtest/gtest.h>

#include "../src/include/search.h"

TEST(key_preparing_test, add_1_1)
{

    EXPECT_EQ("(..)", utils::key_preparing(std::string{"??"}));
    EXPECT_EQ("()", utils::key_preparing(std::string{""}));
    EXPECT_EQ("(abc)", utils::key_preparing(std::string{"abc"}));
    EXPECT_EQ("([]{},./*-+.)", utils::key_preparing(std::string{"[]{},./*-+."}));
    EXPECT_EQ("(.a.b.c.)", utils::key_preparing(std::string{"?a?b?c?"}));
    EXPECT_EQ("(1.2.3)", utils::key_preparing(std::string{"1?2?3"}));
    EXPECT_EQ('(' + std::string(1000, '.') + ')', utils::key_preparing(std::string(1000, '?')));


}
TEST(string_spliting_test, add_1_1)
{
    std::vector<std::string> test_case {
        "one",
        "two",
        "three",
        "four",
    };
    EXPECT_EQ( test_case, utils::string_spliting("one/two/three/four/", "/"));
    EXPECT_EQ( std::vector<std::string>{"one/two/three/four/"},
               utils::string_spliting("one/two/three/four/", "m"));

    EXPECT_EQ( std::vector<std::string>{"one/two/three/four/"},
               utils::string_spliting("one/two/three/four/", "123132"));

    EXPECT_EQ( std::vector<std::string>{"one/two/three/four/"},
               utils::string_spliting("one/two/three/four/", "."));

    EXPECT_EQ( std::vector<std::string>{},
               utils::string_spliting("one/two/three/four/", "one/two/three/four/"));


    EXPECT_EQ( std::vector<std::string>{"one/two/three/four/"},
               utils::string_spliting("one/two/three/four/", ""));

}
