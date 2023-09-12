#pragma once
#include "iserver.hpp"
#include <map>
#include "state.hpp"

namespace chat {
    class Server;
    class IState;

    class ServerHandle: public IServerHandle
    {
    protected:
        Server& m_server;
    private:
        IState* m_state;
        IClient& m_client;
    public:
        ServerHandle(Server& server, IClient& client)
        : m_state(new UnloginedClient)
        , m_client(client)
        , m_server(server)
        {

        }

        ~ServerHandle() noexcept
        {
            delete m_state;
        }

        void msg_recv(const std::string& msg)
        {
            
        }

        void set_state(IState* state)
        {
            if (m_state) {
                m_state = state;
                m_state->set_context(this);
            }
        }

        void msg_accept_to(const std::string& msg) override
        {
            auto state = m_state;
            state->msg_accept_to(msg);
            if (state != m_state) {
                delete state;
            }
        }

        void new_user(const std::string& nike_name, std::size_t hash) override;
        void login(const std::string& nike_name, std::size_t hash) override;
        void exit() override;

        friend class IState;
    };

    class Server: public IServer
    {
    private:
    public:
        std::map<IClient*, ServerHandle> m_clients;
        IServerHandle& connect(IClient& client) override
        {
            auto [it, inserted] = m_clients.emplace(std::piecewise_construct,
                std::forward_as_tuple(&client),
                std::forward_as_tuple(*this, client)
            );
            return it->second;
        }

        friend class ServerHandle;
        void disconnect(IClient& client) override;
    };
}