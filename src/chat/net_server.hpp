#ifndef NET_SERVER
#define NET_SERVER
#include "interfaces.hpp"
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

namespace chat {
    using boost::asio::ip::tcp;

    class NetServer: public IServer, IServerHandle
    {
        boost::asio::io_context io_context;
        tcp::socket socket {io_context};
        IClient* client = nullptr;

    private:
        void go(boost::asio::yield_context yield);
    public:
        NetServer(std::string_view host, std::string_view port);
        IServerHandle& connect(IClient& client) override;
        void disconnect(IClient& client) override;

        void msg_accept(const std::string& msg) override;
        void new_user(const std::string& nick_name, std::size_t hash) override;
        void login(const std::string& nick_name, std::size_t hash) override;
        void exit() override;
        void disconnect() override;

    };
} // namespace chat
#endif //NET_SERVER