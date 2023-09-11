#pragma once
#include "iserver.hpp"
#include <map>

namespace chat {
    class Server;

    class ServerHandle: public IServerHandle
    {
    private:
        IClient& m_client;
        Server& m_server;
    public:
        ServerHandle(Server& server, IClient& client)
        : m_client(client)
        , m_server(server)
        {

        }

        void msg_accept_to(const std::string& msg) override;
        void new_user(const std::string& nike_name, std::size_t hash) override;
        void login(const std::string& nike_name, std::size_t hash) override;
        void exit() override;
    };

    class Server: public IServer
    {
    private:
        std::map<IClient*, ServerHandle> m_clients;
    public:
        IServerHandle& connect(IClient& client) override
        {
            auto [it, inserted] = m_clients.emplace(std::piecewise_construct,
                std::forward_as_tuple(&client),
                std::forward_as_tuple(*this, client)
            );
            return it->second;
        }

        void disconnect(IClient& client) override;
    };
}