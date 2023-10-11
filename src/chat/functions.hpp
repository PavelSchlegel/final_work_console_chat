#pragma once
#include <iostream>
#include <string>
#include "terminal_client.hpp"

#define COLOR_RED "\033[1;31m"
#define COLOR_GRUN "\033[32m"
#define COLOR_RESET "\033[0m"

void start();
void star_print();
std::string get_nick_name();
std::size_t get_user_password();
std::string get_msg();
std::string get_recipient();