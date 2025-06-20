#pragma once

#include <string>

#include "chess.hpp"
#include "engine/Command.hpp"

class PositionEvaluation {
public:
  PositionEvaluation();

  PositionEvaluation(double score);

  PositionEvaluation(double score, int moves_to_mate);

  PositionEvaluation(double score, int moves_to_mate, chess::Move move);

  double score;
  int moves_to_mate;
  chess::Move move;
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
   * @return fen of the board https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
   */
  std::string get_position();

  /**
   * @brief Make move on engine board
   * @param uci_move move in UCI format
   */
  void push_move_uci(std::string uci_move);

  void send_id(std::ostream& os = std::cout);

  void send_info(std::string info, std::ostream& os = std::cout);

  void send_uciok(std::ostream& os = std::cout);

  void send_isready(std::ostream& os = std::cout);

  /**
   * @brief Choose move on board using minimax with alphabeta
   * @param depth # of ply(s) to search w minimax, must be >= 1
   * @return Move on memeber board engine finds to be optimal
   */
  chess::Move find_move(int depth);

  /**
   * @brief Compare two PositionEvaluation objects, with a choice to maximize or minimize.
   * Evaluations ranked as follows:
   * 1) Prefer Move to null move
   * 2) Has mate > no mate > opponent has mate
   * 3) Prefer less moves to mate (or more if opponent mate inevitable)
   * 4) Score
   * @param a evaluation to be considered
   * @param b evaluation to be considered
   * @param maximizing_player true if maximizing the choices, false if minimizing
   * @return true if a is better, false if b is better
   */
  bool compare_moves(PositionEvaluation a, PositionEvaluation b, bool maximizing_player);

private:
  PositionEvaluation minimax(int depth, double alpha, double beta, bool maximizing_player);

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