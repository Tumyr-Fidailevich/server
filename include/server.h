#ifndef SERVER_H
#define SERVER_H

#include "pch.h"
#include "connection_handler.h"

namespace ip = boost::asio::ip;

class Server
{
public:
    Server(boost::asio::io_context& ioContext, const short port);

    void run();

    void handleAccept(ConnectionHandler::pointer connection, const boost::system::error_code& err);

private:
    ip::tcp::acceptor acceptor_;
    boost::asio::io_context& ioContext_;
};

#endif // SERVER_H