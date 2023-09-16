#pragma once
#include <string>

namespace chat {
    class IClient;

    class IServerHandle
    {
    public:
        virtual ~IServerHandle() noexcept {}
        virtual void msg_accept() = 0;
        virtual void new_user() = 0;
        virtual void login() = 0;
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