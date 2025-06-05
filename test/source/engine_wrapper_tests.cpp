#include <gtest/gtest.h>

#include "engine/EngineInterface.hpp"

TEST(EngineWrapperTest, PositionWithMoves) {
    EngineInterface engine_interface = EngineInterface();
    engine_interface.process_command("position startpos moves a2a3 f7f6\n");
}