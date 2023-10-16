#include "functions.hpp"

chat::TerminalClient::TerminalClient(chat::IServer* server, std::ostream& logger)
: m_server_handle(server->connect(*this))
, m_logger(logger)
, stop_flag(false)
{
    methods.push_back(std::make_pair("msg_send", &TerminalClient::msg_send));
    methods.push_back(std::make_pair("new_user", &TerminalClient::new_user));
    methods.push_back(std::make_pair("login", &TerminalClient::login));
    methods.push_back(std::make_pair("echo", &TerminalClient::echo));
    methods.push_back(std::make_pair("exit", &TerminalClient::exit));
    methods.push_back(std::make_pair("info", &TerminalClient::info));
    methods.push_back(std::make_pair("close", &TerminalClient::close));

    std::string line;
    while ( ! stop_flag ) {
        std::getline(std::cin, line);
        this->go(line);
        if ( ! line.empty()) {
            std::cout << line << std::endl;
        }
    }
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

void chat::TerminalClient::close()
{
    stop_flag = true;
}

void chat::TerminalClient::go(std::string& command)
{
    if (std::isdigit(command[0])) {
        int pos = std::stoi(command);
        if (pos > methods.size()) {
            command.clear();
            return;
        }
        (*this.*(methods[pos].second))();
        command.clear();
        return;
    }

    for (int i = 0; i < methods.size(); ++i) {
        if (methods[i].first == command) {
            (*this.*(methods[i].second))();
            command.clear();
            return;
        }
    }
    command.clear();
    command = "UNKNOW COMMAND";
}

void chat::TerminalClient::msg_recv(const std::string& who, const std::string& msg)
{
    std::cout << "\033[32m" <<  who << ":\033[0m" << '\n';
    std::cout << '\t' << msg << std::endl;
}

void chat::TerminalClient::info()
{
    for (int i = 0; i < methods.size(); ++i) {
        std::cout << "\033[32m" << i << "\033[0m" << " " << methods[i].first << std::endl;
    }
}