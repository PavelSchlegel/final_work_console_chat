#pragma once
#include <iostream>
#include <string>
#include "terminal_client.hpp"

void com_parser(chat::TerminalClient* client) noexcept;
bool is_pass_valid(const std::string& pass) noexcept;
bool is_nick_valid(const std::string& nick) noexcept;
std::string get_nick_name();
std::size_t get_pass();
std::string get_msg();
std::string get_recipient();