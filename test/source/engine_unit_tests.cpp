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
}

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
}

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
}

TEST_F(EngineTest, MoveComparison) {
  chess::Move m
      = chess::Move::make<chess::Move::NORMAL>(chess::Square::SQ_E2, chess::Square::SQ_E4);
  PositionEvaluation null_move = PositionEvaluation();
  PositionEvaluation max_mate_in_two
      = PositionEvaluation(std::numeric_limits<double>::infinity(), 2, m);
  PositionEvaluation max_mate_in_three
      = PositionEvaluation(std::numeric_limits<double>::infinity(), 3, m);
  PositionEvaluation min_mate_in_two
      = PositionEvaluation(-std::numeric_limits<double>::infinity(), 2, m);
  PositionEvaluation min_mate_in_three
      = PositionEvaluation(-std::numeric_limits<double>::infinity(), 3, m);
  PositionEvaluation max_score_two = PositionEvaluation(2, std::numeric_limits<int>::max(), m);
  PositionEvaluation max_score_three = PositionEvaluation(3, std::numeric_limits<int>::max(), m);
  PositionEvaluation min_score_two = PositionEvaluation(-2, std::numeric_limits<int>::max(), m);
  PositionEvaluation min_score_three = PositionEvaluation(-3, std::numeric_limits<int>::max(), m);

  // Check prefer move to no move
  EXPECT_TRUE(engine.compare_moves(max_mate_in_three, null_move, true));
  EXPECT_TRUE(engine.compare_moves(min_score_three, null_move, false));
  EXPECT_FALSE(engine.compare_moves(null_move, max_mate_in_three, false));
  EXPECT_FALSE(engine.compare_moves(null_move, min_score_three, true));

  // Check mate > no mate
  EXPECT_TRUE(engine.compare_moves(max_mate_in_two, max_score_two, true));
  EXPECT_FALSE(engine.compare_moves(min_score_two, max_mate_in_two, true));
  EXPECT_TRUE(engine.compare_moves(min_mate_in_two, max_score_two, false));
  EXPECT_FALSE(engine.compare_moves(min_score_two, min_mate_in_two, false));

  // Check no mate > opponent mate
  EXPECT_FALSE(engine.compare_moves(max_mate_in_two, max_score_two, false));
  EXPECT_TRUE(engine.compare_moves(min_score_two, max_mate_in_two, false));
  EXPECT_FALSE(engine.compare_moves(min_mate_in_two, max_score_two, true));
  EXPECT_TRUE(engine.compare_moves(min_score_two, min_mate_in_two, true));

  // Check prefer less moves to mate
  EXPECT_TRUE(engine.compare_moves(max_mate_in_two, max_mate_in_three, true));
  EXPECT_TRUE(engine.compare_moves(min_mate_in_three, min_mate_in_two, true));
  EXPECT_FALSE(engine.compare_moves(max_mate_in_two, max_mate_in_three, false));
  EXPECT_FALSE(engine.compare_moves(min_mate_in_three, min_mate_in_two, false));

  // Check prefer better score
  EXPECT_TRUE(engine.compare_moves(max_score_three, max_score_two, true));
  EXPECT_TRUE(engine.compare_moves(max_score_three, min_score_two, true));
  EXPECT_FALSE(engine.compare_moves(max_score_three, min_score_two, false));
  EXPECT_FALSE(engine.compare_moves(min_score_two, min_score_three, false));
}

TEST_F(EngineTest, PushTwoMoves) {
  engine.set_position_new_game();
  engine.push_move_uci("a2a3");
  EXPECT_EQ(engine.get_position(), "rnbqkbnr/pppppppp/8/8/8/P7/1PPPPPPP/RNBQKBNR b KQkq - 0 1");
  engine.push_move_uci("f7f6");
  EXPECT_EQ(engine.get_position(), "rnbqkbnr/ppppp1pp/5p2/8/8/P7/1PPPPPPP/RNBQKBNR w KQkq - 0 2");
}

TEST_F(EngineTest, FindMoveTakeQueenSimple) {
  engine.set_position("6k1/q7/8/8/8/4Q3/8/3K4 w - - 0 1");
  std::string engine_move = chess::uci::moveToUci(engine.find_move(6, false));
  EXPECT_EQ(engine_move, "e3a7");
}

TEST_F(EngineTest, MateInOne) {
  std::vector<std::pair<std::string, std::string>> fen_and_move = {
      std::make_pair("kr6/1p6/p7/4b3/8/8/6BP/R5K1 w - - 0 1", "a1a6"),
      std::make_pair("r2B3k/1p3p1p/8/8/8/b7/7P/K5R1 w - - 0 1", "d8f6"),
      std::make_pair("8/8/R6p/4pkp1/4N3/3P2PP/1r6/3K4 w - - 0 1", "a6f6"),
      std::make_pair("1k1r4/1bNr4/3P4/8/8/8/5PPP/RR5K w - - 0 1", "a1a8"),
      std::make_pair("r6R/ppk1b3/2p1P3/P7/3N4/8/2R3PP/7K w - - 0 1", "d4b5"),
      std::make_pair("8/3b3Q/3Pkr2/8/4P2p/7P/P5PK/8 w - - 0 1", "h7e7"),
      std::make_pair("8/p1p1bkq1/2Q1nNr1/3pP1r1/3P3p/5P1P/P5PK/2R3R1 w - - 0 1", "c6e8"),
      std::make_pair("8/8/8/knN5/1n6/8/3N4/4K3 w - - 0 1", "d2c4"),
  };
  for (size_t i = 0; i < fen_and_move.size(); ++i) {
    engine.set_position(fen_and_move[i].first);
    std::string engine_move = chess::uci::moveToUci(engine.find_move(6, false));
    EXPECT_EQ(engine_move, fen_and_move[i].second);
  }
}

