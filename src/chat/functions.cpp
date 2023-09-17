#include "functions.hpp"
#include <iostream>
#include <boost/lexical_cast.hpp>

bool is_pass_valid(const std::string& pass) noexcept
{
    return true;
}

bool is_nick_valid(const std::string& nick) noexcept
{
    bool valid_nick = true;
    for (std::size_t i = 0; i < nick.size(); ++i) {
        if (std::isalpha(nick[i])) {
            continue;
        }

        if (nick[i] == ' ') {
            continue;
        }

        valid_nick = false;
    }

    if (valid_nick) {
        return true;
    }

    return false;
}

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
            if (line.find("newuser")) {
                client->new_user();
                continue;
            }
            if (line.find("login")) {
                client->login();
                continue;
            }
            if (line.find("send")) {
                client->msg_send();
                continue;
            }
            if (line.find("exit")) {
                client->exit();
                return;
            }
        }
    }
}

std::string get_nick_name()
{
    std::cout << "Enter your nickname:" << std::endl;
    for (std::string line; std::getline(std::cin, line);) {
        if (line.empty()) {
            std::cout << "ERROR: line is empty!" << std::endl;
            continue;
        }

        if (is_nick_valid(line)) {
            return line;
        }
    }
    
    return "DEFAULT";
}

std::size_t get_pass()
{
    std::cout << "Enter your password" << std::endl;
    bool high = false;
    bool lower = false;
    bool symbol = false;
    std::size_t hash {0000};
    for (std::string pass; std::getline(std::cin, pass);) {
        if (pass.size() < 8) {
            std::cout << "ERROR: string less than 8 characters!" << '\n'
            << "try ahain!" << std::endl;
            continue;
        }
        for (std::size_t i = 0; i < pass.size(); ++i) {
            if (pass[i] == ' ') {
                high = false;
                lower = false;
                symbol = false;
                std::cout << "ERROR: space is not allowed!" << '\n'
                << "try again!" << std::endl;
                break;
            }

            if (!high) {
                if (pass[i] > 64 && pass[i] < 91) {
                    high = true;
                    continue;
                }
            }

            if (!lower) {
                if (pass[i] > 96 && pass[i] < 123) {
                    lower = true;
                    continue;
                }
            }

            if (!symbol) {
                switch (pass[i]) {
                    case '!': {
                        symbol = true;
                        break;
                    }
                    case '@': {
                        symbol = true;
                        break;
                    }
                    case '#': {
                        symbol = true;
                        break;
                    }
                    case '$': {
                        symbol = true;
                        break;
                    }
                    case '%': {
                        symbol = true;
                        break;
                    }
                    case '&': {
                        symbol = true;
                        break;
                    }
                }
            }
        }

        if (high && lower && symbol) {
            hash = std::hash<std::string>{}(pass);
            return hash;
        }
    }
    //!!!!!
    return hash;
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