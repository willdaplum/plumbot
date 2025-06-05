#include "engine/EngineInterface.hpp"

#include <iostream>
#include <sstream>
#include <vector>

#include "engine/Command.hpp"

std::vector<std::string> EngineInterface::vectorize_options(const std::string uci_options) {
  std::stringstream ss(uci_options);
  std::istream_iterator<std::string> begin(ss);
  std::istream_iterator<std::string> end;
  std::vector<std::string> v_options(begin, end);
  return v_options;
};

std::vector<std::string> EngineInterface::vectorize_options_with_fen(
    const std::string uci_options) {
  std::vector<std::string> v_options = vectorize_options(uci_options);
  if (v_options.at(0) != "startpos") {
    for (size_t i = 1; i < 6; ++i) {  // re-form fen as 0 index option
      v_options.at(0) += " " + v_options.at(i);
    }
    v_options.erase(v_options.begin() + 1, v_options.begin() + 6);
  }
  return v_options;
};

void EngineInterface::process_command(const std::string uci_input) {
  const std::string delimiter = " ";
  std::string uci_command_text = uci_input.substr(0, uci_input.find(delimiter));
  std::string uci_options = uci_input.substr(uci_input.find(delimiter) + 1);

  auto uci_command_it = uci_commands.find(uci_command_text);
  if (uci_command_it == uci_commands.end()) {
    // TODO: this is an error
  }
  UCICommand uci_command = uci_command_it->second;

  switch (uci_command) {
    default:
      std::cout << "unrecognized command\n";
      break;
    case UCICommand::DEBUG:
      debug_cmd(vectorize_options(uci_options));
      break;
    case UCICommand::GO:
      go_cmd();
      break;
    case UCICommand::ISREADY:
      isready_cmd();
      break;
    case UCICommand::PONDERHIT:
      break;
    case UCICommand::POSITION:
      position_cmd(vectorize_options_with_fen(uci_options));
      break;
    case UCICommand::QUIT:
      break;
    case UCICommand::REGISTER:
      break;
    case UCICommand::SETOPTION:
      break;
    case UCICommand::STOP:
      break;
    case UCICommand::UCI:
      uci_cmd();
      break;
    case UCICommand::UCINEWGAME:
      break;
  }
};

void EngineInterface::uci_cmd() { 
  plumbot.send_id(); 
  plumbot.send_uciok();
};

void EngineInterface::debug_cmd(const std::vector<std::string> &uci_options) {
  if (uci_options.size() != 1) {
    // TODO: error
  }
  if (uci_options.at(0) == "on") {
    plumbot.set_debug(DebugOption::ON);
  } else if (uci_options.at(0) == "off") {
    plumbot.set_debug(DebugOption::OFF);
  } else {
    // TODO: error
  }
};

void EngineInterface::isready_cmd() {
  plumbot.send_isready();
};

void EngineInterface::position_cmd(const std::vector<std::string> &uci_options) {
  if (uci_options.size() == 0) {
    // TODO: error
  }
  if (uci_options.at(0) == "startpos") {
    plumbot.set_position_new_game();
  } else {
    plumbot.set_position(uci_options[0]);
  }
  for (size_t i = 2; i < uci_options.size(); ++i) {  // moves start after fen
    plumbot.push_move_uci(uci_options[i]);
  }
};

void EngineInterface::go_cmd() {
  chess::Move move = plumbot.find_move();
  std::cout << "bestmove " << chess::uci::moveToUci(move) << std::endl;
}