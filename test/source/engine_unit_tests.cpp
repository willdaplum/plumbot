#include <gtest/gtest.h>

#include <utility>
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
  for (std::string fen : fens) {
    engine.set_position(fen);
    EXPECT_EQ(fen, engine.get_position());
  }
  engine.set_position_new_game();
  EXPECT_EQ("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", engine.get_position());
};

TEST_F(EngineTest, PushMove) {
  std::vector<std::pair<std::string, std::string>> move_and_fen = {
      std::make_pair("e2e4", "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1"),
      std::make_pair("e7e5", "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2"),
      std::make_pair("f1c4", "rnbqkbnr/pppp1ppp/8/4p3/2B1P3/8/PPPP1PPP/RNBQK1NR b KQkq - 1 2"),
      std::make_pair("b8c6", "r1bqkbnr/pppp1ppp/2n5/4p3/2B1P3/8/PPPP1PPP/RNBQK1NR w KQkq - 2 3"),
      std::make_pair("c4f7", "r1bqkbnr/pppp1Bpp/2n5/4p3/4P3/8/PPPP1PPP/RNBQK1NR b KQkq - 0 3"),
      std::make_pair("e8f7", "r1bq1bnr/pppp1kpp/2n5/4p3/4P3/8/PPPP1PPP/RNBQK1NR w KQ - 0 4"),
      std::make_pair("f2f4", "r1bq1bnr/pppp1kpp/2n5/4p3/4PP2/8/PPPP2PP/RNBQK1NR b KQ - 0 4"),
      std::make_pair("c6b4", "r1bq1bnr/pppp1kpp/8/4p3/1n2PP2/8/PPPP2PP/RNBQK1NR w KQ - 1 5"),
      std::make_pair("f4e5", "r1bq1bnr/pppp1kpp/8/4P3/1n2P3/8/PPPP2PP/RNBQK1NR b KQ - 0 5"),
      std::make_pair("b4c6", "r1bq1bnr/pppp1kpp/2n5/4P3/4P3/8/PPPP2PP/RNBQK1NR w KQ - 1 6"),
      std::make_pair("e5e6", "r1bq1bnr/pppp1kpp/2n1P3/8/4P3/8/PPPP2PP/RNBQK1NR b KQ - 0 6"),
      std::make_pair("f7e8", "r1bqkbnr/pppp2pp/2n1P3/8/4P3/8/PPPP2PP/RNBQK1NR w KQ - 1 7"),
      std::make_pair("e6e7", "r1bqkbnr/ppppP1pp/2n5/8/4P3/8/PPPP2PP/RNBQK1NR b KQ - 0 7"),
      std::make_pair("g7g6", "r1bqkbnr/ppppP2p/2n3p1/8/4P3/8/PPPP2PP/RNBQK1NR w KQ - 0 8"),
      std::make_pair("e7d8q", "r1bQkbnr/pppp3p/2n3p1/8/4P3/8/PPPP2PP/RNBQK1NR b KQ - 0 8"),
  };
  engine.set_position_new_game();
  for (size_t i = 0; i < move_and_fen.size(); ++i) {
    engine.push_move_uci(move_and_fen[i].first);
    EXPECT_EQ(engine.get_position(), move_and_fen[i].second);
  }
};

TEST_F(EngineTest, FindMoveTakeQueenSimple) {
  engine.set_position("6k1/q7/8/8/8/4Q3/8/3K4 w - - 0 1");
  std::string engine_move = chess::uci::moveToUci(engine.find_move());
  EXPECT_EQ(engine_move, "e3a7");
};

TEST_F(EngineTest, SimpleCaptures) {
  std::vector<std::pair<std::string, std::string>> fen_and_move = {
      std::make_pair("6k1/8/8/8/8/8/3q4/3K4 w - - 0 1", "d1d2"),
      std::make_pair("6k1/1q6/8/8/8/5B2/8/3K4 w - - 0 1", "f3b7"),
      std::make_pair("6k1/8/2n5/8/3R4/8/8/3K4 b - - 0 1", "c6d4"),
      std::make_pair("6k1/P3r3/8/8/8/8/3P4/3K4 b - - 0 1", "e7a7"),
      std::make_pair("6k1/4q3/8/8/1N5Q/8/8/3K4 b - - 0 1", "e7h4"),
      std::make_pair("4k3/8/8/2b1r3/3P4/8/3K4/8 w - - 0 1", "d4e5"),
      std::make_pair("2r5/3P4/7k/8/8/8/3K4/8 w - - 0 1", "d7c8q"),
  };

  for (size_t i = 0; i < fen_and_move.size(); ++i) {
    engine.set_position(fen_and_move[i].first);
    std::string engine_move = chess::uci::moveToUci(engine.find_move());
    EXPECT_EQ(engine_move, fen_and_move[i].second);
  }
};

TEST_F(EngineTest, IntermediateCaptures) {
  std::vector<std::pair<std::string, std::string>> fen_and_move = {
      std::make_pair("rnbqkbnr/ppp2ppp/8/3pp3/8/P4N2/1PPPPPPP/RNBQKB1R w KQkq - 0 3", "f3e5"),
      std::make_pair("r1b1r1k1/pp1p1ppp/n4n2/1Nbp4/3B4/5P2/PPP1P1PP/R2K1BNR w - - 8 13", "d4c5")};
  for (size_t i = 0; i < fen_and_move.size(); ++i) {
    engine.set_position(fen_and_move[i].first);
    std::string engine_move = chess::uci::moveToUci(engine.find_move());
    EXPECT_EQ(engine_move, fen_and_move[i].second);
  }
}