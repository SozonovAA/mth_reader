#include "../include/search.h"
std::vector<std::string> utils::string_spliting(const std::string &str, const char delim)
{
    std::vector<std::string> out;

    if(*str.begin() == '\n') {
        out.push_back({});
    }
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }

    return out;

}



utils::types::SearchRet_t utils::peapare_key_searching(const std::string &string, const std::string &key)
{

    utils::types::KeysFinded_t ret;
    const std::regex base_regex(key);
    const std::vector<std::smatch> matches{
        std::sregex_iterator{string.begin(), string.end(), base_regex},
        std::sregex_iterator{}
    };
    for(const auto & t : matches) {
        ret.push_back(
                    std::make_pair(static_cast<utils::types::KeysPos_t>(t.position(1)),
                                   t.str(1)
                                   )
                    );
    }
    return std::make_pair(matches.size(), ret);
}



utils::types::SearchRet_t utils::peapare_key_searching(std::string::const_iterator beg,
                                                       std::string::const_iterator end,
                                                       const std::string &key)
{
    utils::types::KeysFinded_t ret;
    const std::regex base_regex(key);
    const std::vector<std::smatch> matches{
        std::sregex_iterator{beg, end, base_regex},
        std::sregex_iterator{}
    };
    for(const auto & t : matches) {
        ret.push_back(
                    std::make_pair(static_cast<utils::types::KeysPos_t>(t.position(1)),
                                   t.str(1)
                                   )
                    );
    }
    return std::make_pair(matches.size(), ret);
}

utils::types::SearchRet_t utils::key_searching(const std::string & string, const std::string & key){


    return utils::peapare_key_searching(string, utils::key_preparing(key));
}
utils::types::SearchRet_t utils::key_searching(std::string::const_iterator beg,
                                               std::string::const_iterator end,
                                               const std::string &key)
{

    return utils::peapare_key_searching(beg, end, utils::key_preparing(key));
}
