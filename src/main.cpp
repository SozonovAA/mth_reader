#include <src/config/MyPrgConfig.h>

#include "include/search.h"
#ifdef USE_SOME_LIB

#endif

#include <thread>
#include <chrono>
#include "../src/include/mthreader.h"
#include "../src/include/fileReader.h"

int main(){
    const std::string file_name = "data/third.in";
    auto f_size = std::filesystem::file_size(file_name);
    auto fs {open_file(file_name)};
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
    business::print(ret);

}
