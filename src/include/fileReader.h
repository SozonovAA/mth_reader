#ifndef FILEREADER_H
#define FILEREADER_H
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

static std::ifstream read_file( const std::filesystem::path& filepath, std::ostream & info = std::cout ) {

    if( not std::filesystem::exists( filepath ) )
        throw std::invalid_argument{ "File: " + filepath.string() + " does not exist." };

    if( not std::filesystem::is_regular_file( filepath ) )
        throw std::invalid_argument{"File: " + filepath.string() + " is not a file."};

    info << "File: " + filepath.string() + " is valid." << std::endl;

    return { filepath };
}

static std::string read_full_stream( std::ifstream _is ) {
    std::string file_;
    while( _is ){
        std::string file_str;
        std::getline( _is, file_str);
        file_ += file_str;
    }
    return file_;
}
#endif // FILEREADER_H
