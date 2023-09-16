#pragma once
#include <iostream>
#include <string>
#include "iclient.hpp"

void com_parser(chat::IClient* client) noexcept;
std::string get_nick_name();
std::size_t get_pass();
std::string get_msg();
std::string get_recipient();