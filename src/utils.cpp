#include "utils.hpp"

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

std::string Utils::get_exec_path(const std::string& cmd_name, const bool type){
    // lambda to check if given file is executable
    auto executable = [](const fs::path& p) -> bool{
        if(fs::is_regular_file(p)){
            fs::perms perms = fs::status(p).permissions();
            return fs::perms::none != (perms & fs::perms::owner_exec);
        }
        return false;
    };

    // check in path if variable set
    const char* path = getenv("PATH");
    if(path) {
        // select the path separator with respect to the operating system
        #ifdef _WIN32
        const char pathsep = ';';
        #else
        const char pathsep = ':';
        #endif
    
        std::stringstream ss(path);
        std::string dir;
    
        // for each path directory, check existance and owner executability
        // file at full path must be regular file and not directory
        while(std::getline(ss, dir, pathsep)){
            fs::path full_path = (fs::path(dir) / cmd_name).lexically_normal();
            if(executable(full_path)) return full_path.string();
        }
    }

    // check outside path if not called by type builtin
    if(!type){
        fs::path full_path = fs::absolute(cmd_name).lexically_normal();
        if(executable(full_path)) return full_path.string();
    }

    // return empty path if not found anywhere
    return "";
}