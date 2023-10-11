#include "net_server.hpp"
#include <iostream>

using namespace chat;
using namespace boost::json;
using namespace boost::asio;

void context_run(boost::asio::io_context& io_context)
{
    io_context.run();
}

NetServer::NetServer(std::string_view host, std::string_view port, std::ostream& logger)
: m_logger(logger)
{
    tcp::resolver resolver(io_context);
    boost::asio::socket_base::keep_alive option(true);
    boost::asio::connect(socket, resolver.resolve(host, port));
    socket.set_option(option);
}

NetServer::~NetServer()
{
    if (m_run.joinable()) {
        m_run.join();
        m_logger << "THREAD JOIN &";
    }
    socket.close();
        m_logger << "SOCKET CLOSE" << std::endl;
}

void NetServer::go(boost::asio::yield_context yield)
{
    boost::asio::spawn(
        io_context, 
        [this](boost::asio::yield_context yield)
        {
            try
            {
                char data[128];
                std::size_t offset = 0;
                std::size_t size = 0;
                boost::json::stream_parser sp;
                boost::json::error_code ec;
                for (;;) {
                    sp.reset();
                    do {
                        if (offset == size) {
                            size = socket.async_read_some(boost::asio::buffer(data), yield);
                            offset = 0;
                        }
                        offset += sp.write_some(&data[offset], size - offset, ec);
                        if (ec) {
                            m_logger << "GO_FUNCTION: " << ec.what() << "SESSION CLOSE" << std::endl;
                            socket.close();
                            return;
                        }

                    } while ( ! sp.done() );
                    boost::json::value j_format = sp.release();
                    m_logger << "NETWORK RECEPTION :" << j_format << std::endl;
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
                m_logger << "NET_SERVER_GO: " << e.what() << std::endl;
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
    m_logger <<"SOCKET_WRITE" << msg << std::endl;
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
    std::thread T(context_run, std::ref(io_context));
    m_run = std::move(T);
    return *this;
}

void NetServer::msg_accept(std::string_view msg)
{
    value j_format {{"message", msg}};
    m_logger << "MSG_ACCEPT" << std::endl;
    server_write(j_format);
}

void NetServer::new_user(std::string_view nick_name, std::size_t hash)
{
    value j_format {{"new_user", nick_name}, {"hash", hash}};
    m_logger << "SENT_TO_SERVER: NEW USER" << std::endl;
    server_write(j_format);
}

void NetServer::login(std::string_view nick_name, std::size_t hash)
{
    value j_format {{"login", nick_name}, {"hash", hash}};
    m_logger << "SENT_TO_SERVER: LOGIN" << std::endl;
    server_write(j_format);
}

void NetServer::exit()
{
    value j_format {{"exit", "client exiting"}};
    m_logger << "SENT_TO_SERVER: EXIT" << std::endl;
    server_write(j_format);
}

void NetServer::disconnect()
{
    value j_format {{"disconnect", "client close"}};
    m_logger << "SENT_TO_SERVER: EXIT" << std::endl;
    server_write(j_format);
}

void NetServer::echo()
{
    value j_format {{"echo", "TEST FROM CLIENT"}};
    m_logger << "SENT_TO_SERVER: ECHO" << std::endl;
    server_write(j_format);
}