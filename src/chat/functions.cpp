#include "functions.hpp"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "./optional_card/optional_card.hpp"
#include <sys/utsname.h>

void star_print()
{
    std::cout << "*****************" << std::endl;
}

void start()
{
    struct utsname utsname;
    uname(&utsname);
    std::cout << "OS: " << utsname.sysname << std::endl;
    std::cout << "Host: " << utsname.nodename << std::endl;
}

std::string get_nick_name()
{
    std::cout << COLOR_GRUN << "Enter your nickname:" << COLOR_RESET << " ";
    std::string nick;
    while (1) {
        std::getline(std::cin, nick);
        for (std::size_t i = 0; i < nick.size(); ++i) {
            if ( ! (std::isalpha(nick[i]) || nick[i] == ' ') ) {
                std::cout << COLOR_GRUN << "invalid nick: try again" << COLOR_RESET << std::endl;
                break;
            }
        }
        return nick;
    }
}

std::size_t get_user_password()
{
    std::cout << COLOR_GRUN << "Enter your password:" << COLOR_RESET << " ";
    std::string pass;
    while (true) {
        std::getline(std::cin, pass);
        if (pass.size() >= 8) {
            Optional_card card = std::for_each(pass.begin(), pass.end(), Optional_card());
                if (card.get_low() && card.get_up() && card.get_special()) {
                        std::size_t hash = std::hash<std::string>{}(pass);
                        return hash;
                    }
                    std::cout << COLOR_GRUN << "invalid pass: try again" << COLOR_RESET << std::endl;
                    pass.clear();
                    continue;
        }
        std::cout << COLOR_GRUN << "invalid pass: try again" << COLOR_RESET << std::endl;
        pass.clear();
    }
}

std::string get_msg()
{
    std::string msg;
    std::cout << COLOR_GRUN  << "Your:" << COLOR_RESET << '\n' << '\t';
    std::getline(std::cin, msg);
    return msg;
}

std::string get_recipient()
{
    std::string recip;
    std::cout << COLOR_GRUN  << "Recipient:" << COLOR_RESET << " ";
    std::getline(std::cin, recip);
    return recip;
}