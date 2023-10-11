#include <chat/net_client.hpp>
#include <boost/asio/spawn.hpp>
#include <iostream>
#include <chat/server.hpp>
#include <fstream>
#include <sys/utsname.h>
#include <chat/functions.hpp>

#define COLOR_RED "\033[1;31m"
#define COLOR_GRUN "\033[32m"
#define COLOR_RESET "\033[0m"

int main (int argc, char* argv[])
{
    star_print();
    start();
    std::cout << COLOR_GRUN << "Server start..." << COLOR_RESET << std::endl;
    std::fstream logger("log_server.txt", std::ios::out);
    using boost::asio::ip::tcp;
    chat::Server server(logger);
    try {
        const char* port = "2020";
        boost::asio::io_context io_context;
        boost::asio::spawn(
            io_context,
            [&](boost::asio::yield_context yield)
            {
                tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), std::atoi(port)));

                for (;;) {
                    boost::system::error_code ec;
                    tcp::socket socket(io_context);
                    acceptor.async_accept(socket, yield[ec]);
                    logger << "NEW_SOCKET" << std::endl;
                    if (!ec)
                    {
                        std::make_shared<chat::NetClient>(server, std::move(socket), logger)->go(io_context);
                    }
                }
            },
            [](std::exception_ptr e)
            {
                if (e) {
                    std::rethrow_exception(e);
                }
            }
        );
        io_context.run();
        std::cout << COLOR_GRUN << "Listing..." << COLOR_RESET << std::endl;
    } catch (std::exception& e) {
        logger << "SERVER_SPAWN:" << e.what() << std::endl;
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}