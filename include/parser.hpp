#pragma once

#include <string>
#include <vector>

enum class ParseState{
    Normal,
    InQuote,
    InDoubleQuote,
    EscapedOut,
    EscapedInDoubleQuote
};

class Command{
public:
    std::string name;
    std::vector<std::string> args;
};

class Parser{
    /**
     * @brief Split string into vector of arguments
     * 
     * @param s String to be split with respect to ' '
     * @return List of arguments including command name
     */
    std::vector<std::string> split(const std::string& s);
public:
    // Public wrapper for split functionality
    Command parse(const std::string& line);
};