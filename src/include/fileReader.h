#ifndef FILEREADER_H
#define FILEREADER_H
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

static std::ifstream open_file( const std::filesystem::path& filepath, std::ostream & info = std::cout ) {
    if( not std::filesystem::exists( filepath ) )
          throw std::invalid_argument{ "File: " + filepath.string() + " does not exist." };

      if( not std::filesystem::is_regular_file( filepath ) )
          throw std::invalid_argument{"File: " + filepath.string() + " is not a file."};

      info << "File: " + filepath.string() + " is valid." << std::endl;

      return std::ifstream(filepath, std::ios::in | std::ios::binary );
}

static std::string read_file_chars( std::ifstream & f, std::uint32_t numb)
{
    // Create a buffer.
    std::vector<char> result(numb);
    // Read the whole file into the buffer.
    f.readsome(&*result.begin(), numb);
    result.resize(f.gcount());

    return std::string(result.begin(), result.end());
}

#endif // FILEREADER_H
