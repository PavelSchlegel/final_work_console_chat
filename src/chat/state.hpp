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
        void msg_accept_to(const std::string& msg, const std::string& who) override {}
        void new_user(const std::string& nike_name, std::size_t hash) override;
        void login(const std::string& nick_name, std::size_t hash) override; 
        void exit() override {}
    };

    class LoginedClient: public IState
    {
    public:
        void msg_accept_to(const std::string& msg, const std::string& who) override
        {
            // for (auto& rec: get_server().m_clients) {
            //     if (m_context != &rec.second) {
            //         rec.second.msg_recv(msg);
            //     }
            // }
        }

        void msg_recv(const std::string& msg) override
        {
            get_client().msg_recv(msg);
        }

        void new_user(const std::string& nike_name, std::size_t hash) override {}
        void login(const std::string& nike_name, std::size_t hash) override {}
        void exit() override
        {
            get_server().logg_out(get_client());
            m_context->set_state(new UnloginedClient);
        }
    };

    inline void UnloginedClient::new_user(const std::string& nick_name, std::size_t hash)
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

    inline void UnloginedClient::login(const std::string& nick_name, std::size_t hash)
    {
        for (auto& rec: get_server().m_users) {
            if (rec.m_userName == nick_name) {
                if (rec.m_userHash == hash) {
                    get_server().m_users_log.emplace(nick_name, get_client());
                    m_context->set_state(new LoginedClient);
                    return;
                }
            }
        } //у юзеров уникальные ники
        get_client().msg_recv("User was not found!");    
    }
}