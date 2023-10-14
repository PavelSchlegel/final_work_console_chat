#pragma once
#include <iostream>
#include <string>
#include "terminal_client.hpp"
#include <chat/cout_color.hpp>

void start();
void star_print();
std::string get_nick_name();
std::size_t get_user_password();
std::string get_msg();
std::string get_recipient();