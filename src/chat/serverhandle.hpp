#ifndef SERVERHANDLE
#define SERVERHANDLE
#include "interfaces.hpp"
#include <iostream>

namespace chat {
    class Server;
    class IState;
    class ServerHandle: public IServerHandle
    {
    private:
        friend class IState;
        IState* m_state;
        bool is_activ;
    protected:
        IClient& m_client;
        Server& m_server;
        std::ostream& m_logger;
    public:
        ServerHandle(Server& server, IClient& client, std::ostream& logger);
        ~ServerHandle() noexcept;

        bool isActiv();
        void set_activ_true();
        void set_activ_false();
        void set_state(IState* state);
        void msg_accept(std::string_view msg) override;
        void new_user(std::string_view nick_name, std::size_t hash) override;
        void login(std::string_view nick_name, std::size_t hash) override;
        void exit() override;
        void disconnect() override;
        void echo() override;
    };
} // namespace chat
#endif //SERVERHANDLE