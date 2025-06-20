#pragma once

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