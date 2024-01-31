#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include "pch.h"

namespace ip = boost::asio::ip;

class ConnectionHandler : public boost::enable_shared_from_this<ConnectionHandler>
{
public:
    typedef boost::shared_ptr<ConnectionHandler> pointer;

    ConnectionHandler(boost::asio::io_context& ioContext) : socket_(ioContext){}

    static pointer create(boost::asio::io_context& ioContext);

    ip::tcp::socket& socket();

    void start();

protected:
    inline bool validateData(const std::string &data) const noexcept;
    
private:
    void handleRead(const boost::system::error_code& err, std::size_t bytes_transferred);

    ip::tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
};

#endif // CONNECTION_HANDLER_H