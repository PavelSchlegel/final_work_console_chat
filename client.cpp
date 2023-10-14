#include <chat/net_server.hpp>
#include <chat/terminal_client.hpp>
#include <chat/functions.hpp>
#include <fstream>
#include <./main_arg/main_arg.hpp>

int main(int argc, char* argv[])
{
    star_print();
    start();
    std::fstream logger("log_client.txt", std::ios::out);
    MainArg args(argc, argv);
    try {
        chat::NetServer server(args[0], args[1], logger);
        chat::TerminalClient client(&server, logger);
        star_print();
        std::cout << 
                colors::grun << "Welcom to console chat!"
                << colors::reset << std::endl;
        star_print();
        std::cout << 
                colors::grun 
                << "Enter your command or info to see methods:"
                << colors::reset << std::endl;
        star_print();
        try {
            while (true) {
                std::string line;
                std::getline(std::cin, line);
                client.go(line);
                if ( ! line.empty()) {
                    std::cout << line << std::endl;
                }
            }
        } catch (...) {
            logger << "PROGRAMM CLOSE" << std::endl;
            std::cout << colors::grun << "By!" << colors::reset << std::endl;
            exit(0);
        }
    } catch (...) {
        logger << "SERVER CONNECTION PROBLEM" << std::endl;
        std::cerr <<
                colors::red << "SERVER CONNECTION PROBLEM"
                << colors::reset << std::endl;
        logger.close();
    }

    return 0;
}