#include "execute/execute.hpp"
#include "parse/parser.hpp" // including in cpp instead of hpp for Command

#include <iostream>
#include <filesystem>
#include <functional>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <unordered_map>

namespace fs = std::filesystem;

Executer::Executer(){
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

std::string Executer::get_exec_path(const std::string& cmd_name){
    const char* path = std::getenv("PATH");
    if(!path) { // no path variable
        return "";
    }

    // select the path separator with respect to the operating system
    #ifdef _WIN32
    const char pathsep = ';';
    #else
    const char pathsep = ':';
    #endif

    std::stringstream ss(path);
    std::string dir;

    // for each path directory, check existance and owner executability
    while(std::getline(ss, dir, pathsep)){
        fs::path full_path = fs::path(dir) / cmd_name;
        fs::perms perms = fs::status(full_path).permissions();
        if(fs::exists(full_path) && fs::perms::none != (perms & fs::perms::owner_exec)){
            return full_path;
        }
    }

    return "";
}

ExecResult Executer::execute(const Command& cmd){
    auto it = builtin_funcs.find(cmd.name);
    if(it != builtin_funcs.end()){
        return it->second(cmd);
    }
    else{
        std::string exec_path = get_exec_path(cmd.name);
        if(!exec_path.empty()){
            return exec_external(exec_path, cmd);
        }
    }
    std::cout << cmd.name << ": command not found" << std::endl;
    return ExecResult::Continue;
}

ExecResult Executer::exec_external(const std::string path, const Command& cmd){
    // create child process, and execute 'exec' command in it
    pid_t pid = fork();
    if(pid == 0){
        // convert vector<string> inside const Command cmd to vector<char*>
        // const Command is made non-const, then args are looped over
        // string::data() function returns null-terminated (const) char*
        std::vector<char*> args;
        for(std::string& arg: const_cast<Command&>(cmd).args){
            args.push_back(arg.data());
        }
        args.push_back(nullptr);
        
        // execute command at path with given args from cmd
        execv(path.data(), args.data());

        // in case of execv not executing (improper command), kill child
        perror("execv failed");
        exit(EXIT_FAILURE);
    }
    else if(pid < 0){
        perror("fork failed");
    }
    else {
        wait(NULL);
    }

    return ExecResult::Continue;
}

//----- BUILTINS -----
ExecResult Executer::exec_cd(const Command& cmd){
    fs::path cd_path(cmd.args[1]);
    if(fs::exists(cd_path)){
        fs::current_path(cd_path);
    }
    else{
        std::cout << "cd: " << cd_path.c_str();
        std::cout << ": No such file or directory" << std::endl;
    }
    return ExecResult::Continue;
}

ExecResult Executer::exec_echo(const Command& cmd){
    for(size_t i = 1; i < cmd.args.size(); i++){
        std::cout << (cmd.args[i]) << ' ';
    }
    std::cout << std::endl;

    return ExecResult::Continue;
}

ExecResult Executer::exec_exit(const Command& cmd){
    return ExecResult::Exit;
}

ExecResult Executer::exec_pwd(const Command& cmd){
    std::string cur_path = fs::current_path();
    std::cout << cur_path << std::endl;
    return ExecResult::Continue;
}

ExecResult Executer::exec_type(const Command& cmd){
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