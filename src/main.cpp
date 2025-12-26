#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  while(1){
    // loop
    std::cout << "$ ";

    // read
    std::string command;
    std::getline(std::cin, command);

    // eval for "exit" command
    if(command == "exit") break;

    // eval = error, print
    std::cout << command << ": command not found\n";
  }
}
