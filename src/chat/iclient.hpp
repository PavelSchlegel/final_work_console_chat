#pragma once
#include <string>
#include "iserver.hpp"
#include "./post_envelope/post_envelope.hpp"
#include "function.hpp"

namespace chat {
    class IServer;

    class IClient
    {
    public:
        // virtual void msg_recv(const std::string& msg) = 0;
        // virtual void msg_send(const std::string& msg) = 0;
        virtual void msg_recv() = 0;
        virtual void msg_send() = 0;
        virtual void new_user() = 0;
        virtual void login() = 0;
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

        void msg_send() override
        {
            Letter letter;
            letter.set_recipient(get_recipient());
            letter.set_msg(get_msg());
            //client nick...
            m_server_handle.msg_accept_to(letter);
        }

        void new_user() override
        {
            m_server_handle.login(get_nick_name(), get_pass());
        }

        void login() override
        {
            m_server_handle.login(get_nick_name(), get_pass());
        }

        void exit() override
        {
            m_server->disconnect(*this);
        }

        void disconnect() override
        {
            m_server->disconnect(*this);
        }
    };
}