#include <gtest/gtest.h>

#include <thread>
#include <chrono>
#include "../src/include/mthreader.h"
#include "../src/include/fileReader.h"



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

    std::uint64_t numb = 0;
    for(const auto & it : std::vector<business::types::SearchingResult>{res}){
        numb+= it.numb_;
    };
    EXPECT_EQ(numb, 3);

}

TEST(mth_test, simple_split_searching_test)
{
    std::string test_case1 = {
        R"(I've paid my dues
Time after time.
I've done my sentence
But committed no )"};

    std::string test_case2 = {
        R"(crime.
And bad mistakes ?
I've made a few.
I've had my share of sand kicked in my face
But I've come through.
)"};
    auto res1 = business::search(test_case1, "?ad");
    auto res2 = business::search(test_case2, "?ad");

    std::uint64_t numb = 0;
    for(const auto & it : std::vector<business::types::SearchingResult>{res1, res2}){
        numb+= it.numb_;
    };
    EXPECT_EQ(numb, 3);

}
TEST(mth_test, MthReader_searching_test_1)
{

    const std::string file_name = "data/first";
    auto f_size = std::filesystem::file_size(file_name + ".in");
    auto fs {open_file(file_name + ".in")};

    auto n_reading_char = 0;
    auto MAX_THREAD_N = std::thread::hardware_concurrency();
    if(f_size > (500000 * MAX_THREAD_N) ) {
        n_reading_char = 500000;
    } else {
        n_reading_char = f_size / MAX_THREAD_N;
    }

    business::MthReader mth("?ad", MAX_THREAD_N, n_reading_char);
    mth.bind_finction(business::prepare_key_search);

    auto ret = mth.searching_proc(fs);
    std::uint64_t numb = 0;
    for(const auto & it : ret){
        numb+= it.numb_;
    };

    auto fs_out {open_file(file_name + ".out")};

    std::string line;
    std::getline(fs_out, line);
    std::uint64_t data_out = std::stoi( line );
    EXPECT_EQ(numb, data_out);
}

TEST(mth_test, MthReader_searching_test_2)
{

    const std::string file_name = "data/second";
    auto f_size = std::filesystem::file_size(file_name + ".in");
    auto fs {open_file(file_name + ".in")};

    auto n_reading_char = 0;
    auto MAX_THREAD_N = std::thread::hardware_concurrency();
    if(f_size > (500000 * MAX_THREAD_N) ) {
        n_reading_char = 500000;
    } else {
        n_reading_char = f_size / MAX_THREAD_N;
    }

    business::MthReader mth("?ad", MAX_THREAD_N, n_reading_char);
    mth.bind_finction(business::prepare_key_search);

    auto ret = mth.searching_proc(fs);
    std::uint64_t numb = 0;
    for(const auto & it : ret){
        numb+= it.numb_;
    };

    auto fs_out {open_file(file_name + ".out")};

    std::string line;
    std::getline(fs_out, line);
    std::uint64_t data_out = std::stoi( line );
    EXPECT_EQ(numb, data_out);
}

TEST(mth_test, MthReader_searching_test_3)
{

    const std::string file_name = "data/third";
    auto f_size = std::filesystem::file_size(file_name + ".in");
    auto fs {open_file(file_name + ".in")};

    auto n_reading_char = 0;
    auto MAX_THREAD_N = std::thread::hardware_concurrency();
    if(f_size > (500000 * MAX_THREAD_N) ) {
        n_reading_char = 500000;
    } else {
        n_reading_char = f_size / MAX_THREAD_N;
    }

    business::MthReader mth("?ad", MAX_THREAD_N, n_reading_char);
    mth.bind_finction(business::prepare_key_search);

    auto ret = mth.searching_proc(fs);
    std::uint64_t numb = 0;
    for(const auto & it : ret){
        numb+= it.numb_;
    };

    auto fs_out {open_file(file_name + ".out")};

    std::string line;
    std::getline(fs_out, line);
    std::uint64_t data_out = std::stoi( line );
    EXPECT_EQ(numb, data_out);

}
TEST(mth_test, MthReader_searching_test_4)
{

    const std::string file_name = "data/fourth";
    auto f_size = std::filesystem::file_size(file_name + ".in");
    auto fs {open_file(file_name + ".in")};

    auto n_reading_char = 0;
    auto MAX_THREAD_N = std::thread::hardware_concurrency();
    if(f_size > (500000 * MAX_THREAD_N) ) {
        n_reading_char = 500000;
    } else {
        n_reading_char = f_size / MAX_THREAD_N;
    }

    business::MthReader mth("?ad", MAX_THREAD_N, n_reading_char);
    mth.bind_finction(business::prepare_key_search);

    auto ret = mth.searching_proc(fs);
    std::uint64_t numb = 0;
    for(const auto & it : ret){
        numb+= it.numb_;
    };

    auto fs_out {open_file(file_name + ".out")};

    std::string line;
    std::getline(fs_out, line);
    std::uint64_t data_out = std::stoi( line );
    EXPECT_EQ(numb, data_out);

}



TEST(mth_test, MthReader_searching_test_6)
{

    const std::string file_name = "data/sixth";
    auto f_size = std::filesystem::file_size(file_name + ".in");
    auto fs {open_file(file_name + ".in")};

    auto n_reading_char = 0;
    auto MAX_THREAD_N = std::thread::hardware_concurrency();
    if(f_size > (500000 * MAX_THREAD_N) ) {
        n_reading_char = 500000;
    } else {
        n_reading_char = f_size / MAX_THREAD_N;
    }

    business::MthReader mth("I've paid my duesTime after time.I've done my sentenceBut committed no crime.And bad mistakes ?I've made a few.I've had my share of sand kicked in my faceBut I've come through.I've paid my duesTime after time.I've done my sentenceBut committed no crime.And bad mistakes ?I've made a few.I've had my share of sand kicked in my faceBut I've come through.I've paid my duesTime after time.I've done my sentenceBut committed no crime.And bad mistakes ?I've made a few.I've had my share of sand kicked in my faceBut I've come through.I've paid my duesTime after time.I've done my sentenceBut committed no crime.And bad mistakes ?I've made a few.I've had my share of sand kicked in my faceBut I've come through.I've paid my duesTime after time.I've done my sentenceBut committed no crime.And bad mistakes ?I've made a few.I've had my share of sand kicked in my faceBut I've come through.I've paid my duesTime after time.I've done my sentenceBut committed no crime.And bad mistakes ?I've made a few.I've had",
                            MAX_THREAD_N,
                            n_reading_char);
    mth.bind_finction(business::prepare_key_search);

    auto ret = mth.searching_proc(fs);
    std::uint64_t numb = 0;
    for(const auto & it : ret){
        numb+= it.numb_;
    };

    auto fs_out {open_file(file_name + ".out")};

    std::string line;
    std::getline(fs_out, line);
    std::uint64_t data_out = std::stoi( line );
    EXPECT_EQ(numb, data_out);

}
