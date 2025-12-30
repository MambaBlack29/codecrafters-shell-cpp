#include "parse/parser.hpp"

std::vector<std::string> Parser::split(const std::string& s){
    std::vector<std::string> out;
    std::string cur;

    for(char ch : s){
        if(ch == ' '){
            if(!cur.empty()){
                out.push_back(cur);
                cur.clear();
            }
        }
        else cur.push_back(ch);
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