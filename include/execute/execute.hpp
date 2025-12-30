#pragma once

#include <functional>
#include <string>
#include <unordered_map>

// forward initialisation
class Command;

enum class ExecResult {Continue, Exit};

class Executer{
    using BuiltinFunc = std::function<ExecResult(const Command& cmd)>;
    std::unordered_map<std::string, BuiltinFunc> builtin_funcs;

    ExecResult builtin_echo(const Command& cmd);
    ExecResult builtin_exit(const Command& cmd);
    ExecResult builtin_type(const Command& cmd);
public:
    Executer();
    ExecResult execute(const Command& cmd);
};