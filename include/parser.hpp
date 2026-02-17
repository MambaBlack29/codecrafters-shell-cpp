#pragma once

#include <string>
#include <vector>

/**
 * @brief States for parsing quoted and escaped characters
 */
enum class ParseState{
    Normal,
    InQuote,
    InDoubleQuote,
    EscapedOut,
    EscapedInDoubleQuote
};

/**
 * @brief Parsed command with name and arguments
 */
class Command{
public:
    std::string name;
    std::vector<std::string> args;
};

/**
 * @brief Parser for shell command lines with quote and escape handling
 */
class Parser{
    /**
     * @brief Split command line into arguments respecting quotes and escapes
     * @param s Input command line string
     * @return Vector of arguments including command name, or empty on parse error
     */
    std::vector<std::string> split(const std::string& s);
public:
    /**
     * @brief Parse command line into Command structure
     * @param line Input command line
     * @return Command with name and arguments
     */
    Command parse(const std::string& line);
};