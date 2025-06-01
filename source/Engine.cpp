#include "engine/Engine.hpp"

#include <iostream>
#include <limits>

#include "engine/Command.hpp"

PositionEvaluation::PositionEvaluation() {
  score = 0;
  moves_to_mate = std::numeric_limits<int>::infinity();
};

PositionEvaluation::PositionEvaluation(int score) : score(score) {
  moves_to_mate = std::numeric_limits<int>::infinity();
};

PositionEvaluation::PositionEvaluation(int score, int moves_to_mate)
    : score(score), moves_to_mate(moves_to_mate) {};

void Engine::send_id() {
  std::cout << "id name " << m_debug_mode << std::endl;
  std::cout << "id author " << m_id_author << std::endl;
};

void Engine::set_debug(DebugOption debug_mode) { m_debug_mode = static_cast<int>(debug_mode); };

void Engine::send_info(std::string info) { std::cout << "info " << info << std::endl; };

void Engine::push_move_uci(std::string uci_move) {
  chess::Move move = chess::uci::uciToMove(m_board, uci_move);
  m_board.makeMove(move);
};

void Engine::pop_move_uci(std::string uci_move) {
  chess::Move move = chess::uci::uciToMove(m_board, uci_move);
  m_board.unmakeMove(move);
};

void Engine::set_position(std::string fen) { m_board.setFen(fen); };

void Engine::set_position_new_game() { set_position(chess::constants::STARTPOS); };

PositionEvaluation Engine::static_evaluation() {
    return PositionEvaluation();
};

// TODO: turn alpha and beta into PositionEvaluation objects? I think?
PositionEvaluation Engine::minimax(int depth, int alpha, int beta, bool maximizing_player) {
  if (depth == 0 /* or node leaf?? */) {
    return static_evaluation();
  }

  chess::Movelist moves;
  chess::movegen::legalmoves(moves, m_board);
  PositionEvaluation eval = PositionEvaluation();
  if (maximizing_player) {
    eval.score = -std::numeric_limits<int>::infinity();
    for (auto it = moves.begin(); moves.begin() != moves.end(); ++it) {
      m_board.makeMove(*it);
      eval = std::max(eval, minimax(depth - 1, alpha, beta, false), EvaluationCmp());
      m_board.unmakeMove(*it);
      if (eval.score >= beta) {
        break;
      }
      alpha = std::max(alpha, eval.score);
    }
    return eval;
  } else {  // minimizing player
    eval.score = -std::numeric_limits<int>::infinity();
    for (auto it = moves.begin(); moves.begin() != moves.end(); ++it) {
      m_board.makeMove(*it);
      eval = std::min(eval, minimax(depth - 1, alpha, beta, true), EvaluationCmp());
      m_board.unmakeMove(*it);
      if (eval.score <= alpha) {
        break;
      }
      beta = std::min(beta, eval.score);
    }
    return eval;
  }
};