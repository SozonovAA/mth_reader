#ifndef MTHREADER_H
#define MTHREADER_H
#include <future>
#include <vector>

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
};

} // namespace types

//todo: реализовать и протестировать статическую функцию, которая будет читать строку и парсить её
static types::SearchingResult search(std::string_view str, std::string_view key) {
    types::SearchingResult ret;
    std::vector<std::string> after_spliting{utils::string_spliting(str.data(), '\n')};
    auto strings_number = after_spliting.size();

    for(const auto & str: after_spliting) {
        types::SearchingResult::all_data_in_row_t adr;
        adr.reserve(strings_number);
        auto row_res = utils::key_searching(str, utils::key_preparing(std::string{key}));
        ret.numb_ += row_res.first;

        for(const auto & t : row_res.second) {
//            std::cout << t.first << " ";
//            std::cout << t.second << std::endl;
            adr.emplace_back(types::SearchingResult::single_data_in_row_t{
                                 std::make_pair(t.first+1, t.second )
                             });
        }
        adr.shrink_to_fit();
        ret.result_.emplace_back(std::move(adr));
    }

    return ret;
}

//todo: реализовать и протестировать статическую функцию,
//      который будет по вектору из ретерн велью формировать корректный тип для вывода

/**
 * @brief The MthReader class ответственный за создание многопоточных экземпляров функции
 * и последующую генерацию правильного отображения результатов выполнения.
 */
class MthReader
{
public:
    MthReader();


    //todo: реализовать мейн функцию, которая будет запускать чтение из файла и создавать экземпляры фьюч

private:
    //todo: создать тип данных, который будет хранить экзепляры фьюч
    std::future<bool> dpAsync_;



    std::future<bool> data_pack_proc( std::uint16_t cycles_n = 1 )
    {
        return std::async(std::launch::async,[cycles_n,this](){

            return true;
        });
    }


};

} // namespace business

#endif // MTHREADER_H
