#include <chat/net_server.hpp>
#include <chat/terminal_client.hpp>
#include <chat/functions.hpp>
#include <fstream>
#include <sys/utsname.h>

int main(int argc, char* argv[])
{
    struct utsname utsname;
    uname(&utsname);
    std::cout << "OS: " << utsname.sysname << std::endl;
    std::cout << "Host: " << utsname.nodename << std::endl;
    std::cout << "Clietnt start..." << std::endl;
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
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        client.go(line);
        if ( ! line.empty()) {
            std::cout << line << std::endl;
        }
    }

    return 0;
}