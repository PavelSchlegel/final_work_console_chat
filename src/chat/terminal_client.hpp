#pragma once
#include <iostream>
#include "interfaces.hpp"
#include <functional>

namespace chat {

    class TerminalClient: public chat::IClient
    {
    private:

        using Method = void (TerminalClient::*)();
        using Method_list = std::vector<std::pair<std::string, Method>>;

        IServerHandle& m_server_handle;
        Method_list methods;

        void msg_send();
        void new_user();
        void login();
        void echo();
        void exit();

    public:

        TerminalClient(chat::IServer* server = nullptr);
        ~TerminalClient();

        void msg_recv(const std::string& who, const std::string& msg) override;
        void go(const std::string& method);
        void info();
    };
} // namespace chat