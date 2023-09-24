#include "net_server.hpp"

using namespace chat;
NetServer::NetServer(std::string_view host, std::string_view port)
{
    tcp::resolver resolver(io_context);
    boost::asio::connect(socket, resolver.resolve(host, port));
}

void NetServer::go(boost::asio::yield_context yield)
{
    //read socket and call method
}

IServerHandle& NetServer::connect(IClient& client)
{
    this->client = &client;
    boost::asio::spawn(
        this->io_context,
        [this] (boost::asio::yield_context yield)
        {
            try
            {
                go(yield);
            }
            catch (std::exception& e)
            {
                socket.close();
            }
        },
        boost::asio::detached
    );
    return *this;
}

void NetServer::disconnect(IClient& client)
{

}

void NetServer::msg_accept(const std::string& msg)
{
    // creat json ->serialis -> socket
}

void NetServer::new_user(const std::string& nick_name, std::size_t hash)
{

}

void NetServer::login(const std::string& nick_name, std::size_t hash)
{

}

void NetServer::exit()
{

}

void NetServer::disconnect()
{

}