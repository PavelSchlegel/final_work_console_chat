#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "function.hpp"
/*
class Gmock: public chat::TerminalClient
{
public:
    MOCK_METHOD(void, msg_recv, (const std::string& who, const std::string& msg), (override));
    MOCK_METHOD(void, msg_send, (), (override));
    MOCK_METHOD(void, new_user, (), (override));
    MOCK_METHOD(void, login, (), (override));
    MOCK_METHOD(void, exit, (), (override));
};

TEST(Mock, test_parser_func)
{
    // using ::testing::Return;
    Gmock M;
    EXPECT_CALL(M, msg_recv).Times(::testing::AtLeast(1));
    EXPECT_CALL(M, msg_send).Times(::testing::AtLeast(1));
    EXPECT_CALL(M, new_user).Times(::testing::AtLeast(1));
    EXPECT_CALL(M, login).Times(::testing::AtLeast(1));
    EXPECT_CALL(M, exit).Times(::testing::AtLeast(1));

    com_parser(&M);
}
*/
TEST(Func, get_nick)
{
    EXPECT_EQ(get_nick_name(), "Halford");
}