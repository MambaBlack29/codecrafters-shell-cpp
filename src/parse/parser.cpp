#include "parse/parser.hpp"

#include <string>
#include <iostream>
#include <vector>

std::vector<std::string> Parser::split(const std::string& s){
    std::vector<std::string> out;
    std::string cur;
    ParseState state = ParseState::Normal;

    for(char ch : s){
        switch (state){
        case ParseState::Normal:
            if(isspace(ch)){
                if(!cur.empty()){
                    out.push_back(cur);
                    cur.clear();
                }
            }
            else if(ch == '\'') state = ParseState::InQuote;
            else if(ch == '\"') state = ParseState::InDoubleQuote;
            else if(ch == '\\') state = ParseState::EscapedOut;
            else cur.push_back(ch);
            break;
        
        case ParseState::InQuote:
            if(ch == '\'') state = ParseState::Normal;
            else cur.push_back(ch);
            break;
        
        case ParseState::InDoubleQuote:
            if(ch == '\"') state = ParseState::Normal;
            else if(ch == '\\') state = ParseState::EscapedInDoubleQuote;
            else cur.push_back(ch);
            break;
        
        case ParseState::EscapedOut:
            cur.push_back(ch);
            state = ParseState::Normal;
            break;

        case ParseState::EscapedInDoubleQuote:
            if(ch == '\"' || ch == '\\') cur.push_back(ch);
            else cur.append({'\\', ch});
            state = ParseState::InDoubleQuote;
            break;

        default:
            break;
        }
    }

    if(state != ParseState::Normal){
        std::cerr << "Incomplete command input" << std::endl;
        return std::vector<std::string>();
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