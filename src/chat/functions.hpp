#pragma once
#include <iostream>
#include <string>
#include "terminal_client.hpp"

void com_parser(chat::TerminalClient* client) noexcept;
std::string get_nick_name();
std::size_t get_user_password();
std::string get_msg();
std::string get_recipient();