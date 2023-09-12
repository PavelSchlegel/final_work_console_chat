#pragma once
#include "server.hpp"

namespace chat {

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
        void msg_accept_to(const std::string& msg) override {}
        void new_user(const std::string& nike_name, std::size_t hash) override {}
        void login(const std::string& nike_name, std::size_t hash) override
        {

        }
        void exit() override {}
    };

    class LoginedClient: public IState
    {
    public:
        void msg_accept_to(const std::string& msg) override
        {
            for (auto& rec: get_server().m_clients) {
                if (m_context != &rec.second) {
                    rec.second.msg_recv(msg);
                }
            }
        }

        void msg_recv(const std::string& msg) override
        {
            get_client().msg_recv(msg);
        }

        void new_user(const std::string& nike_name, std::size_t hash) override {}
        void login(const std::string& nike_name, std::size_t hash) override {}
        void exit() override {}
    };
}