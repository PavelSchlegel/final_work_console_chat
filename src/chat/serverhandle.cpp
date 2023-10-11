#include "serverhandle.hpp"
#include "state.hpp"

using namespace chat;

ServerHandle::ServerHandle(Server& server, IClient& client, std::ostream& logger)
: m_state(new UnloginedClient(logger))
, is_activ(false)
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

void ServerHandle::msg_accept(std::string_view msg)
{
    m_logger << "SERVER_HANDLE: ";
    auto state = m_state;
    state->msg_accept(msg);
    if (state != m_state) {
        delete state;
    }
}

void ServerHandle::new_user(std::string_view nick_name, std::size_t hash)
{
    m_logger << "SERVER_HANDLE: ";
    auto state = m_state;
    state->new_user(nick_name, hash);
    if (state != m_state) {
        delete state;
    }
}

void ServerHandle::login(std::string_view nick_name, std::size_t hash)
{
    m_logger << "SERVER_HANDLE: ";
    auto state = m_state;
    state->login(nick_name, hash);
    if (state != m_state) {
        delete state;
    }
}

void ServerHandle::exit()
{
    m_logger << "SERVER_HANDLE: ";
    auto state = m_state;
    state->exit();
    if (state != m_state) {
        delete state;
    }
}

void ServerHandle::disconnect()
{
    m_logger << "SERVER_HANDLE: ";
    auto state = m_state;
    state->disconnect();
    if (state != m_state) {
        delete state;
    }
}

void ServerHandle::echo()
{
    m_logger << "SERVER_HANDLE: ";
    auto state = m_state;
    state->echo();
    if (state != m_state) {
        delete state;
    }
}

bool ServerHandle::isActiv()
{
    return is_activ;
}

void ServerHandle::set_activ_true()
{
    this->is_activ = true;
    // is_activ = true;
}

void ServerHandle::set_activ_false()
{
    is_activ = false;
}