#ifndef STATE
#define STATE
#include "serverhandle.hpp"
#include <fstream>

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
        virtual void msg_accept(std::string_view msg) = 0;
        virtual void new_user(std::string_view nick_name, std::size_t hash) = 0;
        virtual void login(std::string_view nick_name, std::size_t hash) = 0;
        virtual void exit() = 0;
        virtual void disconnect() = 0;
        void set_context(chat::ServerHandle* context)
        {
            m_context = context;
        }
    };

    class UnloginedClient: public IState
    {
        std::ostream& m_logger;
    public:
        UnloginedClient(std::ostream& logger)
        :m_logger(logger)
        {

        }
        void msg_accept(std::string_view msg) override;
        void new_user(std::string_view nick_name, std::size_t hash) override;
        void login(std::string_view nick_name, std::size_t hash) override;
        void exit() override {}
        void disconnect() override;
        void echo() override;
    };

    class LoginedClient: public IState
    {
        std::ostream& m_logger;
        std::string m_my_name;
    public:
        explicit LoginedClient(std::string_view name, std::ostream& logger)
        : m_logger(logger)
        , m_my_name(name.begin(), name.end())
        {
            // m_context->set_activ_true();
        }

        void msg_accept(std::string_view msg) override;
        void new_user(std::string_view nick_name, std::size_t hash) override {}
        void login(std::string_view nick_name, std::size_t hash) override {}
        void exit() override;

        void disconnect() override;
        void echo() override;
    };
} // namespace chat
#endif //STATE