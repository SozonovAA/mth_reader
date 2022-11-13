#ifndef FILEREADER_H
#define FILEREADER_H
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string read_file_chars( const std::filesystem::path& path, std::uint32_t numb)
{
    // Open the stream to 'lock' the file.
    std::ifstream f(path, std::ios::in | std::ios::binary);

    // Create a buffer.
    std::vector<char> result(numb);
    // Read the whole file into the buffer.
    f.readsome(&*result.begin(), numb);
    result.resize(f.gcount());

    return std::string(result.begin(), result.end());
}

#endif // FILEREADER_H
