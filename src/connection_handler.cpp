#include "connection_handler.h"

ConnectionHandler::pointer ConnectionHandler::create(boost::asio::io_context& ioContext)
{
    return pointer(new ConnectionHandler(ioContext));
}

ip::tcp::socket& ConnectionHandler::socket()
{
    return socket_;
}

void ConnectionHandler::start()
{
    socket_.async_read_some(boost::asio::buffer(data_, max_length), boost::bind(&ConnectionHandler::handleRead,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

inline bool ConnectionHandler::validateData(const std::string &data) const noexcept
{
    return (data.length() > 2) && (std::stoi(data) % 32 == 0);
}

void ConnectionHandler::handleRead(const boost::system::error_code& ec, std::size_t bytes_transferred)
{
    if(!ec){
        std::string preparedData = std::string(data_, bytes_transferred);
        if(validateData(preparedData))
            std::cout << "Received data: " << preparedData << std::endl;
        else
            std::cerr << "Error: invalid data" << std::endl;
        start();
    }else{
        std::cout << "Error during handle reading" << std::endl;
        socket_.close();
    }
}