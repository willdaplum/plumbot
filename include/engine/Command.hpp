#pragma once

#include "chess.hpp"

enum class UCICommand {
  UCI,
  DEBUG,
  ISREADY,
  SETOPTION,
  REGISTER,
  UCINEWGAME,
  POSITION,
  GO,
  STOP,
  PONDERHIT,
  QUIT
};

enum class DebugOption { OFF, ON };

enum class RegisterOption { LATER, NAME, CODE };

enum class PositionOption { MOVES };

enum class GoOption {
  SEARCHMOVES,
  PONDER,
  WTIME,
  BTIME,
  WINC,
  BINC,
  MOVESTOGO,
  DEPTH,
  NODES,
  MOVETIME,
  INFINITE
};

struct GoParameters {
  std::vector<chess::Move> search_moves;
  bool ponder = false;
  int wtime = 0;
  int btime = 0;
  int winc = 0;
  int binc = 0;
  int movestogo = 0;
  int depth = 0;
  int nodes = 0;
  int movetime = 0;
  bool infinite = false;
};