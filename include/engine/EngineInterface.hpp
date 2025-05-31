#pragma once

#include <string>
#include <unordered_map>

#include "Engine.hpp"
#include "Command.hpp"


class EngineInterface {
public:


 /**
 * @brief Interprets UCI commands and forwards to chess engine
 * @param uci_input the command line input to be parsed as UCI
 * @return a string of expected UCI output
 */
 std::string process_command(const std::string uci_input);

private:
 void uci_cmd();

 std::string debug_cmd();

 std::string isready_cmd();

 std::string setoption_cmd();

 std::string register_cmd();

 std::string ucinewgame_cmd();

 std::string position_cmd();

 std::string go_cmd();

 std::string stop_cmd();

 std::string ponderhit_cmd();

 std::string quit_cmd();

 Engine plumbot = Engine();

 const std::unordered_map<std::string, UCICommand> uci_commands {
    {"uci", UCICommand::UCI},
    {"debug", UCICommand::DEBUG},
    {"isready", UCICommand::ISREADY},
    {"setoption", UCICommand::SETOPTION},
    {"register", UCICommand::REGISTER},
    {"ucinewgame", UCICommand::UCINEWGAME},
    {"position", UCICommand::POSITION},
    {"go", UCICommand::GO},
    {"stop", UCICommand::STOP},
    {"ponderhit", UCICommand::PONDERHIT},
    {"quit", UCICommand::QUIT}
 };
};