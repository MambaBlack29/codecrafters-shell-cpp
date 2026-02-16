#include "execute/execute.hpp"
#include "parse/parser.hpp" // including in cpp instead of hpp for Command

#include <iostream>
#include <filesystem>
#include <functional>
#include <string>
#include <unordered_map>

Executer::Executer(){
    builtin_funcs["echo"] = [this](const Command& cmd){
        return builtin_echo(cmd);
    };
    builtin_funcs["exit"] = [this](const Command& cmd){
        return builtin_exit(cmd);
    };
    builtin_funcs["type"] = [this](const Command& cmd){
        return builtin_type(cmd);
    };
}

ExecResult Executer::execute(const Command& cmd){
    auto it = builtin_funcs.find(cmd.name);
    if(it != builtin_funcs.end()){
        return it->second(cmd);
    }
    std::cout << cmd.name << ": command not found" << std::endl;
    return ExecResult::Continue;
}

std::string Executer::get_exec_path(const std::string& cmd){
    const char* path = std::getenv("PATH");
    if(!path) { // no path variable
        return "";
    }

    namespace fs = std::filesystem;
    std::stringstream ss(path);
    std::string dir;
    while(std::getline(ss, dir, ':')){
        fs::path full_path = fs::path(dir) / cmd;
        fs::perms perms = fs::status(full_path).permissions();
        if(fs::exists(full_path) && fs::perms::none != (perms & fs::perms::owner_exec)){
            return full_path;
        }
    }

    return "";
}

ExecResult Executer::builtin_echo(const Command& cmd){
    for(size_t i = 1; i < cmd.args.size(); i++){
        std::cout << (cmd.args[i]) << ' ';
    }
    std::cout << std::endl;

    return ExecResult::Continue;
}

ExecResult Executer::builtin_exit(const Command& cmd){
    return ExecResult::Exit;
}

ExecResult Executer::builtin_type(const Command& cmd){
    for(size_t i = 1; i < cmd.args.size(); i++){
        const std::string target = cmd.args[i];

        if(builtin_funcs.find(target) != builtin_funcs.end()){
            std::cout << target << " is a shell builtin" << std::endl;
        }
        else{
            std::string exec_path = get_exec_path(target);
            if(!exec_path.empty()){
                std::cout << target << " is " << exec_path << std::endl;
            }
            else{
                std::cout << (target) << ": not found" << std::endl;
            }
        }
    }

    return ExecResult::Continue;
}