#pragma once
#include <string>

class Letter final
{
private:
    std::string m_msg {""};
public:
    std::string m_sender {"default"};
    std::string m_recipient {"defult"};

    Letter()
    {

    }

    Letter(const std::string& sender, const std::string& recepient)
    : m_msg("default")
    , m_sender(sender)
    , m_recipient(recepient)
    {

    }

    Letter(const std::string& msg)
    : m_msg(msg)
    , m_sender("default")
    , m_recipient("default")
    {

    }

    ~Letter()
    {

    }

    void set_recipient(const std::string& recipient) noexcept
    {
        m_recipient = recipient;
    }

    void set_sender(const std::string& sender)
    {
        m_sender = sender;
    }
};