#include "functions.hpp"

void chat::TerminalClient::msg_send()
{
    m_server_handle.msg_accept(get_msg());
}

void chat::TerminalClient::new_user()
{
    m_server_handle.new_user(get_nick_name(), get_user_password());
}

void chat::TerminalClient::login()
{
    m_server_handle.login(get_nick_name(), get_user_password());
}