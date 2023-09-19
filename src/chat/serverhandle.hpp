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
    public:
        ServerHandle(Server& server, IClient& client);
        ~ServerHandle() noexcept;

        void set_state(IState* state);
        void msg_accept(const std::string& msg) override;
        void new_user(const std::string& nick_name, std::size_t hash) override;
        void login(const std::string& nick_name, std::size_t hash) override;
        void exit() override;
        void disconnect() override;
    };
} // namespace chat
#endif //SERVERHANDLE