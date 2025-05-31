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
            std::cout << "unrecognized command\n";
            break;
        case UCICommand::DEBUG:
            std::cout << "debug\n";
            break;
        case UCICommand::GO:
            std::cout << "go\n";
            break;
        case UCICommand::ISREADY:
            std::cout << "isready\n";
            break;
        case UCICommand::PONDERHIT:
            std::cout << "ponderhit\n";
            break;
        case UCICommand::POSITION:
            std::cout << "position\n";
            break;
        case UCICommand::QUIT:
            std::cout << "quit\n";
            break;
        case UCICommand::REGISTER:
            std::cout << "register\n";
            break;
        case UCICommand::SETOPTION:
            std::cout << "setoption\n";
            break;
        case UCICommand::STOP:
            std::cout << "stop\n";
            break;
        case UCICommand::UCI:
            uci_cmd();
            break;
        case UCICommand::UCINEWGAME:
            std::cout << "ucinewgame\n";
            break;
    }
    return "";
};

void EngineInterface::uci_cmd() {
    plumbot.get_id();
}