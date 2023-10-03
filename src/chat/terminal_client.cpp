#include "functions.hpp"

chat::TerminalClient::TerminalClient(chat::IServer* server)
: m_server_handle(server->connect(*this))
{
    methods.push_back(std::make_pair("msg_send", &TerminalClient::msg_send));
    methods.push_back(std::make_pair("new_user", &TerminalClient::new_user));
    methods.push_back(std::make_pair("login", &TerminalClient::login));
    methods.push_back(std::make_pair("echo", &TerminalClient::echo));
    methods.push_back(std::make_pair("exit", &TerminalClient::exit));
    methods.push_back(std::make_pair("info", &TerminalClient::info));
}

chat::TerminalClient::~TerminalClient()
{
    m_server_handle.disconnect();
}

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

void chat::TerminalClient::echo()
{
    m_server_handle.echo();
}

void chat::TerminalClient::exit()
{
    m_server_handle.exit();
}

void chat::TerminalClient::go(const std::string& method)
{
    if (std::isdigit(method[0])) {
        int pos = std::stoi(method);
        if (pos > methods.size()) {
            return;
        }
        (*this.*(methods[pos].second))();
        return;
    }

    for (int i = 0; i < methods.size(); ++i) {
        if (methods[i].first == method) {
            // std::cout << "I have " << method << std::endl;
            (*this.*(methods[i].second))();
            return;
        }
    }
}

void chat::TerminalClient::msg_recv(const std::string& who, const std::string& msg)
{
    std::cout << who << ":" << '\n';
    std::cout << msg << std::endl;
}

void chat::TerminalClient::info()
{
    for (int i = 0; i < methods.size(); ++i) {
        std::cout << i << " " << methods[i].first << std::endl;
    }
}