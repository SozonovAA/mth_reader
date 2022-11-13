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
        auto str = read_file_chars("data/first.in", 200);
        EXPECT_EQ(test_case, str);
    }
    {
        std::string test_case = {
R"(I've paid my dues
Time after time.)"
        };
        auto str = read_file_chars("data/first.in", 34);
        EXPECT_EQ(test_case, str);
    }

//    std::cout << str << std::endl;
}
