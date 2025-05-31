#pragma once

#include <string>

#include "engine/Command.hpp"

class Engine {
public:
  void set_debug(DebugOption debug_mode);

  void set_position(std::string fen);

  void set_position_new_game();

  void send_id();

  void send_info(std::string info);

private:
  void minimax();

  void static_evaluate();

  const std::string m_id_name = "plumbot";
  const std::string m_id_author = "will cooley";
  bool m_debug_mode = false;
};