#pragma once
#include <string>

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
        virtual void connect(IServer& server) = 0;
        virtual void disconnect() = 0;
    };
}