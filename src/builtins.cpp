#include "builtins.hpp"
#include "utils.hpp"

#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

Builtins::Builtins(){
    builtin_funcs["cd"] = [this](const Command& cmd){
        return exec_cd(cmd);
    };
    builtin_funcs["echo"] = [this](const Command& cmd){
        return exec_echo(cmd);
    };
    builtin_funcs["exit"] = [this](const Command& cmd){
        return exec_exit(cmd);
    };
    builtin_funcs["pwd"] = [this](const Command& cmd){
        return exec_pwd(cmd);
    };
    builtin_funcs["type"] = [this](const Command& cmd){
        return exec_type(cmd);
    };
}

ExecResult Builtins::exec_builtin(const Command& cmd){
    auto it = builtin_funcs.find(cmd.name);
    if(it != builtin_funcs.end()){
        return it->second(cmd);
    }
    return ExecResult::NoBuiltin;
}

ExecResult Builtins::exec_cd(const Command& cmd){
    // set cd path
    fs::path cd_path;
    const char* home = getenv("HOME");
    if(cmd.args.size() == 1){
        cd_path /= home;
    }
    else if(cmd.args[1][0] == '~'){
        size_t i = (cmd.args[1].size() == 1)? 1 : 2;
        cd_path /= fs::path(home) / cmd.args[1].substr(i);
    }
    else{
        cd_path /= cmd.args[1];
    }

    // change directory if path exists and is directory
    if(!fs::exists(cd_path)){
        std::cerr << "cd: " << cd_path.string();
        std::cerr << ": No such file or directory" << std::endl;
    }
    else if(!fs::is_directory(cd_path)){
        std::cerr << "cd: not a directory: ";
        std::cerr << cd_path.string() << std::endl;
    }
    else{
        fs::current_path(cd_path);
    }
    return ExecResult::Continue;
}

ExecResult Builtins::exec_echo(const Command& cmd){
    for(size_t i = 1; i < cmd.args.size(); i++){
        std::cout << (cmd.args[i]);
        if(i < cmd.args.size() - 1){
            std::cout << ' ';
        }
    }
    std::cout << std::endl;

    return ExecResult::Continue;
}

ExecResult Builtins::exec_exit(const Command& cmd){
    return ExecResult::Exit;
}

ExecResult Builtins::exec_pwd(const Command& cmd){
    std::string cur_path = fs::current_path();
    std::cout << cur_path << std::endl;
    return ExecResult::Continue;
}

ExecResult Builtins::exec_type(const Command& cmd){
    // for all arguments determine type iteratively
    for(size_t i = 1; i < cmd.args.size(); i++){
        const std::string target = cmd.args[i];

        // search for command in builtin and PATH in order
        if(builtin_funcs.find(target) != builtin_funcs.end()){
            std::cout << target << " is a shell builtin" << std::endl;
        }
        else{
            std::string exec_path = Utils::get_exec_path(target, true);
            if(!exec_path.empty()){
                std::cout << target << " is " << exec_path << std::endl;
            }
            else{
                std::cerr << (target) << ": not found" << std::endl;
            }
        }
    }

    return ExecResult::Continue;
}