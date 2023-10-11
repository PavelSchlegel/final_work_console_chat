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

        void jFormatRead(const boost::json::value& json)
        {
            if (json.is_object()) {
                boost::json::object json_obj = json.as_object();
                if (json_obj.contains("echo")) {
                    std::cout << "Logg write..." << std::endl;
                    m_logger << "JSON_READ: CALL ECHO FROM CLIENT" << std::endl;
                    m_server_handle.echo();
                    return;
                }

                if (auto nick_ptr =  json_obj.if_contains("new_user")) {
                    if (auto nick = nick_ptr->if_string()) {
                        if (auto hash_ptr = json_obj.if_contains("hash")) {
                            if (auto hash = hash_ptr->if_uint64()) {
                                std::cout << "Logg write..." << std::endl;
                                m_logger << "JSON_READ: NEW USER: " << *nick << std::endl;
                                m_server_handle.new_user(*nick, *hash);
                                return;
                            }
                        }
                    } 
                }

                if (auto login_ptr = json_obj.if_contains("login")) {
                    if (auto nick = login_ptr->if_string()) {
                        if (auto hash_ptr = json_obj.if_contains("hash")) {
                            if (auto hash = hash_ptr->if_uint64()) {
                                std::cout << "Logg write..." << std::endl;
                                m_logger << "JSON_READ: USER" << *nick << "LOGIN" << std::endl;
                                m_server_handle.login(*nick, *hash);
                                return;
                            }
                        }
                    }
                }

                if (auto login_ptr = json_obj.if_contains("exit")) {
                        std::cout << "Logg write..." << std::endl;
                        m_logger << "JSON_READ: USER EXIT" << std::endl;
                        m_server_handle.exit();
                        return;
                }

                if (auto msg_ptr = json_obj.if_contains("message")) {
                    if (auto msg = msg_ptr->if_string()) {
                        std::cout << "Logg write..." << std::endl;
                        m_logger << "JSON_READ: MESSAGE IN" << std::endl;
                        m_server_handle.msg_accept(*msg);
                        return;
                    }
                }
            }
        }

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
                std::cout << "Logg write..." << std::endl;
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
                        std::size_t offset = 0;
                        std::size_t size = 0;
                        boost::json::stream_parser sp;
                        boost::json::error_code ec;
                        for (;;) {
                            sp.reset();
                            do {
                                if (offset == size) {
                                    size = m_socket.async_read_some(boost::asio::buffer(data), yield);
                                    offset = 0;
                                }
                                offset += sp.write_some(&data[offset], size - offset, ec);
                                if (ec) {
                                    std::cout << "Logg write...ERROR: ASYNC_GO" << std::endl;
                                    m_logger << "GO_FUNCTION: " << ec.what() << "CLIENT DISCINNECTED" << std::endl;
                                    m_socket.close();
                                    return;
                                }
                            } while ( ! sp.done() );
                            boost::json::value json = sp.release();
                            std::cout << "Logg write..." << std::endl;
                            m_logger << "NET_ACCEPT: " << json << std::endl;
                            //вызовы server_handle
                            jFormatRead(json);
                        }
                    }
                    catch (std::exception& e)
                    {
                         std::cout << "Logg write...ERROR: ASYNC_GO_CATCH" << std::endl;
                        m_socket.close();
                        m_logger << "CLIENT DISCONNECTED" << std::endl;
                    }
                },
                boost::asio::detached
            );
        }
    };
} // namespace chat