#include <chat/net_server.hpp>
#include <chat/terminal_client.hpp>
#include <chat/functions.hpp>
#include <fstream>

int main(int argc, char* argv[])
{
    std::fstream logger("log_client.txt", std::ios::out);
    // if (argc != 3)
    // {
    //     std::cerr << "Usage: chat_client <host> <port>\n";
    //     /*
    //     example
    //     host: localhost or 127.0.0.1
    //     port: 2020
    //     */
    //     return 1;
    // }

    chat::NetServer server(/*argv[1], argv[2]*/"127.0.0.1", "2020", logger);
    chat::TerminalClient client(&server);

    std::cout << "Welcom to console chat!" << std::endl;
    std::cout << "Enter your command or info to see methods:" << std::endl;
    while (1) {
        std::string line;
        std::getline(std::cin, line);
        client.go(line);
        line.clear();
    }

    return 0;
}