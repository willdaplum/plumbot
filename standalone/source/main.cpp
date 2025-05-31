#include <iostream>
#include <string>

#include "engine/EngineInterface.hpp"

auto main(int argc, char** argv) -> int {
  (void)argv[argc - 1];  // Not using cmd line args, so this quiets WUnused-variables

  EngineInterface engine = EngineInterface();

  std::string line;
  while (true) {
    std::getline(std::cin, line);

    if (line == "exit") break;

    engine.process_command(line);
  }
}
