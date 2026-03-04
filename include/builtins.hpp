#pragma once

#include "types.hpp"

#include <functional>
#include <string>
#include <unordered_map>

/**
 * @brief Manager for shell builtin commands
 */
class Builtins{
    using BuiltinFunc = std::function<ExecResult(const Command& cmd)>;

    /**
     * @brief Map to find and call builtin functions
     */
    std::unordered_map<std::string, BuiltinFunc> builtin_funcs;

    // Builtin command implementations

    /**
     * @brief Change the current working directory
     * @param cmd Command with target directory as first argument
     * @return ExecResult::Continue
     */
    ExecResult exec_cd(const Command& cmd);

    /**
     * @brief Print arguments to stdout
     * @param cmd Command with arguments to print
     * @return ExecResult::Continue
     */
    ExecResult exec_echo(const Command& cmd);

    /**
     * @brief Exit the shell
     * @param cmd Command (arguments ignored)
     * @return ExecResult::Exit
     */
    ExecResult exec_exit(const Command& cmd);

    /**
     * @brief Print the current working directory
     * @param cmd Command (arguments ignored)
     * @return ExecResult::Continue
     */
    ExecResult exec_pwd(const Command& cmd);

    /**
     * @brief Display information about command type
     * @param cmd Command with target commands as arguments
     * @return ExecResult::Continue
     */
    ExecResult exec_type(const Command& cmd);

public:
    /**
     * @brief Initialize builtins and register all builtin commands
     */
    Builtins();

    /**
     * @brief Execute a builtin command if registered
     * @param cmd Command to execute
     * @return ExecResult::NoBuiltin if command is not a builtin, otherwise execution result
     */
    ExecResult exec_builtin(const Command& cmd);
};