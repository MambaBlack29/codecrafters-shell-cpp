#pragma once

#include <string>
#include <vector>

class Command{
public:
    std::string name;
    std::vector<std::string> args;
};

class Parser{
    std::vector<std::string> split(const std::string& s);
public:
    Command parse(const std::string& line);
};