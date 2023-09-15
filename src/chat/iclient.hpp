#pragma once
#include <string>
#include "iserver.hpp"

namespace chat {
    class IServer;

    class IClient
    {
    public:
        virtual void msg_recv(const std::string& msg) = 0;
        virtual void msg_send(const std::string& msg) = 0;
        virtual void new_user(const std::string& nike_name, std::size_t hash) = 0;
        virtual void login(const std::string& nike_name, std::size_t hash) = 0;
        virtual void exit() = 0;
        // virtual void connect(IServer& server) = 0;
        virtual void disconnect() = 0;
    };

    class Client: public IClient
    {
    private:
        IServer* m_server;
        IServerHandle& m_server_handle;
    public:
        Client(chat::IServer* server = nullptr)
        : m_server(server)
        , m_server_handle(m_server->connect(*this))
        {
            
        }

        ~Client()
        {

        }

        void msg_recv(const std::string& msg)
        {
            //some
        }

        void msg_send(const std::string& msg)
        {
            m_server_handle.msg_accept_to(const std::string &msg, const std::string &who);
        }

        void new_user(const std::string& nike_name, std::size_t hash) {}
        void login(const std::string& nike_name, std::size_t hash) {}
        void exit() {}
        // void connect(IServer& server)
        // {
            
        // }

        void disconnect()
        {
            m_server->disconnect(*this);
        }
    };
}