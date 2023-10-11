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
    while (true) {
        std::getline(std::cin, pass);
        if (pass.size() >= 8) {
            Optional_card card = std::for_each(pass.begin(), pass.end(), Optional_card());
                if (card.get_low() && card.get_up() && card.get_special()) {
                        std::size_t hash = std::hash<std::string>{}(pass);
                        return hash;
                    }
                    std::cout << "invalid pass: try again" << std::endl;
                    pass.clear();
        }
        std::cout << "invalid pass: try again" << std::endl;
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