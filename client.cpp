#include <chat/net_server.hpp>
#include <chat/terminal_client.hpp>
#include <chat/functions.hpp>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: chat_client <host> <port>\n";
        /*
        example
        host: localhost or 127.0.0.1
        port: 2020
        */
        return 1;
    }

    chat::NetServer server(argv[1], argv[2]);
    chat::TerminalClient client(&server);
    com_parser(&client);
    return 0;
}