#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Command.hpp"
#include "Engine.hpp"

class EngineInterface {
public:
  /**
   * @brief Interprets UCI commands and forwards to chess engine
   * @param uci_input the command line input to be parsed as UCI
   * @param os stream for command output, defaults to std::cout (use stringstream for testing)
   * @return a string of expected UCI output
   */
  void process_command(const std::string uci_input, std::ostream& os = std::cout);

private:
  std::vector<std::string> vectorize_options(const std::string uci_options);

  std::vector<std::string> vectorize_options_with_fen(const std::string uci_options);

  void uci_cmd(std::ostream& os = std::cout);

  void debug_cmd(const std::vector<std::string>& uci_options);

  void isready_cmd(std::ostream& os = std::cout);

  std::string setoption_cmd();

  std::string register_cmd();

  std::string ucinewgame_cmd();

  void position_cmd(const std::vector<std::string>& uci_options);

  void go_cmd(const std::vector<std::string>& uci_options, std::ostream& os = std::cout);

  void stop_cmd();

  std::string ponderhit_cmd();

  std::string quit_cmd();

  Engine plumbot = Engine();

  const std::unordered_map<std::string, UCICommand> uci_commands{
      {"uci", UCICommand::UCI},           {"debug", UCICommand::DEBUG},
      {"isready", UCICommand::ISREADY},   {"setoption", UCICommand::SETOPTION},
      {"register", UCICommand::REGISTER}, {"ucinewgame", UCICommand::UCINEWGAME},
      {"position", UCICommand::POSITION}, {"go", UCICommand::GO},
      {"stop", UCICommand::STOP},         {"ponderhit", UCICommand::PONDERHIT},
      {"quit", UCICommand::QUIT}};
};