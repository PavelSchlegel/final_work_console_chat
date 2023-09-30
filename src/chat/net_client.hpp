#pragma once
#include <memory>
#include "interfaces.hpp"
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/json.hpp>
#include <queue>
#include <iostream>


namespace chat {
    using boost::asio::ip::tcp;
    using wriete_msg = std::queue<boost::json::value>;

    class NetClient: public chat::IClient, public std::enable_shared_from_this<NetClient>
    {
    private:
        wriete_msg msg_scud;
        tcp::socket m_socket;
        IServerHandle& m_server_handle;
        std::ostream& m_logger;

        void do_write(boost::asio::yield_context yield)
        {
            auto self(shared_from_this());
            char buf[128];
            boost::json::serializer sr;
            while ( ! msg_scud.empty() ) {
                boost::system::error_code ec;
                auto& j_format = msg_scud.front();
                sr.reset(&j_format);
                do {
                    boost::asio::async_write(
                        m_socket,
                        boost::asio::buffer(sr.read(buf)),
                        yield[ec]
                    );
                    if (ec) {
                        m_socket.close();
                    }
                } while( ! sr.done() );
                m_logger << "MSG_TO_CLIENT_RESPONSED" << std::endl;
                msg_scud.pop();
            }
        }

    public:
        NetClient(chat::IServer& server, tcp::socket socket, std::ostream& logger)
        : m_socket(std::move(socket))
        , m_server_handle(server.connect(*this))
        , m_logger(logger)
        {
            
        }

        ~NetClient()
        {
            m_server_handle.disconnect();
        }

        void msg_recv(const std::string& who, const std::string& msg) override
        {
            boost::json::value j_format {{"who", who}, {"message", msg}};
            msg_scud.push(j_format);
            if ( ! msg_scud.empty() ) {
                boost::asio::spawn(std::bind(&NetClient::do_write, this, std::placeholders::_1));
            }
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
                            boost::json::stream_parser sp;
                            boost::json::error_code ec;
                            sp.reset();
                            do {
                                sp.write(data, ec);
                                if (ec) {
                                    std::cout << ec.what() << std::endl;
                                }
                            } while ( ! sp.done() );
                            boost::json::value j_format = sp.release();
                            m_logger << "INPUT JSON" << std::endl;
                            //вызовы server_handle
                            if (j_format.is_object()) {
                                boost::json::object json_obj = j_format.as_object();
                                if (auto it = json_obj.find("echo"); it != json_obj.end()) {
                                    msg_recv("SERVER", "SERVER RESPONSE");
                                }
                            }
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