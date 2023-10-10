#ifndef NET_SERVER
#define NET_SERVER

#include "interfaces.hpp"
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/json.hpp>
#include <thread>

namespace chat {
    using boost::asio::ip::tcp;

    class NetServer: public IServer, IServerHandle
    {
    private:
        friend void context_run(boost::asio::io_context& io_context);
        
        boost::asio::io_context io_context;
        tcp::socket socket {io_context};
        IClient* client = nullptr;
        std::ostream& m_logger;
        std::thread m_run;

        void go(boost::asio::yield_context yield);
        void server_write(boost::json::value& msg);
    public:
        NetServer(std::string_view host, std::string_view port, std::ostream& logger);
        ~NetServer();
        IServerHandle& connect(IClient& client) override;
        void disconnect(IClient& client) override;

        void msg_accept(const std::string& msg) override;
        void new_user(std::string_view nick_name, std::size_t hash) override;
        void login(std::string_view nick_name, std::size_t hash) override;
        void exit() override;
        void disconnect() override;
        void echo() override;
    };
} // namespace chat
#endif //NET_SERVER