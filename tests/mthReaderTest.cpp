#include <gtest/gtest.h>

#include "../src/include/mthreader.h"


TEST(mth_test, simple_searching_test)
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
    auto res = business::search(test_case, "?ad");
    std::uint64_t row = 0;
    EXPECT_EQ(res.numb_, 3);

    EXPECT_EQ(res.result_.at(4).at(0).first, 5);
    EXPECT_EQ(res.result_.at(5).at(0).first, 6);
    EXPECT_EQ(res.result_.at(6).at(0).first, 6);

    EXPECT_EQ(res.result_.at(4).at(0).second, "bad");
    EXPECT_EQ(res.result_.at(5).at(0).second, "mad");
    EXPECT_EQ(res.result_.at(6).at(0).second, "had");

}
