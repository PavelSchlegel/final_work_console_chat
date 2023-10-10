#include "state.hpp"
#include "server.hpp"

using namespace chat;

void UnloginedClient::disconnect()
{
    get_server().m_clients.erase(&get_client());
}

void UnloginedClient::new_user(std::string_view nick_name, std::size_t hash)
{
    for (auto& rec: get_server().m_users) {
        if (rec.m_userName == nick_name) {
            get_client().msg_recv("SERVER:", "Nick is used!");
            return;
        }
    }
    get_server().m_users.emplace_back(UserHash{{nick_name.begin(), nick_name.end()}, hash});
    m_context->set_state(new LoginedClient(nick_name));
}

void UnloginedClient::login(const std::string& nick_name, std::size_t hash)
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
void LoginedClient::msg_accept(const std::string& msg)
{
    for (auto& rec: get_server().m_clients) {
        if (&rec.second != m_context) {
            rec.first->msg_recv(m_my_name, msg);
        }
    }
}

void LoginedClient::disconnect()
{
    for (auto it = get_server().m_clients.begin(); it != get_server().m_clients.end(); ++it) {
        if (it->first == &get_client()) {
            get_server().m_clients.erase(it);
        }
    }
}
