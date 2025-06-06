#include <gtest/gtest.h>

#include "engine/EngineInterface.hpp"

TEST(EngineWrapperTest, Position) {
    EngineInterface engine_interface = EngineInterface();
    engine_interface.process_command("position startpos moves a2a3 f7f6\n");
    engine_interface.process_command("position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
};

TEST(EngineWrapperTest, PositionWithFen) {

    
};