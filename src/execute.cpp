#include "builtins.hpp"
#include "execute.hpp"
#include "utils.hpp"

#include <iostream>
#include <filesystem>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <unordered_map>

namespace fs = std::filesystem;

ExecResult Executer::execute(const Command& cmd){
    // if empty command or parsing error continue directly
    if(cmd.name.empty()) return ExecResult::Continue;

    // search for command in builtin, PATH and directly in order
    ExecResult builtin_response = builtins.exec_builtin(cmd);
    if(builtin_response != ExecResult::NoBuiltin){
        return builtin_response;
    }
    else{
        std::string exec_path = Utils::get_exec_path(cmd.name, false);
        if(!exec_path.empty()){
            return exec_external(exec_path, cmd);
        }
    }
    std::cerr << cmd.name << ": command not found" << std::endl;
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
        std::cerr << "execv failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    else if(pid < 0){
        std::cerr << "fork failed"  << std::endl;
    }
    else {
        wait(NULL);
    }

    return ExecResult::Continue;
}