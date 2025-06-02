#include <gtest/gtest.h>

#include <vector>

#include "engine/Engine.hpp"

class EngineTest : public ::testing::Test {
protected:
  Engine engine;  // expensive object

  void SetUp() override {}

  void TearDown() override {
    engine.set_debug(DebugOption::OFF);
    engine.set_position_new_game();
  }
};

TEST_F(EngineTest, SetDebugFlag) {
  engine.set_debug(DebugOption::ON);
  EXPECT_EQ(engine.get_debug(), true);
  engine.set_debug(DebugOption::OFF);
  EXPECT_EQ(engine.get_debug(), false);
  engine.set_debug(DebugOption::ON);
  EXPECT_EQ(engine.get_debug(), true);
};

TEST_F(EngineTest, SetPosition) {
  std::vector<std::string> fens
      = {"6k1/q7/8/8/8/4Q3/8/3K4 w - - 0 1",
         "rnbqkb1r/1pp1pp1p/p2p1np1/5P2/4P3/2NP4/PPP3PP/R1BQKBNR b KQkq - 0 5",
         "r3k2r/1bpqppbp/p1np1n2/1p3P2/1P1P1B2/2N2Q2/P1P3PP/R3KBNR w KQkq - 5 11",
         "r3k1r1/1bp1pp2/3p1b2/1p3q1p/1P1n2n1/2N5/PRP3PP/2BKQ1NR b q - 1 19",
         "r3k1r1/2p1pp2/3pqb2/1b6/1P5p/4B3/PRP1N2P/3KQ3 w q - 0 27",
         "r3k1r1/2pbpp2/3p1b2/8/1P5p/2N5/PRP4P/3Kq1B1 w q - 0 29",
         "2r1kr2/4b3/2Pp4/3bp3/8/P1R3BN/2PK3P/8 b - - 2 46",
         "4k3/1b2br2/3p4/8/1BP5/P7/5N1P/5K2 w - - 3 54",
         "4k3/1b2br2/3p4/8/1BP5/P7/5N1P/5K2 w - - 11 58",
         "8/p5kp/4n3/4r3/8/5bp1/8/5K1r w - - 2 59",
         "6k1/5p2/p5p1/1p2Q2p/4p3/P3P2P/2r1KPP1/2q2R2 w - - 3 33"};
  for(std::string fen : fens) {
    engine.set_position(fen);
    EXPECT_EQ(fen, engine.get_position());
  }
  engine.set_position_new_game();
  EXPECT_EQ("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", engine.get_position());
};