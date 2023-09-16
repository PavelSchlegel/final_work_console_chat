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
        virtual void msg_recv(const std::string& msg) = 0;
        virtual void msg_send() = 0;
        virtual void new_user() = 0;
        virtual void login() = 0;
        virtual void exit() = 0;
    };

    class TerminalClient: public IClient
    {
    private:
        // IServer* m_server;
        IServerHandle& m_server_handle;
    public:
        TerminalClient(chat::IServer* server = nullptr)
        // : m_server(server)
        : m_server_handle(server->connect(*this))
        {
            
        }

        ~TerminalClient()
        {

        }

        void msg_recv(const std::string& msg)
        {
            std::cout << msg << std::endl;
        }

        void msg_send() override
        {
            m_server_handle.msg_accept();
        }

        void new_user() override
        {
            m_server_handle.new_user();
        }

        void login() override
        {
            m_server_handle.login();
        }

        void exit() override
        {
            m_server_handle.exit();
        }
/*
        void disconnect() override
        {
            exit();
            m_server->disconnect(*this);
        }
*/
    };
};