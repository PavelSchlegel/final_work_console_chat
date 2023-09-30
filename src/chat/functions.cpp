#include "functions.hpp"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "./optional_card/optional_card.hpp"

void com_parser(chat::TerminalClient *client) noexcept
{
    std::cout << "Welcom to console chat!" << std::endl;
    std::cout << "Enter your command:" << std::endl;
    while (true) {
        for (std::string line; std::getline(std::cin, line);) {
            if (line.empty()) {
                std::cout << std::endl;
                continue;
            }
            if (line.find("echo") != std::string::npos) {
                client->echo();
                continue;
            }
            if (line.find("newuser") != std::string::npos) {
                client->new_user();
                continue;
            }
            if (line.find("login") != std::string::npos) {
                client->login();
                continue;
            }
            if (line.find("send") != std::string::npos) {
                client->msg_send();
                continue;
            }
            if (line.find("exit") != std::string::npos) {
                client->exit();
                return;
            }
        }
    }
}

std::string get_nick_name()
{
    std::cout << "Enter your nickname:" << std::endl;
    std::string nick;
    while (1) {
        std::getline(std::cin, nick);
        for (std::size_t i = 0; i < nick.size(); ++i) {
            if ( ! (std::isalpha(nick[i]) || nick[i] == ' ') ) {
                break;
            }
        }
        return nick;
    }
}

std::size_t get_user_password()
{
    std::cout << "Enter your password:" << std::endl;
    std::string pass;
    while (1) {
        std::getline(std::cin, pass);
        if (pass.size() >= 8) {
            Optional_card card = std::for_each(pass.begin(), pass.end(), Optional_card());
                if (card.get_low() && card.get_up() && card.get_special()) {
                        std::size_t hash = std::hash<std::string>{}(pass);
                        return hash;
                    }
                    pass.clear();
        }
        pass.clear();
    }
}

std::string get_msg()
{
    std::string msg;
    std::cout << "Your message:" << std::endl;
    std::getline(std::cin, msg);
    return msg;
}

std::string get_recipient()
{
    std::string recip;
    std::cout << "Recipient:" << std::endl;
    std::getline(std::cin, recip);
    return recip;
}