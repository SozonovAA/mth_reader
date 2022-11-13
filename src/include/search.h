#ifndef SEARCH_H
#define SEARCH_H
#include <string>
#include <vector>
#include <regex>
#include <iostream>

namespace utils {
namespace types {
using KeysNumber_t = std::uint32_t;

using KeysPos_t = std::uint32_t;
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
static void string_spliting(std::string const &str, const char delim,
            std::vector<std::string> &out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}


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

    const auto r = std::regex(std::string{"(["+any_from+"])"});
    return std::string{ '(' + regex_replace(key.data(), r, any_to) + ')' };
}


static types::SearchRet_t key_searching(const std::string & string, const std::string & key){

    types::KeysFinded_t ret;
    const std::regex base_regex(key_preparing(key));
    const std::vector<std::smatch> matches{
        std::sregex_iterator{string.begin(), string.end(), base_regex},
        std::sregex_iterator{}
    };
    for(const auto & t : matches) {
        ret.push_back(
                    std::make_pair(static_cast<types::KeysPos_t>(t.position(1)),
                                   t.str(1)
                                   )
                    );
    }
    return std::make_pair(matches.size(), ret);
}

static void result_printing(const types::SearchRet_t & res) {
    std::cout << res.first << std::endl;
    for(const auto & t : res.second) {
        std::cout << t.first << " ";
        std::cout << t.second << std::endl;
    }
}

} // namespace utils

#endif // SEARCH_H
