#ifndef SERVER
#define SERVER

#include <boost/json.hpp>
#include "interfaces.hpp"
#include "serverhandle.hpp"
#include <map>
#include <vector>
#include <fstream>

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
        std::ostream& m_logger;

    public:
        std::vector<UserHash> m_users; //user registr
        std::map<IClient*, ServerHandle> m_clients; //connected

        Server (std::ostream& logger)
        : m_logger(logger)
        {
            std::fstream fs("m_users_save.txt", std::ios::in);
            if (fs.is_open()) {
                auto db = boost::json::parse(fs).as_array();
                for (const auto& value : db) {
                    auto user = value.as_object();
                    m_users.emplace_back(UserHash{user["nick"].as_string().c_str(), user["hash"].to_number<std::size_t>()});
                }
            }
        }

        ~Server()
        {
            db_save();
        }

        void db_save()
        {
            boost::json::array db;
            for (const auto& user : m_users) {
                db.emplace_back(boost::json::object{{"nick", user.m_userName}, {"hash", user.m_userHash}});
            }
            std::fstream("m_users_save.txt", std::ios::out) << boost::json::serialize(db);
        }

        IServerHandle& connect(IClient& client) override
        {
            auto [it, inserted] = m_clients.emplace(std::piecewise_construct,
                std::forward_as_tuple(&client),
                std::forward_as_tuple(*this, client, m_logger)
            );
            m_logger << "SERVER: NEW_CONNECT:" << std::endl;
            return it->second;
        }

        void disconnect(IClient& client) override
        {
            if (auto rec = m_clients.find(&client); rec != m_clients.end()) {
                m_clients.erase(rec);
                m_logger << "SERVER: CLIENT_DISCONNECTED:" << std::endl;
            }
        }

    };
} // namespace chat
#endif //SERVER