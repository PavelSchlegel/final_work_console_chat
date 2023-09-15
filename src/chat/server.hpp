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

        void msg_recv(const std::string& msg)
        {
            
        }

        void set_state(IState* state)
        {
            m_state = state;
        }

        void msg_accept_to(const std::string& msg, const std::string& who) override
        {
            auto state = m_state;
            state->msg_accept_to(msg, who);
            if (state != m_state) {
                delete state;
            }
        }

        void new_user(const std::string& nike_name, std::size_t hash) override
        {
            auto state = m_state;
            state->new_user(nike_name, hash);
            if (state != m_state) {
                delete state;
            }
        }

        void login(const std::string& nike_name, std::size_t hash) override
        {
            auto state = m_state;
            state->login(nike_name, hash);
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
        std::map<std::string, IClient*> m_users_log; //logined users
        std::vector<UserHash> m_users; //registr
        std::map<IClient*, ServerHandle> m_clients; //connected
        IServerHandle& connect(IClient& client) override
        {
            auto [it, inserted] = m_clients.emplace(std::piecewise_construct,
                std::forward_as_tuple(&client),
                std::forward_as_tuple(*this, client)
            );
            return it->second;
        }

        void logg_out(IClient& client) noexcept
        {
            for (auto it = m_users_log.begin(); it != m_users_log.end(); ++it) {
                if (it->second == &client) {
                    m_users_log.erase(it);
                }
            }
        }

        void disconnect(IClient& client) override;
        friend class ServerHandle;
    };
}