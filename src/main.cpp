#include <csignal>
#include "server.h"

const short PORT = 1234;

void signalHandler(int signum) {
    std::cout << "Shutdown server" << std::endl;
    exit(signum);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "RU");
    try
    {
        boost::asio::io_context ioContext;
        Server server(ioContext, PORT);
        server.run();

        std::signal(SIGINT, signalHandler);

        ioContext.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error during running server" << std::endl;
    }
    
    return 0;
}