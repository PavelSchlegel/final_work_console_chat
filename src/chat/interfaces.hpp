#ifndef INTERFACES
#define INTERFACES
#include <string>

namespace chat {

    class IClient
    {
    public:
        virtual ~IClient() noexcept {}
        virtual void msg_recv(const std::string& who, const std::string& msg) = 0;
    };

    class IServerHandle
    {
    public:
        virtual ~IServerHandle() noexcept {}
        virtual void msg_accept(std::string_view msg) = 0;
        virtual void new_user(std::string_view nick_name, std::size_t hash) = 0;
        virtual void login(std::string_view nick_name, std::size_t hash) = 0;
        virtual void exit() = 0;
        virtual void disconnect() = 0;
        virtual void echo() = 0;
    };

    class IServer
    {
    public:
        virtual ~IServer() noexcept {}
        virtual IServerHandle& connect(IClient& client) = 0;
        virtual void disconnect(IClient& client) = 0;
    };
}; // namespace chat
#endif //INTERFACES