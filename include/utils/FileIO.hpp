#pragma once

#include <string>

namespace myutils
{
    /**
     * @brief Read all the file contents from a file and return the contents
     * within a std::string
     *
     * @param filepath path to the file
     * @return std::string containing the contents of the file
     */
    std::string readFileContents(std::string &filepath);
}
