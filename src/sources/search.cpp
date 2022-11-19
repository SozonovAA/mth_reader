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
