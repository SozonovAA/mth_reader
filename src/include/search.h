#ifndef SEARCH_H
#define SEARCH_H
#include <string>
#include <vector>
#include <regex>
#include <iostream>

#include <mutex>

namespace utils {
namespace types {
using KeysNumber_t = std::uint64_t;

using KeysPos_t = std::uint64_t;
using KeyInStr_t = std::string;

using KeyFinded_t = std::pair<KeysPos_t, KeyInStr_t>;
using KeysFinded_t = std::vector<KeyFinded_t>;
using SearchRet_t = std::pair<KeysNumber_t, KeysFinded_t>;

} // namespace types

/**
 * @brief string_spliting функция разделения строки на вектор строк по определенному разделителю
 * @param str исходная строка
 * @param delim разделитель
 * @param out вектор строк, полученных после сплита
 */
std::vector<std::string> string_spliting(const std::string & str, const char delim);



/**
 * @brief key_preparing функция "подготовки" ключа к использованию в регулярном выражении
 * @param key исходный ключ
 * @param any_from символ в ключе, который обозначает любой символ
 * @param any_to символ в регулярном выражении, который обозначает любой символ
 * @return подготовленный ключ в круглых скобках, для использования в регулярных выражениях
 */
static const std::string key_preparing(const std::string_view & key,
                                     const std::string & any_from = "?",
                                     const std::string & any_to = "."){
    std::mutex m;
    std::lock_guard<std::mutex> lg(m);
    const auto r = std::regex(std::string{"(["+any_from+"])"});
    return std::string{ '(' + regex_replace(key.data(), r, any_to) + ')' };
}


types::SearchRet_t key_searching(const std::string & string, const std::string & key);
types::SearchRet_t key_searching(std::string::const_iterator beg,
                                 std::string::const_iterator end,
                                 const std::string & key);

types::SearchRet_t peapare_key_searching(const std::string & string, const std::string & key);
types::SearchRet_t peapare_key_searching(std::string::const_iterator beg,
                                         std::string::const_iterator end,
                                         const std::string & key);

static void result_printing(const types::SearchRet_t & res) {
    std::cout << res.first << std::endl;
    for(const auto & t : res.second) {
        std::cout << t.first << " ";
        std::cout << t.second << std::endl;
    }
}

} // namespace utils

#endif // SEARCH_H
