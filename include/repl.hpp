#pragma once

/**
 * @brief Read-Eval-Print Loop for the shell
 */
class Repl{
public:
    /**
     * @brief Start the interactive shell loop
     * 
     * Prompts for input, parses commands, and executes them until exit
     */
    void run();
};