#pragma once

#include "builtins.hpp"
#include "types.hpp"

#include <string>

/**
 * @brief Command execution handler for shell builtins and external programs
 */
class Executer{
    Builtins builtins;

    /**
     * @brief Fork and execute external program
     * @param path Full path to executable
     * @param cmd Command with arguments
     * @return ExecResult::Continue
     */
    ExecResult exec_external(const std::string path, const Command& cmd);
public:
    /**
     * @brief Execute a command (builtin or external)
     * @param cmd Command to execute
     * @return ExecResult::Continue to continue REPL, ExecResult::Exit to terminate
     */
    ExecResult execute(const Command& cmd);
};