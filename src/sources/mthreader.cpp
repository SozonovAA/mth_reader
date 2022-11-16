#include "../include/mthreader.h"
#include "../include/fileReader.h"
#include "../include/search.h"

namespace business {

types::SearchingResult search(std::string str, std::string_view key)
{

    types::SearchingResult ret;

    std::vector<std::string> after_spliting{utils::string_spliting(str, '\n')};

    if(not (ret.is_last_char_n = (str.back() == '\n') )) {
        ret.last_row_size = after_spliting.back().size();
    }
    auto strings_number = after_spliting.size();

    for(const auto & str: after_spliting) {
        types::SearchingResult::all_data_in_row_t adr;
        adr.reserve(strings_number);
        auto row_res = utils::key_searching(str, utils::key_preparing(std::string{key}));
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


void MthReader::bind_finction(function_t f)
{
    bind_f = f;
}

std::vector<types::SearchingResult> MthReader::searching_proc(std::ifstream & fs)
{
    std::string str;
    do{
        str = read_file_chars(fs, reading_ch_n_);
        if(m_.try_lock() and str.size()){
            add_new_searching_th(str);
            m_.unlock();
        }
    }while(str.size());

    while(! current_th_numb_) {

    }

    return all_res_;
}

bool MthReader::add_new_searching_th(std::string str)
{
    if(current_th_numb_ < max_th_number_){

        ++serching_index_;
        all_res_.resize(serching_index_);

        //todo: необходимо разобраться как правильно контролировать количество потоков
        std::future<void> as = { std::async(std::launch::async,[this, str](){
            ++current_th_numb_;
            all_res_.at(serching_index_-1) = (bind_f(str, key_));
            --current_th_numb_;
        })};
        dpAsync_.emplace_back(std::move(as));
        m_.unlock();
        return true;
    } else {
        m_.lock();
        return false;
    }

}


}
