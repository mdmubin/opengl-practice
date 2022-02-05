#include "FileIO.hpp"

#include <fstream>

#include <fmt/core.h>


std::string myutils::readFileContents(std::string &filepath)
{
    std::ifstream reader(filepath, std::ios::in);
    if (reader.fail())
    {
        fmt::print(stderr, "FILENAME: '{}' COULD NOT BE OPENED / FILE DOES NOT EXIST.\n\n", filepath);
        return "";
    }
    return std::string{std::istreambuf_iterator<char>{reader}, {}};
}
