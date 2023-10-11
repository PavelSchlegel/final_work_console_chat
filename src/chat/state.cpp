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
    get_client().msg_recv("SERVER:", "Welcome!");
    m_logger << "UNLOGINED_CLIENT: NEW_USER" << std::endl;
    get_server().m_users.emplace_back(UserHash{{nick_name.begin(), nick_name.end()}, hash});
    m_context->set_state(new LoginedClient(nick_name, m_logger));
    m_context->set_activ_true();
}

void UnloginedClient::login(std::string_view nick_name, std::size_t hash)
{
    for (auto& rec: get_server().m_users) {
        if (rec.m_userName == nick_name) {
            if (rec.m_userHash == hash) {
                m_context->set_state(new LoginedClient(nick_name, m_logger));
                get_client().msg_recv("SERVER:", "Welcome!");
                return;
            }
        }
    } //у юзеров уникальные ники
    get_client().msg_recv("SERVER:","Invalid pass or nickname!");    
}

void UnloginedClient::msg_accept(std::string_view msg)
{
    get_client().msg_recv("SERVER", "CLIENT LOGIN ZERO");
}

void UnloginedClient::echo()
{
    get_client().msg_recv("Server", "ECHO RESPONSE");
}

void LoginedClient::msg_accept(std::string_view msg)
{
    for (auto& rec: get_server().m_clients) {
        if (&rec.second != m_context) {
            if (rec.second.isActiv()) {
                rec.first->msg_recv(m_my_name, {msg.begin(), msg.end()});
            }
        }
    }
}

void LoginedClient::exit()
{
    for (auto& rec: get_server().m_clients) {
        if (&rec.second != m_context) {
            rec.first->msg_recv(m_my_name, "exit from server");
        }
    }
    get_client().msg_recv("SERVER:", "See you later!");
    m_context->set_activ_false();
    m_context->set_state(new UnloginedClient(m_logger));
}

void LoginedClient::disconnect()
{
    for (auto it = get_server().m_clients.begin(); it != get_server().m_clients.end(); ++it) {
        if (it->first == &get_client()) {
            get_server().m_clients.erase(it);
        }
    }
}

void LoginedClient::echo()
{
    get_client().msg_recv("Server", "ECHO RESPONSE");
}