TEST_F(EngineTest, SimpleCaptures) {
  std::vector<std::pair<std::string, std::string>> fen_and_move = {
      std::make_pair("6k1/8/8/8/8/8/3q4/3K4 w - - 0 1", "d1d2"),
      std::make_pair("6k1/1q6/8/8/8/5B2/8/3K4 w - - 0 1", "f3b7"),
      std::make_pair("6k1/8/2n5/8/3R4/8/8/3K4 b - - 0 1", "c6d4"),
      std::make_pair("2B3k1/P3r3/8/8/8/8/3P4/3K4 b - - 0 1", "e7a7"),
      std::make_pair("6k1/4q3/8/8/1N5Q/8/8/3K4 b - - 0 1", "e7h4"),
      std::make_pair("4k3/8/8/2b1r3/3P4/8/3K4/8 w - - 0 1", "d4e5"),
      std::make_pair("2r5/3P4/7k/8/8/8/3K4/8 w - - 0 1", "d7c8q"),
  };

  for (size_t i = 0; i < fen_and_move.size(); ++i) {
    engine.set_position(fen_and_move[i].first);
    std::string engine_move = chess::uci::moveToUci(engine.find_move(6, false));
    EXPECT_EQ(engine_move, fen_and_move[i].second);
  }
}

TEST_F(EngineTest, IntermediateCaptures) {
  std::vector<std::pair<std::string, std::string>> fen_and_move = {
      std::make_pair("rnbqkbnr/ppp2ppp/8/3pp3/8/P4N2/1PPPPPPP/RNBQKB1R w KQkq - 0 3", "f3e5"),
      std::make_pair("r1b1r1k1/pp1p1ppp/n4n2/1Nbp4/3B4/5P2/PPP1P1PP/R2K1BNR w - - 8 13", "d4c5")};
  for (size_t i = 0; i < fen_and_move.size(); ++i) {
    engine.set_position(fen_and_move[i].first);
    std::string engine_move = chess::uci::moveToUci(engine.find_move(6, false));
    EXPECT_EQ(engine_move, fen_and_move[i].second);
  }
}


TEST_F(EngineTest, MateInTwo) {
  std::vector<std::pair<std::string, std::string>> fen_and_move = {
      std::make_pair("7r/7k/1R6/R7/7r/8/8/6K1 w - - 0 1", "a5a7"),
      std::make_pair("rk2r3/8/8/8/8/2R5/3R4/6K1 w - - 0 1", "d2b2"),
      std::make_pair("5r1k/2RR4/5r2/8/8/6Pp/7P/6K1 w - - 0 1", "d7h7"),
      std::make_pair("3r2kr/8/8/8/8/5R2/4R3/6K1 w - - 0 1", "e2g2"),
      std::make_pair("rr4k1/2R4R/5p1P/5p2/8/P7/8/K7 w - - 0 1", "c7g7"),
      std::make_pair("r4bk1/3R3p/6p1/3N4/8/8/6PP/7K w - - 0 1", "d5f6"),
      std::make_pair("R3N1k1/5p2/6p1/3b2P1/8/5r2/7P/7K w - - 0 1", "e8f6"),
      std::make_pair("4r1kb/3R3p/6p1/8/6N1/8/6PP/7K w - - 0 1", "g4h6"),
      std::make_pair("6k1/3R2p1/5pNp/5P2/3b4/3r4/6PP/7K w - - 0 1", "d7d8"),
      std::make_pair("5rk1/5pp1/8/8/6N1/5P2/5K2/6R1 w - - 0 1", "g4f6"),
      std::make_pair("r5k1/3R3p/4P1pb/3N1p2/8/8/6PP/7K w - - 0 1", "d5f6"),
      std::make_pair("6k1/5p2/5B2/3R3P/8/5n2/5r2/7K w - - 0 1", "d5d8"),
      std::make_pair("7b/4r1k1/7p/3Bp2K/4P3/8/8/5R2 w - - 0 1", "f1g1"),
      std::make_pair("2R5/5pkr/6b1/2B5/5PK1/8/8/8 w - - 0 1", "c5f8"),
  };

  for (size_t i = 0; i < fen_and_move.size(); ++i) {
    engine.set_position(fen_and_move[i].first);
    std::string engine_move = chess::uci::moveToUci(engine.find_move(6, false));
    EXPECT_EQ(engine_move, fen_and_move[i].second);
  }
}