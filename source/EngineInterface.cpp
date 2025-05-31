#include "engine/EngineInterface.hpp"
#include "engine/Command.hpp"

#include <iostream>


std::string EngineInterface::process_command(const std::string uci_input) {
    const std::string delimiter = " ";
    std::string uci_command_text = uci_input.substr(0, uci_input.find(delimiter));
    auto uci_command_it = uci_commands.find(uci_command_text);
    if(uci_command_it == uci_commands.end()) {
        // TODO: this is an error
    }
    UCICommand uci_command =  uci_command_it->second;

    switch (uci_command) {
        default:
        case UCICommand::DEBUG:
            std::cout << "debug\n";
        case UCICommand::GO:
        case UCICommand::ISREADY:
        case UCICommand::PONDERHIT:
        case UCICommand::POSITION:
        case UCICommand::QUIT:
        case UCICommand::REGISTER:
        case UCICommand::SETOPTION:
        case UCICommand::STOP:
        case UCICommand::UCI:
        case UCICommand::UCINEWGAME:
    }
    return "";
};
