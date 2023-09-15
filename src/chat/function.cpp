#include "function.hpp"
#include <iostream>

std::string get_nick_name()
{
    std::cout << "Enter your nickname:" << std::endl;
    while (true) {
        bool valid_pass = false;
        std::string pass;
        std::getline(std::cin, pass);
        for (std::size_t i = 0; i < pass.size() && !valid_pass; ++i) {
            if (std::isalpha(pass[i])) {
                continue;
            }

            if (pass[i] == ' ') {
                continue;
            }

            valid_pass = true;
        }
        if (!valid_pass) {
            return pass;
        }
    }
}

std::size_t get_pass()
{
    std::string pass;
    std::cout << "Enter you password" << std::endl;
    std::getline(std::cin, pass);
    std::size_t pass_hash = std::stoi(pass);
    return pass_hash;
}

std::string get_msg()
{
    std::string msg;
    std::cout << "Enter your message:" << std::endl;
    std::getline(std::cin, msg);
    return msg;
}

std::string get_recipient()
{
    std::string recip;
    std::cout << "Enter who is recipient?" << std::endl;
    std::getline(std::cin, recip);
    return recip;
}