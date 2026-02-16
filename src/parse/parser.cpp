#include "parse/parser.hpp"

#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> Parser::split(const std::string& s){
    std::vector<std::string> out;
    std::string cur;
    bool squote = false;

    for(char ch : s){
        if(!squote && ch == ' '){
            if(!cur.empty()){
                out.push_back(cur);
                cur.clear();
            }
        }
        else if(ch == '\''){
            squote = !squote;
        }
        else {
            cur.push_back(ch);
        }
    }

    if(!cur.empty()) out.push_back(cur);
    return out;
}

Command Parser::parse(const std::string& line){
    Command cmd;
    cmd.args = split(line);
    if(!cmd.args.empty()) cmd.name = cmd.args.front();
    return cmd;
}