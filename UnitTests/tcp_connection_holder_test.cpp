#include <gtest/gtest.h>

#include "tcp_connection_holder.h"


class TcpConnectionHolderTest: public ::testing::TestWithParam<int>
{ };

TEST_P(TcpConnectionHolderTest, Basic)
{
    const int socket = GetParam();
    std::cout << "Testing with parametr: " << socket << std::endl;
    try
    {
        TcpConnectionHolder tcpConnectionHolder(socket);
        ASSERT_EQ(socket, 1) << socket;
    }
    catch (const std::runtime_error& err)
    {
        ASSERT_EQ(socket, -1) << err.what() << "\nsocket: " << socket;
    }
}

INSTANTIATE_TEST_CASE_P(Test, TcpConnectionHolderTest, testing::Values(-1, 1));
