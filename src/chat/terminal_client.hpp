#pragma once
#include <iostream>
#include "iserver.hpp"
#include "iclient.hpp"

namespace chat {

    class TerminalClient: public chat::IClient
    {
    private:
        IServerHandle& m_server_handle;
    public:
        TerminalClient(chat::IServer* server = nullptr)
        : m_server_handle(server->connect(*this))
        {
            
        }

        ~TerminalClient()
        {
            m_server_handle.disconnect();
        }

        void msg_recv(const std::string& who, const std::string& msg) override
        {
            std::cout << who << ":" << '\n';
            std::cout << msg << std::endl;
        }

        void msg_send();

        void new_user();

        void login();

        void exit()
        {
            m_server_handle.exit();
        }

    };
} // namespace chat