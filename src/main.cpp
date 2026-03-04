#include <iostream>
#include <string>

#include "execute.hpp"
#include "parser.hpp"

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // when executer object created, builtins constructor called
    Parser parser;
    Executer executer;

    // Read-Eval-Print Loop for the shell
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

    return 0;
}
