#include "engine/EngineInterface.hpp"

#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

#include "engine/Command.hpp"

std::vector<std::string> EngineInterface::vectorize_options(const std::string uci_options) {
  std::stringstream ss(uci_options);
  std::istream_iterator<std::string> begin(ss);
  std::istream_iterator<std::string> end;
  std::vector<std::string> v_options(begin, end);
  return v_options;
}

std::vector<std::string> EngineInterface::vectorize_options_with_fen(
    const std::string uci_options) {
  std::vector<std::string> v_options = vectorize_options(uci_options);
  if (v_options.at(0) != "startpos") {
    for (size_t i = 2; i < 7; ++i) {  // re-form fen as 1 indexed option
      v_options.at(1) += " " + v_options.at(i);
    }
    v_options.erase(v_options.begin() + 2, v_options.begin() + 7);
  }
  return v_options;
}

void EngineInterface::process_command(const std::string uci_input, std::ostream& os) {
  const std::string delimiter = " ";
  std::string uci_command_text = uci_input.substr(0, uci_input.find(delimiter));
  std::string uci_options = uci_input.substr(uci_input.find(delimiter) + 1);

  auto uci_command_it = uci_commands.find(uci_command_text);
  if (uci_command_it == uci_commands.end()) {
    os << "HELP THIS IS AN ERROR:";
  }
  UCICommand uci_command = uci_command_it->second;

  switch (uci_command) {
    default:
      os << "unrecognized command\n";
      break;
    case UCICommand::DEBUG:
      debug_cmd(vectorize_options(uci_options));
      break;
    case UCICommand::GO:
    {
      std::thread go_thread([&]() { go_cmd(vectorize_options(uci_options), os); });
      go_thread.detach();
      break;
    }
    case UCICommand::ISREADY:
      isready_cmd(os);
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
      stop_cmd();
      break;
    case UCICommand::UCI:
      uci_cmd(os);
      break;
    case UCICommand::UCINEWGAME:
      break;
  }
}

void EngineInterface::uci_cmd(std::ostream& os) {
  plumbot.send_id(os);
  plumbot.send_uciok(os);
}

void EngineInterface::debug_cmd(const std::vector<std::string>& uci_options) {
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
}

void EngineInterface::isready_cmd(std::ostream& os) { plumbot.send_isready(os); }

void EngineInterface::position_cmd(const std::vector<std::string>& uci_options) {
  if (uci_options.size() == 0) {
    // TODO: error
  }
  if (uci_options.at(0) == "startpos") {
    plumbot.set_position_new_game();
  } else {
    plumbot.set_position(uci_options[1]);
  }
  for (size_t i = 2; i < uci_options.size(); ++i) {  // moves start after fen
    plumbot.push_move_uci(uci_options[i]);
  }
}

// TODO: set go options as member variables?
GoParameters EngineInterface::parse_go_options(const std::vector<std::string>& uci_options) {
  std::vector<chess::Move> search_moves;
  GoParameters go_params;

  for (auto option_it = uci_options.begin(); option_it != uci_options.end(); ++option_it) {
    if (go_options.find(*option_it) != go_options.end()) {
      GoOption go_option = go_options.at(*option_it);
      switch (go_option) {
        case GoOption::SEARCHMOVES:
          for (auto searchmove_it = option_it + 1;
               searchmove_it != uci_options.end()
               && go_options.find(*searchmove_it) == go_options.end();
               ++searchmove_it) {
            search_moves.push_back(chess::uci::uciToMove(plumbot.get_board(), *searchmove_it));
          }
          break;
        case GoOption::PONDER:
          go_params.ponder = true;
          break;
        case GoOption::WTIME:
          go_params.wtime = std::stoi(*(++option_it));
          break;
        case GoOption::BTIME:
          go_params.btime = std::stoi(*(++option_it));
          break;
        case GoOption::WINC:
          go_params.winc = std::stoi(*(++option_it));
          break;
        case GoOption::BINC:
          go_params.binc = std::stoi(*(++option_it));
          break;
        case GoOption::MOVESTOGO:
          go_params.movestogo = std::stoi(*(++option_it));
          break;
        case GoOption::DEPTH:
          go_params.depth = std::stoi(*(++option_it));
          break;
        case GoOption::NODES:
          go_params.nodes = std::stoi(*(++option_it));
          break;
        case GoOption::MOVETIME:
          go_params.movetime = std::stoi(*(++option_it));
          break;
        case GoOption::INFINITE:
          go_params.infinite = true;
          break;
      }
    }
  }

  return go_params;
}

void EngineInterface::go_cmd(const std::vector<std::string>& uci_options, std::ostream& os) {
  GoParameters go_params = parse_go_options(uci_options);

  plumbot.find_move(go_params.depth);
  os << "bestmove " << chess::uci::moveToUci(plumbot.get_best_move()) << std::endl;
}

void EngineInterface::stop_cmd() { plumbot.stop_search(); }