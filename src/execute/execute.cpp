#include <iostream>

#include "execute/execute.hpp"
#include "parse/parser.hpp"

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
    // check validity and execute
    auto it = builtin_funcs.find(cmd.name);
    if(it != builtin_funcs.end()){
        return it->second(cmd);
    }
    std::cout << cmd.name << ": command not found" << std::endl;
    return ExecResult::Continue;
}

ExecResult Executer::builtin_echo(const Command& cmd){
    for(auto it = cmd.args.begin(); it != cmd.args.end(); it++){
        if(it == cmd.args.begin()) continue;
        std::cout << (*it) << ' ';
    }
    std::cout << std::endl;

    return ExecResult::Continue;
}

ExecResult Executer::builtin_exit(const Command& cmd){
    return ExecResult::Exit;
}

ExecResult Executer::builtin_type(const Command& cmd){
    for(auto it = cmd.args.begin(); it != cmd.args.end(); it++){
        if(it == cmd.args.begin()) continue;

        if(builtin_funcs.find(*it) != builtin_funcs.end()){
            std::cout << (*it) << " is a shell builtin" << std::endl;
        }
        else{
            std::cout << (*it) << ": not found" << std::endl;
        }
    }

    return ExecResult::Continue;
}