#include "function.hpp"
#include <iostream>

std::string get_nick_name()
{
    std::string nick;
    std::cout << "Enter you nickname:" << std::endl;
    std::getline(std::cin, nick);
    return nick;
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