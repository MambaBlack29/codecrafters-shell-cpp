#include <iostream>
#include <string>

#include "cli/repl.hpp"
#include "parse/parser.hpp"

void Repl::run(){
    Parser parser;

    while(true){
        // prompt
        std::cout << "$ ";

        // read
        std::string line;
        std::getline(std::cin, line);
        Command cmd = parser.parse(line);

        // execute
        if(cmd.name.empty()) continue;
        else if(cmd.name == "exit") break;
        else if(cmd.name == "echo"){
            for(auto it = cmd.args.begin(); it != cmd.args.end(); it++){
                if(it == cmd.args.begin()) continue;
                std::cout << (*it) << ' ';
            }
            std::cout << std::endl;
        }
        else std::cout << cmd.name << ": command not found\n";
    }
}