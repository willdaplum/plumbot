#include <gtest/gtest.h>

#include "engine/EngineInterface.hpp"

TEST(EngineWrapperTest, Position) {
  EngineInterface engine_interface = EngineInterface();
  engine_interface.process_command("position startpos moves a2a3 f7f6\n");
  engine_interface.process_command(
      "position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

TEST(EngineWrapperTest, TwoMoveRepetitionNotNull) {
  EngineInterface engine_interface = EngineInterface();
  std::ostringstream oss;
  engine_interface.process_command(
      "position startpos moves d2d4 b7b6 e2e4 b8c6 f1b5 a7a6 b5c6 d7c6 c1g5 h7h6 g5h4 g8f6 h4f6 "
      "e7f6 c2c3 a8a7 b1d2 d8e7 d1f3 c6c5 d4c5 b6c5 g1e2 f6f5 e4f5 e7d7 h1f1 a6a5 d2c4 f7f6 f3h5 "
      "e8e7 e2f4 d7f5 f4g6 e7d8 h5f5 c8f5 g6h8 f5e6 c4e3 d8e8 e1c1 a5a4 h8g6 e6a2 g6f8 e8f8 e3f5 "
      "a7a5 d1d8 f8f7 d8c8 a5a7 c8d8 a7a5 d8c8",
      oss);
  engine_interface.process_command("go", oss);
  EXPECT_TRUE(oss && oss.str() != "bestmove a1a1\n");
}