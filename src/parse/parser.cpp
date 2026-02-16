#include "parse/parser.hpp"

#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> Parser::split(const std::string& s){
    std::vector<std::string> out;
    std::string cur;
    bool quote = false;
    bool dquote = false;

    for(char ch : s){
        // handle space
        if(!dquote && !quote && ch == ' '){
            if(!cur.empty()){
                out.push_back(cur);
                cur.clear();
            }
        }
        //handle quotes
        else if(!dquote && ch == '\''){
            quote = !quote;
        }
        else if(!quote && ch == '\"'){
            dquote = !dquote;
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