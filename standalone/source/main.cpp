#include <iostream>
#include <fstream>
#include <string>

#include "engine/EngineInterface.hpp"

auto main(int argc, char** argv) -> int {
  (void)argv[argc - 1];  // Not using cmd line args, so this quiets WUnused-variables

  EngineInterface engine = EngineInterface();

  std::string logfile_name = "/Users/williamcooley/code/plumbot/logs/log.txt";

  std::string line;
  while (true) {
    std::getline(std::cin, line);
    std::ofstream myfile;
    myfile.open (logfile_name, std::ios::app);
    myfile << line << std::endl;
    myfile.close();

    if (line == "exit") break;
    if (line == "quit") break;

    engine.process_command(line);
  }
}
