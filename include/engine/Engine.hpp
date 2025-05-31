#pragma once

#include <string>

class Engine {
public:
 void set_debug(bool debug_on);

 void set_position(std::string fen);

 void set_position_new_game();

private:
 void minimax();

 void static_evaluate();

};