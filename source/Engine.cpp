#include "engine/Engine.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>

#include "engine/Command.hpp"

namespace {
  // excludes king & none, as they don't have a defined value
  constexpr chess::PieceType valued_piece_types[]
      = {chess::PieceType::PAWN, chess::PieceType::BISHOP, chess::PieceType::ROOK,
         chess::PieceType::KNIGHT, chess::PieceType::QUEEN};

  constexpr chess::Color colors[] = {chess::Color::BLACK, chess::Color::WHITE};
}  // namespace

PositionEvaluation::PositionEvaluation() {
  score = 0;
  moves_to_mate = std::numeric_limits<int>::max();
  move = chess::Move::NO_MOVE;
}

PositionEvaluation::PositionEvaluation(double score) : score(score) {
  moves_to_mate = std::numeric_limits<int>::max();
  move = chess::Move::NO_MOVE;
}

PositionEvaluation::PositionEvaluation(double score, int moves_to_mate)
    : score(score), moves_to_mate(moves_to_mate) {
  move = chess::Move::NO_MOVE;
}

PositionEvaluation::PositionEvaluation(double score, int moves_to_mate, chess::Move move)
    : score(score), moves_to_mate(moves_to_mate), move(move) {}

void Engine::send_id(std::ostream& os) {
  os << "id name " << m_id_name << std::endl;
  os << "id author " << m_id_author << std::endl;
}

void Engine::set_debug(DebugOption debug_mode) { m_debug_mode = static_cast<int>(debug_mode); }

bool Engine::get_debug() { return m_debug_mode; }

void Engine::send_info(std::string info, std::ostream& os) { os << "info " << info << std::endl; }

void Engine::send_uciok(std::ostream& os) { os << "uciok" << std::endl; }

void Engine::send_isready(std::ostream& os) { os << "readyok" << std::endl; }

void Engine::push_move_uci(std::string uci_move) {
  chess::Move move = chess::uci::uciToMove(m_board, uci_move);
  m_board.makeMove(move);
}

void Engine::set_position(std::string fen) { m_board.setFen(fen); }

void Engine::set_position_new_game() { set_position(chess::constants::STARTPOS); }

std::string Engine::get_position() { return m_board.getFen(); }

int Engine::get_piece_value(chess::PieceType piece_type) {
  return m_piece_values[static_cast<int>(piece_type)];
}

// NOTE: does not check for checkmate, will always be intmax
// NOTE: board with white up material will always be positive, black negative
PositionEvaluation Engine::static_evaluation() {
  int score = 0;
  for (chess::PieceType piece_type : valued_piece_types) {
    for (chess::Color color : colors) {
      int type_total_score
          = get_piece_value(piece_type) * m_board.pieces(piece_type, color).count();
      if (color == chess::Color::BLACK) {
        score -= type_total_score;
      } else {  // color == chess::Color::WHITE
        score += type_total_score;
      }
    }
  }
  return PositionEvaluation(score);
}

