#include "engine/Engine.hpp"

#include <iostream>

#include "engine/Command.hpp"

void Engine::send_id() {
  std::cout << "id name " << m_debug_mode << std::endl;
  std::cout << "id author " << m_id_author << std::endl;
};

void Engine::set_debug(DebugOption debug_mode) { m_debug_mode = static_cast<int>(debug_mode); };

void Engine::send_info(std::string info) { std::cout << "info " << info << std::endl; };