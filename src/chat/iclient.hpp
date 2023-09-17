#pragma once
#include <string>

namespace chat {
    class IServer;

    class IClient
    {
    public:
        virtual void msg_recv(const std::string& who, const std::string& msg) = 0;
    };
}; // namespace chat