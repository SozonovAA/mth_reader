#include <gtest/gtest.h>

#include "../src/include/fileReader.h"
#include "../src/include/search.h"


TEST(file_read_test, read_file_chars)
{
    {
        std::string test_case = {
R"(I've paid my dues
Time after time.
I've done my sentence
But committed no crime.
And bad mistakes ?
I've made a few.
I've had my share of sand kicked in my face
But I've come through.
)"
        };

        auto fs = open_file("data/first.in");
        auto str = read_file_chars(fs, 200);
        EXPECT_EQ(test_case, str);
    }
    {
        std::string test_case = {
R"(I've paid my dues
Time after time.
)"
        };
        auto fs = open_file("data/first.in");
        auto str = read_file_chars(fs, 35);
        EXPECT_EQ(test_case, str);

        std::string test_case1 = {
            R"(I've done my sentence
)"
        };
        auto str1 = read_file_chars(fs, 22);
        EXPECT_EQ(test_case1, str1);

        std::string test_case2 = {
            R"(But committed no crime.
And bad mistakes ?
I've made a few.
I've had my share of sand kicked in my face
But I've come through.
)"
        };
        auto str2 = read_file_chars(fs, 1000);
        EXPECT_EQ(test_case2, str2);
    }
}
