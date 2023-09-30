#ifndef STATE
#define STATE
#include "serverhandle.hpp"

namespace chat {
    class LoginedClient;

    class IState: public IServerHandle
    {
    protected:
        ServerHandle* m_context;

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
        void disconnect() override;
        void echo() override {};
    };

    class LoginedClient: public IState
    {
        std::string m_my_name;
    public:
        explicit LoginedClient(std::string name) noexcept
        : m_my_name(std::move(name))
        {

        }

        void msg_accept(const std::string& msg) override;
        void new_user(const std::string& nick_name, std::size_t hash) override {}
        void login(const std::string& nick_name, std::size_t hash) override {}
        void exit() override
        {
            m_context->set_state(new UnloginedClient);
        }

        void disconnect() override;
        void echo() override {};
    };
} // namespace chat
#endif //STATE