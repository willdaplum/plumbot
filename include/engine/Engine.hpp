#pragma once

#include <string>

class Engine {
public:
 void set_debug(bool debug_on);

 void set_position(std::string fen);

 void set_position_new_game();

 void get_id();

private:
 void minimax();

 void static_evaluate();

 const std::string id_name = "plumbot";
 const std::string id_author = "will cooley";
};