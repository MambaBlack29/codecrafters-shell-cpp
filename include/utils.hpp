#pragma once

#include <string>

namespace Utils{
    /**
     * @brief Search for executable in PATH and filesystem
     * @param cmd_name Name or path of command
     * @param type If true, only search PATH directories
     * @return Absolute path to executable, or empty string if not found
     */
    std::string get_exec_path(const std::string& cmd_name, const bool type);
}
