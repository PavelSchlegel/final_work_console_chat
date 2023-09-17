#pragma once
#include "iserver.hpp"
#include <map>
#include "state.hpp"
#include <vector>

namespace chat {
    class Server;
    class IState;

    class ServerHandle: public IServerHandle
    {
    protected:
        Server& m_server;
        IClient& m_client;
    private:
        IState* m_state;
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

        void set_state(IState* state)
        {
            m_state = state;
        }

        void msg_accept(const std::string& msg) override
        {
            auto state = m_state;
            state->msg_accept(msg);
            if (state != m_state) {
                delete state;
            }
        }

        void new_user(const std::string& nick_name, std::size_t hash) override
        {
            auto state = m_state;
            state->new_user(nick_name, hash);
            if (state != m_state) {
                delete state;
            }
        }

        void login(const std::string& nick_name, std::size_t hash) override
        {
            auto state = m_state;
            state->login(nick_name, hash);
            if (state != m_state) {
                delete state;
            }
        }
        
        void exit() override
        {
            auto state = m_state;
            state->exit();
            if (state != m_state) {
                delete state;
            }
        }

        void disconnect() override
        {
            m_state->disconnect();
        }

        friend class IState;
    };

    struct UserHash
    {
        std::string m_userName;
        std::size_t m_userHash;
    };

    class Server: public IServer
    {
    private:
    public:
        std::vector<UserHash> m_users; //user registr
        std::map<IClient*, ServerHandle> m_clients; //connected
        IServerHandle& connect(IClient& client) override
        {
            auto [it, inserted] = m_clients.emplace(std::piecewise_construct,
                std::forward_as_tuple(&client),
                std::forward_as_tuple(*this, client)
            );
            return it->second;
        }

        void disconnect(IClient& client) override
        {
            if (auto rec = m_clients.find(&client); rec != m_clients.end()) {
                m_clients.erase(rec);
            }
        }

        friend class ServerHandle;
    };
} // namespace chat