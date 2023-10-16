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
        std::ostream& m_logger;
        bool stop_flag;

        void msg_send();
        void new_user();
        void login();
        void echo();
        void exit();
        void info();
        void close();
        void go(std::string& method);

    public:

        TerminalClient(chat::IServer* server, std::ostream& logger);
        ~TerminalClient();

        void msg_recv(const std::string& who, const std::string& msg) override;
    };
} // namespace chat