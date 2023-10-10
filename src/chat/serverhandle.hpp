#ifndef SERVERHANDLE
#define SERVERHANDLE
#include "interfaces.hpp"

namespace chat {
    class Server;
    class IState;
    class ServerHandle: public IServerHandle
    {
    private:
        friend class IState;
        IState* m_state;
    protected:
        Server& m_server;
        IClient& m_client;
        std::ostream& m_logger;
    public:
        ServerHandle(Server& server, IClient& client, std::ostream& logger);
        ~ServerHandle() noexcept;

        void set_state(IState* state);
        void msg_accept(const std::string& msg) override;
        void new_user(std::string_view nick_name, std::size_t hash) override;
        void login(std::string_view nick_name, std::size_t hash) override;
        void exit() override;
        void disconnect() override;
        void echo() override;
    };
} // namespace chat
#endif //SERVERHANDLE