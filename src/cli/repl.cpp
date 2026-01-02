#include <iostream>
#include <string>

#include "cli/repl.hpp"
#include "execute/execute.hpp"
#include "parse/parser.hpp"

void Repl::run(){
    Parser parser;
    Executer executer;

    while(true){
        // prompt
        std::cout << "$ ";

        // read
        std::string line;
        if(!std::getline(std::cin, line)) break;
        Command cmd = parser.parse(line);

        // execute = eval and print
        ExecResult res = executer.execute(cmd);
        if(res == ExecResult::Exit) break;
    }
}