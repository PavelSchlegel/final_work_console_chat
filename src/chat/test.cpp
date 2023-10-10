#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "functions.hpp"
#include "net_client.hpp"

// class Mock: chat::TerminalClient
// {
// public:
// // caller сторона клиента
//     MOCK_METHOD(void, echo, ());
//     MOCK_METHOD(void, login, ());
//     MOCK_METHOD(void, exit, ());
//     MOCK_METHOD(void, info, ());
//     MOCK_METHOD(void, new_user, ());
//     MOCK_METHOD(void, go, (const std::string& go));
// };

// TEST(Mock, call_terminal_client)
// {
//     using::testing::Return;
//     Mock terminal_cllient;
//     EXPECT_CALL(terminal_cllient, echo).Times(::testing::AtLeast(1));
//     EXPECT_CALL(terminal_cllient, login).Times(::testing::AtLeast(1));
//     EXPECT_CALL(terminal_cllient, exit).Times(::testing::AtLeast(1));
//     EXPECT_CALL(terminal_cllient, info).Times(::testing::AtLeast(1));
//     EXPECT_CALL(terminal_cllient, new_user).Times(::testing::AtLeast(1));
//     EXPECT_CALL(terminal_cllient, go).Times(::testing::AtLeast(5));

//     terminal_cllient.go("echo");
//     terminal_cllient.go("login");
//     terminal_cllient.go("new_user");
//     terminal_cllient.go("exit");
//     terminal_cllient.go("info");
// }