// TODO: turn alpha and beta into PositionEvaluation objects? I think?
PositionEvaluation Engine::minimax(int depth, double alpha, double beta, bool maximizing_player) {
  if (depth == 0 || m_stop_search) {
    return static_evaluation();
  }
  if (m_board.isRepetition()) {
    return PositionEvaluation(0);  // Draw
  }
  if (m_board.isHalfMoveDraw()) {
    if (m_board.getHalfMoveDrawType().first == chess::GameResultReason::CHECKMATE) {
      if (m_board.sideToMove() == chess::Color::WHITE) {
        return PositionEvaluation(-std::numeric_limits<double>::infinity(), 0);  // Black wins
      }
      return PositionEvaluation(std::numeric_limits<double>::infinity(), 0);  // White wins
    }
    return PositionEvaluation(0);  // Draw
  }

  chess::Movelist moves;
  chess::movegen::legalmoves(moves, m_board);

  if (moves.size() == 0) {
    if (m_board.inCheck()) {  // checkmate
      if (m_board.sideToMove() == chess::Color::WHITE) {
        return PositionEvaluation(-std::numeric_limits<double>::infinity(), 0);  // Black wins
      }
      return PositionEvaluation(std::numeric_limits<double>::infinity(), 0);  // White wins
    }
    return PositionEvaluation(0);  // Draw
  }

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(moves.begin(), moves.end(), g);

  PositionEvaluation eval = PositionEvaluation();
  if (maximizing_player) {
    eval.score = -std::numeric_limits<double>::infinity();
    for (auto it = moves.begin(); it != moves.end(); ++it) {
      m_board.makeMove(*it);
      std::string move_uci = chess::uci::moveToUci(*it);
      PositionEvaluation cur_eval = minimax(depth - 1, alpha, beta, false);
      cur_eval.move = *it;

      if (compare_moves(cur_eval, eval, maximizing_player)) {
        eval = cur_eval;
      }
      m_board.unmakeMove(*it);
      if (eval.score >= beta) {
        break;
      }
      alpha = std::max(alpha, eval.score);
    }
    if (eval.moves_to_mate != std::numeric_limits<int>::max()) {
      eval.moves_to_mate++;
    }
    return eval;
  } else {  // minimizing player
    eval.score = std::numeric_limits<double>::infinity();
    for (auto it = moves.begin(); it != moves.end(); ++it) {
      m_board.makeMove(*it);
      std::string move_uci = chess::uci::moveToUci(*it);
      PositionEvaluation cur_eval = minimax(depth - 1, alpha, beta, true);
      cur_eval.move = *it;

      if (compare_moves(cur_eval, eval, maximizing_player)) {
        eval = cur_eval;
      }
      m_board.unmakeMove(*it);
      if (eval.score <= alpha) {
        break;
      }
      beta = std::min(beta, eval.score);
    }
    if (eval.moves_to_mate != std::numeric_limits<int>::max()) {
      eval.moves_to_mate++;
    }
    return eval;
  }
}

chess::Move Engine::find_move(int depth) {
  m_stop_search = false;
  PositionEvaluation best_move = PositionEvaluation();
  bool maximizing_player = m_board.sideToMove() == chess::Color::WHITE;
  for (int ply = 1; ply <= depth; ++ply) {
    best_move = minimax(ply, -std::numeric_limits<double>::infinity(),
                        std::numeric_limits<double>::infinity(), maximizing_player);
    if (m_stop_search) {
      break;
    }
    m_best_move = best_move.move;
  }
  return m_best_move;
}

bool Engine::compare_moves(PositionEvaluation a, PositionEvaluation b, bool maximizing_player) {
  if (a.move == chess::Move::NO_MOVE && b.move != chess::Move::NO_MOVE) {
    return false;
  } else if (a.move != chess::Move::NO_MOVE && b.move == chess::Move::NO_MOVE) {
    return true;
  }

  if (maximizing_player) {
    if (a.moves_to_mate == b.moves_to_mate) {
      return a.score > b.score;
    } else {  // must be a checkmate
      if (a.score == b.score) {
        if (a.score < 0) {
          return a.moves_to_mate > b.moves_to_mate;
        } else {
          return a.moves_to_mate < b.moves_to_mate;
        }
      } else if (a.score == std::numeric_limits<double>::infinity()
                 || b.score == -std::numeric_limits<double>::infinity()) {
        return true;
      } else {
        return false;
      }
    }
  } else {  // minimizing_player
    if (a.moves_to_mate == b.moves_to_mate) {
      return a.score < b.score;
    } else {  // must be a checkmate
      if (a.score == b.score) {
        if (a.score < 0) {
          return a.moves_to_mate < b.moves_to_mate;
        } else {
          return a.moves_to_mate > b.moves_to_mate;
        }
      } else if (a.score == -std::numeric_limits<double>::infinity()
                 || b.score == std::numeric_limits<double>::infinity()) {
        return true;
      } else {
        return false;
      }
    }
  }
}

chess::Move Engine::get_best_move() { return m_best_move; }

void Engine::stop_search() { m_stop_search = true; }