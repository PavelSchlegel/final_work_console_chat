#include "net_server.hpp"
#include <iostream>

using namespace chat;
using namespace boost::json;
using namespace boost::asio;

NetServer::NetServer(std::string_view host, std::string_view port, std::ostream& logger)
: m_logger(logger)
{
    tcp::resolver resolver(io_context);
    boost::asio::connect(socket, resolver.resolve(host, port));
}

void NetServer::go(boost::asio::yield_context yield)
{
    //read socket and call method
    boost::asio::spawn(
        io_context, 
        [this](boost::asio::yield_context yield)
        {
            try
            {
                char data[128];
                for (;;) {
                    boost::json::stream_parser sp;
                    boost::json::error_code ec;
                    sp.reset();
                    do {
                        std::size_t n = socket.async_read_some(boost::asio::buffer(data), yield);
                        sp.write_some(data, n, ec);
                        if (ec) {
                            std::cout << ec.what() << std::endl;
                        }
                    } while ( ! sp.done() );
                    boost::json::value j_format = sp.release();
                    m_logger << "INPUT JSON" << std::endl;
                    //вызовы server_handle
                    if (j_format.is_object()) {
                        boost::json::object json_obj = j_format.as_object();
                        auto who = json_obj.find("who");
                        if (who == json_obj.end()) {
                            continue;
                        }
                        auto msg = json_obj.find("message");
                        if (msg == json_obj.end()) {
                            continue;
                        }
                        client->msg_recv(who->value().as_string().c_str(), msg->value().as_string().c_str());
                    }
                }
            }
            catch (std::exception& e)
            {
                socket.close();
            }
        },
        boost::asio::detached
    );
}

void NetServer::server_write(boost::json::value& msg)
{
    char buf[128];
    serializer sr;
    sr.reset(&msg);
    do {
        std::string_view chunk = sr.read(buf);
        boost::asio::write(socket, boost::asio::buffer(chunk.data(), chunk.size()));
    } while ( ! sr.done());
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
                std::cout << e.what() << std::endl;
                socket.close();
            }
        },
        boost::asio::detached
    );
    m_logger << "CONNECT" << std::endl;
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

void NetServer::echo()
{
    value j_format {{"echo", "TEST FROM CLIENT"}};
    server_write(j_format);
}