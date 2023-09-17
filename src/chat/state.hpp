#pragma once
#include "server.hpp"
#include "iclient.hpp"
#include "server.hpp"

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
        virtual void msg_accept(const std::string& msg) = 0;
        virtual void new_user(const std::string& nick_name, std::size_t hash) = 0;
        virtual void login(const std::string& nick_name, std::size_t hash) = 0;
        virtual void exit() = 0;
        virtual void disconnect() = 0;
        void set_context(chat::ServerHandle* context)
        {
            m_context = context;
        }
    };

    class UnloginedClient: public IState
    {
    public:
        void msg_accept(const std::string& msg) override {}
        void new_user(const std::string& nick_name, std::size_t hash) override;
        void login(const std::string& nick_name, std::size_t hash) override;
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

        void msg_accept(const std::string& msg) override
        {
            for (auto& rec: get_server().m_clients) {
                if (&rec.second != m_context) {
                    rec.first->msg_recv(m_my_name, msg);
                }
            }
        }

        void new_user(const std::string& nick_name, std::size_t hash) override {}
        void login(const std::string& nick_name, std::size_t hash) override {}
        void exit() override
        {
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

    inline void UnloginedClient::new_user(const std::string& nick_name, std::size_t hash)
    {
        for (auto& rec: get_server().m_users) {
            if (rec.m_userName == nick_name) {
                get_client().msg_recv("SERVER:", "Nick is used!");
                return;
            }
        }
        get_server().m_users.emplace_back(UserHash{nick_name, hash});
        m_context->set_state(new LoginedClient(nick_name));
    }

    inline void UnloginedClient::login(const std::string& nick_name, std::size_t hash)
    {
        for (auto& rec: get_server().m_users) {
            if (rec.m_userName == nick_name) {
                if (rec.m_userHash == hash) {
                    m_context->set_state(new LoginedClient(nick_name));
                    return;
                }
            }
        } //у юзеров уникальные ники
        get_client().msg_recv("SERVER:","Invalid pass or nickname!");    
    }
}