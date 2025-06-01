#pragma once

#include <string>

#include "chess.hpp"
#include "engine/Command.hpp"

class PositionEvaluation {
public:
  PositionEvaluation();

  PositionEvaluation(int score);

  PositionEvaluation(int score, int moves_to_mate);

  int score;
  int moves_to_mate;
};

struct EvaluationCmp {
  bool operator()(PositionEvaluation a, PositionEvaluation b) const {
    if (a.score == b.score) {
      return a.moves_to_mate < b.moves_to_mate;
    }
    return a.score < b.score;
  }
};

class Engine {
public:
  void set_debug(DebugOption debug_mode);

  void set_position(std::string fen);

  void set_position_new_game();

  void push_move_uci(std::string uci_move);

  void pop_move_uci(std::string uci_move);

  void send_id();

  void send_info(std::string info);

private:
  PositionEvaluation minimax(int depth, int alpha, int beta, bool maximizing_player);

  PositionEvaluation static_evaluation();

  const std::string m_id_name = "plumbot";
  const std::string m_id_author = "will cooley";
  bool m_debug_mode = false;
  chess::Board m_board = chess::Board(chess::constants::STARTPOS);
};