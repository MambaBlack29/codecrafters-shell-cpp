#pragma once

#include <string>
#include <vector>

/**
 * @brief Result of command execution
 * @enum NoBuiltin Command is not a builtin
 * @enum Continue Continue execution loop
 * @enum Exit Terminate the shell
 */
enum class ExecResult {
    NoBuiltin,
    Continue, 
    Exit
};

/**
 * @brief Parsed shell command with name and arguments
 */
class Command{
public:
    std::string name;        ///< Command name
    std::vector<std::string> args;  ///< Command arguments including name at index 0
};