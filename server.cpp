#include <chat/net_client.hpp>
#include <boost/asio/spawn.hpp>
#include <iostream>
#include <chat/server.hpp>
#include <fstream>

int main (int argc, char* argv[])
{
    std::fstream logger("log_server.txt", std::ios::out);
    using boost::asio::ip::tcp;
    chat::Server server(logger);
    try {
        if (argc != 2)
        {
            std::cerr << "Usage: chat_server <port>\n";
            /*
            example
            port: 2020
            */
            return 1;
        }

        boost::asio::io_context io_context;

        boost::asio::spawn(
            io_context,
            [&](boost::asio::yield_context yield)
            {
                tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), std::atoi(argv[1])));

                for (;;) {
                    boost::system::error_code ec;
                    tcp::socket socket(io_context);
                    acceptor.async_accept(socket, yield[ec]);
                    logger << "NEW_CONNECT" << std::endl;
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
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}