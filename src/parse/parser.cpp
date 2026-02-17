#include "parse/parser.hpp"

#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> Parser::split(const std::string& s){
    std::vector<std::string> out;
    std::string cur;
    bool quote = false;
    bool dquote = false;
    bool back = false;

    for(char ch : s){
        // handle space
        if(!back && !dquote && !quote && ch == ' '){
            if(!cur.empty()){
                out.push_back(cur);
                cur.clear();
            }
        }
        // handle quotes
        else if(!back && !dquote && ch == '\''){
            quote = !quote;
        }
        else if(!back && !quote && ch == '\"'){
            dquote = !dquote;
        }
        // handle back slash outside quotes
        else if(!back && !dquote && !quote && ch == '\\'){
            back = !back;
        }
        else {
            cur.push_back(ch);
            if(back){
                back = !back;
            }
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