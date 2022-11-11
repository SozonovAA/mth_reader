#ifndef SEARCH_H
#define SEARCH_H
#include <string>
#include <vector>
#include <regex>
#include <iostream>

namespace utils {
namespace types {
using KeyNumber_t = std::uint32_t;

using KeysPos_t = std::uint32_t;
using KeyInStr_t = std::string;

using KeyFinded_t = std::pair<KeysPos_t, KeyInStr_t>;
using KeysFinded_t = std::vector<KeyFinded_t>;
using SearchRet_t = std::pair<KeyNumber_t, KeysFinded_t>;

} // namespace types


static const std::string key_preparing(const std::string_view & key,
                                     const std::string & from = "?",
                                     const std::string & to = "."){

    const auto r = std::regex(std::string{"(["+from+"])"});
    return std::string{ '(' + regex_replace(key.data(), r, to) + ')' };
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
