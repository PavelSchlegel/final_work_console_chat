#pragma once
#include <memory>
#include "interfaces.hpp"
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

namespace chat {
    using boost::asio::ip::tcp;

    class NetClient: public chat::IClient, public std::enable_shared_from_this<NetClient>
    {
    private:
        tcp::socket m_socket;
        IServerHandle& m_server_handle;
    public:
        NetClient(chat::IServer& server, tcp::socket socket)
        : m_socket(std::move(socket))
        , m_server_handle(server.connect(*this))
        {
            
        }

        ~NetClient()
        {
            m_server_handle.disconnect();
        }

        void msg_recv(const std::string& who, const std::string& msg) override
        {
            //wriete
        }

        void go(boost::asio::io_context& io_context)
        {
            auto self(shared_from_this());
            boost::asio::spawn(
                io_context, 
                [this, self](boost::asio::yield_context yield)
                {
                    try
                    {
                        char data[128];
                        for (;;) {
                            std::size_t n = m_socket.async_read_some(boost::asio::buffer(data), yield);

                            //вызовы server_handle
                        }
                    }
                    catch (std::exception& e)
                    {
                        m_socket.close();
                    }
                },
                boost::asio::detached
            );
        }
    };
} // namespace chat