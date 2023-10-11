#include <chat/net_server.hpp>
#include <chat/terminal_client.hpp>
#include <chat/functions.hpp>
#include <fstream>
#include <./main_arg/main_arg.hpp>

#define COLOR_RED "\033[1;31m"
#define COLOR_GRUN "\033[32m"
#define COLOR_RESET "\033[0m"


int main(int argc, char* argv[])
{
    start();
    std::fstream logger("log_client.txt", std::ios::out);
    MainArg args(argc, argv);
    try {
        chat::NetServer server(args[0], args[1], logger);
        chat::TerminalClient client(&server, logger);
        star_print();
        std::cout << 
                COLOR_GRUN << "Welcom to console chat!"
                << COLOR_RESET << std::endl;
        star_print();
        std::cout << 
                COLOR_GRUN 
                << "Enter your command or info to see methods:"
                << COLOR_RESET << std::endl;
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
            std::cout << COLOR_GRUN << "By!" << COLOR_RESET << std::endl;
            exit(0);
        }
    } catch (...) {
        logger << "SERVER CONNECTION PROBLEM" << std::endl;
        std::cerr <<
                COLOR_RED << "SERVER CONNECTION PROBLEM"
                << COLOR_RESET << std::endl;
        logger.close();
    }

    return 0;
}