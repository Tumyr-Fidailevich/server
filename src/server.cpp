#include "server.h"

Server::Server(boost::asio::io_context& ioContext, const short port) :
ioContext_(ioContext), acceptor_(ioContext, ip::tcp::endpoint(ip::tcp::v4(), port))
{
    std::cout << "Server started" << std::endl;
}

void Server::run()
{
    auto connection = ConnectionHandler::create(ioContext_);
    
    acceptor_.async_accept(connection->socket(),
        boost::bind(&Server::handleAccept, this, connection, boost::asio::placeholders::error));
}

void Server::handleAccept(ConnectionHandler::pointer connection, const boost::system::error_code& ec)
{
    if (!ec) {
        std::cout << "Starting new connection.. " << std::endl;
        connection->start();
    }else
    {
        std::cerr << "User disconnected from the server" << std::endl;
    }
    run();
}