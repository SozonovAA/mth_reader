#ifndef MTHREADER_H
#define MTHREADER_H
#include <future>
#include <vector>
#include <mutex>
#include <atomic>

#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include "search.h"
namespace business {

namespace types {

//todo: создать тип данных, который будет возвращаься из функции
struct SearchingResult {
    using numbers_of_finded_res_t = std::uint64_t;

    using position_in_row_t = std::uint64_t;
    using finded_data_t =  std::string;
    using single_data_in_row_t = std::pair<position_in_row_t, finded_data_t>;
    using all_data_in_row_t = std::vector<single_data_in_row_t>;
    using all_finded_data_r = std::vector<all_data_in_row_t>;

    /**
     * @brief numb_ количество ключей в данном фрагменте текста
     */
    numbers_of_finded_res_t numb_ = 0;

    /**
     * @brief result_ все данные, которые были надйены в тексте
     */
    all_finded_data_r result_;

    bool is_last_char_n = true;

    std::uint64_t last_row_size = 0;
};

} // namespace types

types::SearchingResult search(const std::string &str, std::string_view key);
types::SearchingResult prepare_key_search(const std::string &str, std::string_view key);

//todo: реализовать и протестировать статическую функцию,
//      который будет по вектору из ретерн велью формировать корректный тип для вывода
static std::uint64_t print(const std::vector<types::SearchingResult> res, std::ostream & info = std::cout) {
    std::int64_t row = 0;
    std::uint64_t numb = 0;

    std::for_each(res.begin(), res.end(), [&](const auto & it){
        numb+= it.numb_;
    });
    info << numb << std::endl;
    std::uint16_t add_to_first_row = 0;

    for(auto & singl_res : res){
        for(const auto & it : singl_res.result_){
            ++row;
            for(const auto & itt : it){
                info << row << " " << add_to_first_row + itt.first << " " << itt.second << std::endl;
                }
            add_to_first_row = 0;
            }

        if(!singl_res.is_last_char_n) {
            --row;
        }
        add_to_first_row = singl_res.last_row_size;

        }
    return numb;
}

//todo: возможно он просто запускатор и следитель за количеством потоков
/**
 * @brief The MthReader class ответственный за создание многопоточных экземпляров функции
 * и последующую генерацию правильного отображения результатов выполнения.
 */
class MthReader
{
public:
    using function_t = std::function<types::SearchingResult(std::string str, std::string_view key)>;

    MthReader(std::string key, std::uint16_t max_th_number, std::uint64_t reading_ch_n) :
        dpAsync_{},
        key_{utils::key_preparing(key)},
        max_th_number_{max_th_number},
        reading_ch_n_{reading_ch_n},
        current_th_numb_{0},
        serching_index_{},
        all_res_{},
        m_{},
        ioService_{},
        threadpool_{},
        work_(ioService_)
    {
        if(auto key_size = key.size(); key_size > reading_ch_n) {
            reading_ch_n_ = key_size * 50;
            max_th_number_ = (max_th_number * reading_ch_n) / reading_ch_n_;
        }
        for(auto i = 0; i < max_th_number ; ++i){
            threadpool_.create_thread(
                boost::bind(&boost::asio::io_service::run, &ioService_)
            );
        }

    };



    void bind_finction(function_t f);

    //todo: реализовать мейн функцию, которая будет запускать чтение из файла и создавать экземпляры фьюч
    std::vector<types::SearchingResult> searching_proc(std::ifstream &fs);

private:
    //todo: создать тип данных, который будет хранить экзепляры фьюч
    std::vector<std::future<void>> dpAsync_;

    /**
     * @brief key_ ключ, который необходимо искать
     */
    const std::string key_;

    std::uint16_t max_th_number_;

    std::uint64_t reading_ch_n_;

    std::atomic<std::uint16_t> current_th_numb_;

    std::uint64_t serching_index_;


    std::vector<types::SearchingResult> all_res_;

    std::mutex m_;

    /*
     * Create an asio::io_service and a thread_group (through pool in essence)
     */
    boost::asio::io_service ioService_;
    boost::thread_group threadpool_;
    /*
     * This will start the ioService processing loop. All tasks
     * assigned with ioService.post() will start executing.
     */
    boost::asio::io_service::work work_;


    /**
     * @brief bind_f экземпляр функции, которая будет вызываться в отдельном потоке
     */
    function_t bind_f;

    void add_new_searching_th(std::string str);


    void myTask(const std::string &str);
};

} // namespace business

#endif // MTHREADER_H
