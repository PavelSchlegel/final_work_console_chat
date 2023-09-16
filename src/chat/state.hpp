#pragma once
#include "server.hpp"
#include "iclient.hpp"

namespace chat {
    class LoginedClient;

    class IState: public IServerHandle
    {
    protected:
        chat::ServerHandle* m_context;

        Server& get_server() const noexcept
        {
            return m_context->m_server;
        }

        IClient& get_client() const noexcept
        {
            return m_context->m_client;
        }

    public:
        virtual void msg_recv(const std::string& msg) = 0;
        void set_context(chat::ServerHandle* context)
        {
            m_context = context;
        }
    };

    class UnloginedClient: public IState
    {
    public:
        void msg_recv(const std::string& msg) override {}
        void msg_accept() override {}
        void new_user() override;
        void login() override; 
        void exit() override {}
        void disconnect() override
        {
            for (auto it = get_server().m_clients.begin(); it != get_server().m_clients.end(); ++it) {
                if (it->first == &get_client()) {
                    get_server().m_clients.erase(it);
                }
            }
        }
    };

    class LoginedClient: public IState
    {
        std::string m_my_name;
    public:
        explicit LoginedClient(std::string name) noexcept
        : m_my_name(std::move(name))
        {

        }

        void msg_accept() override
        {
            std::string msg = get_msg();
            for (auto& rec: get_server().m_clients) {
                if(rec.second.)
            }
        }

        void msg_recv(const std::string& msg) override
        {
            get_client().msg_recv(msg);
        }

        void new_user() override {}
        void login() override {}
        void exit() override
        {
            // get_server().logg_out(get_client());
            m_context->set_state(new UnloginedClient);
        }

        void disconnect() override
        {
            for (auto it = get_server().m_clients.begin(); it != get_server().m_clients.end(); ++it) {
                if (it->first == &get_client()) {
                    get_server().m_clients.erase(it);
                }
            }
        }
    };

    inline void UnloginedClient::new_user()
    {
        for (auto& rec: get_server().m_users) {
            if (rec.m_userName == nick_name) {
                get_client().msg_recv("Nick is used!");
                return;
            }
        }
        get_server().m_users.emplace_back(UserHash{nick_name, hash});
        get_server().m_users_log.emplace(nick_name, get_client());
    }

    inline void UnloginedClient::login()
    {
        for (auto& rec: get_server().m_users) {
            if (rec.m_userName == nick_name) {
                if (rec.m_userHash == hash) {
                    // get_server().m_users_log.emplace(nick_name, get_client());
                    m_context->set_state(new LoginedClient(nick_name));
                    return;
                }
            }
        } //у юзеров уникальные ники
        get_client().msg_recv("User was not found!");    
    }
}