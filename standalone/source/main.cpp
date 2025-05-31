#include <iostream>
#include <string>

auto main(int argc, char** argv) -> int {
  std::string line;
  while (true) {
      std::getline(std::cin, line);

      if (line == "exit") break;

      std::cout << "You entered: " << line << std::endl;
  }
}
