#ifndef SERVER
#define SERVER

#include "interfaces.hpp"
#include "serverhandle.hpp"
#include <map>
#include <vector>

namespace chat {
  
    struct UserHash
    {
        std::string m_userName;
        std::size_t m_userHash;
    };

    class Server: public IServer
    {
    private:
        friend class ServerHandle;
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

    };
} // namespace chat
#endif //SERVER