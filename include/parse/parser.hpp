#pragma once

#include <vector>
#include <string>

struct Command{
    std::string name;
    std::vector<std::string> args;
};

class Parser{
    static std::vector<std::string> split(const std::string& s);
public:
    Command parse(const std::string& line) const;
};