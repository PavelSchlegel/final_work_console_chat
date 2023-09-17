#pragma once
#include <string>

namespace chat {
    class IClient;

    class IServerHandle
    {
    public:
        virtual ~IServerHandle() noexcept {}
        virtual void msg_accept(const std::string& msg) = 0;
        virtual void new_user(const std::string& nick_name, std::size_t hash) = 0;
        virtual void login(const std::string& nick_name, std::size_t hash) = 0;
        virtual void exit() = 0;
        virtual void disconnect() = 0;
    };

    class IServer
    {
    public:
        virtual IServerHandle& connect(IClient& client) = 0;
        virtual void disconnect(IClient& client) = 0;
    };

}