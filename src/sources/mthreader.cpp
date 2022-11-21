#include "../include/mthreader.h"
#include "../include/fileReader.h"
#include "../include/search.h"

namespace business {



types::SearchingResult prepare_key_search(const std::string & str, std::string_view key)
{

    types::SearchingResult ret;

    //todo: брать последнюю строку, если она не нулевая и прибавлять к следующему
    // больште ключи ломают логику
    std::vector<std::string> after_spliting{utils::string_spliting(str, '\n')};

    if(not (ret.is_last_char_n = (str.back() == '\n') )) {
        ret.last_row_size = after_spliting.back().size();
    }
    auto strings_number = after_spliting.size();

    for(const auto & str: after_spliting) {
        types::SearchingResult::all_data_in_row_t adr;
        adr.reserve(strings_number);

        auto row_res = utils::peapare_key_searching(str.begin(),
                                                    str.end(),
                                                    key.data());
        ret.numb_ += row_res.first;

        for(const auto & t : row_res.second) {
            adr.emplace_back(types::SearchingResult::single_data_in_row_t{
                                 std::make_pair(t.first+1, t.second )
                             });
        }
        adr.shrink_to_fit();
        ret.result_.emplace_back(std::move(adr));
    }

    return ret;

}

types::SearchingResult search(const std::string & str, std::string_view key)
{
    return prepare_key_search(str, utils::key_preparing(std::string{key}));
}


void MthReader::bind_finction(function_t f)
{
    bind_f = f;
}

std::vector<types::SearchingResult> MthReader::searching_proc(std::ifstream & fs)
{
    std::string str;
    do{
        str = read_file_chars(fs, reading_ch_n_);
        if(str.size()){
            add_new_searching_th(str);
        }
    }while(str.size());

    while(current_th_numb_.load()) {

    }

    ioService_.stop();
    /*
     * Will wait till all the threads in the thread pool are finished with
     * their assigned tasks and 'join' them. Just assume the threads inside
     * the threadpool will be destroyed by this method.
     */
    threadpool_.join_all();
    return all_res_;
}

void MthReader::myTask(const std::string & str) {

    auto res {bind_f(str, key_)};
    {
        std::lock_guard<std::mutex> lg(m_);

        ++serching_index_;
        all_res_.resize(serching_index_);
        all_res_.at(serching_index_-1) = std::move(res);
    }
    --current_th_numb_;

    return;
}

void MthReader::add_new_searching_th(std::string str)
{
    ++current_th_numb_;
    auto clb = [this, str]() -> void{
        myTask(str);
    };
    ioService_.post(clb);

}


}
