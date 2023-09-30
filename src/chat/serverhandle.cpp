#include "serverhandle.hpp"
#include "state.hpp"

using namespace chat;

ServerHandle::ServerHandle(Server& server, IClient& client, std::ostream& logger)
: m_state(new UnloginedClient)
, m_client(client)
, m_server(server)
, m_logger(logger)
{
    m_state->set_context(this);
}

ServerHandle::~ServerHandle() noexcept
{
    delete m_state;
}

void ServerHandle::set_state(IState* state)
{
    m_state = state;
    state->set_context(this);
}

void ServerHandle::msg_accept(const std::string& msg)
{
    auto state = m_state;
    state->msg_accept(msg);
    if (state != m_state) {
        delete state;
    }
}

void ServerHandle::new_user(const std::string& nick_name, std::size_t hash)
{
    auto state = m_state;
    state->new_user(nick_name, hash);
    if (state != m_state) {
        delete state;
    }
}

void ServerHandle::login(const std::string& nick_name, std::size_t hash)
{
    auto state = m_state;
    state->login(nick_name, hash);
    if (state != m_state) {
        delete state;
    }
}

void ServerHandle::exit()
{
    auto state = m_state;
    state->exit();
    if (state != m_state) {
        delete state;
    }
}

void ServerHandle::disconnect()
{
    m_state->disconnect();
}

void ServerHandle::echo()
{
    
}