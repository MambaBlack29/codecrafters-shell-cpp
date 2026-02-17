#pragma once

#include <functional>
#include <string>
#include <unordered_map>

// forward declaration
class Command;

/**
 * @brief Result of command execution
 */
enum class ExecResult {Continue, Exit};

/**
 * @brief Command execution handler for shell builtins and external programs
 */
class Executer{
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

    /**
     * @brief Fork and execute external program
     * @param path Full path to executable
     * @param cmd Command with arguments
     * @return ExecResult::Continue
     */
    ExecResult exec_external(const std::string path, const Command& cmd);

    /**
     * @brief Search for executable in PATH and filesystem
     * @param cmd_name Name or path of command
     * @param type If true, only search PATH directories
     * @return Absolute path to executable, or empty string if not found
     */
    std::string get_exec_path(const std::string& cmd_name, const bool type);
public:
    /**
     * @brief Initialize executer and register builtin commands
     */
    Executer();

    /**
     * @brief Execute a command (builtin or external)
     * @param cmd Command to execute
     * @return ExecResult::Continue to continue REPL, ExecResult::Exit to terminate
     */
    ExecResult execute(const Command& cmd);
};