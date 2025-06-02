#pragma once

#include <string>

#include "chess.hpp"
#include "engine/Command.hpp"

class PositionEvaluation {
public:
  PositionEvaluation();

  PositionEvaluation(int score);

  PositionEvaluation(int score, int moves_to_mate);

  PositionEvaluation(int score, int moves_to_mate, chess::Move move);

  int score;
  int moves_to_mate;
  chess::Move move;
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

/**
   * @brief Interprets UCI commands and forwards to chess engine
   * @param debug_mode Flag to be set (ON -> true)
   */
  void set_debug(DebugOption debug_mode);

  /**
   * @brief Get boolean of debug flag (true -> ON)
   * @return true if debug output is on
   */
  bool get_debug();

  /**
   * @brief Sets board to given fen position
   * @param fen valid fen string https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
   */
  void set_position(std::string fen);

  /**
   * @brief Sets board fen to standard starting position
   * "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
   */
  void set_position_new_game();

  /**
   * @brief Interprets UCI commands and forwards to chess engine
   * @param uci_input the command line input to be parsed as UCI
   * @return fen of the board https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
   */
  std::string get_position();

  void push_move_uci(std::string uci_move);

  void pop_move_uci(std::string uci_move);

  void send_id();

  void send_info(std::string info);

  chess::Move find_move();

private:
  PositionEvaluation minimax(int depth, int alpha, int beta, bool maximizing_player);

  PositionEvaluation static_evaluation();

  int get_piece_value(chess::PieceType piece_type);

  const std::string m_id_name = "plumbot";
  const std::string m_id_author = "will cooley";
  bool m_debug_mode = false;
  chess::Board m_board = chess::Board(chess::constants::STARTPOS);
  std::unordered_map<int, int> m_piece_values = {{static_cast<int>(chess::PieceType::PAWN), 1},
                                                 {static_cast<int>(chess::PieceType::BISHOP), 3},
                                                 {static_cast<int>(chess::PieceType::KNIGHT), 3},
                                                 {static_cast<int>(chess::PieceType::ROOK), 5},
                                                 {static_cast<int>(chess::PieceType::QUEEN), 9},
                                                 {static_cast<int>(chess::PieceType::NONE), 0},
                                                 {static_cast<int>(chess::PieceType::KING), 0}};
};