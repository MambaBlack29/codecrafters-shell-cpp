#pragma once

#include <functional>
#include <string>
#include <unordered_map>

// forward initialisation
class Command;

enum class ExecResult {Continue, Exit};

class Executer{
    using BuiltinFunc = std::function<ExecResult(const Command& cmd)>;

    /**
     * @brief Map to find and call builtin functions
     */
    std::unordered_map<std::string, BuiltinFunc> builtin_funcs;

    // Implementations of all the builtin functions

    ExecResult builtin_echo(const Command& cmd);
    ExecResult builtin_exit(const Command& cmd);
    ExecResult builtin_type(const Command& cmd);
public:
    /**
     * @brief configures the 'builtin_funcs' map
     * 
     * Sets the 'builtin_funcs' for each funcion via a lambda expression
     */
    Executer();

    /**
     * @brief Wrapper for execution of functions
     * 
     * Executes builtin functino if 'cmd' found in 'builtin_funcs'
     * Prints error statement if not found
     * 
     * @param cmd Command type present in 'parser.hpp'
     * @return ExecResult: Continue or Exit
     */
    ExecResult execute(const Command& cmd);
};