/*
** BasicServer
** File description:
** TcpHandler methods
*/

/// \file TcpHandler.cpp
/// \author Arthur L.
/// \brief TcpHandler methods

#include "TcpHandler.hpp"

BasicServer::TcpHandler::TcpHandler(boost::asio::io_context &io, std::function<void(TcpSocket *)> fct) :
    _endpoint(boost::asio::ip::tcp::v4(), TCP_SERVER_PORT), _acceptor(io, _endpoint), _callBack(fct)
{
    accept();
}

BasicServer::TcpHandler::~TcpHandler()
{
}

void BasicServer::TcpHandler::accept()
{
    boost::shared_ptr<TcpSocket> waitingConnection = boost::make_shared<TcpSocket>(_acceptor.get_executor().context(), _callBack);
    _acceptor.async_accept(waitingConnection->getSocket(),
        boost::bind(&TcpHandler::handleAcceptance, this, waitingConnection, boost::asio::placeholders::error));
}

void BasicServer::TcpHandler::handleAcceptance(boost::shared_ptr<TcpSocket> sock, const boost::system::error_code err)
{
    if (err) {
        std::cout << err.category().name() << " : " << err.message() << std::endl;
    } else {
        sock->start();
        _sockets.push_back(sock);
    }

}

void BasicServer::TcpHandler::dispConnections()
{
    for (auto &i : _sockets) {
        if (i->state())
            std::cout << "Connected to " << i->remoteIp() << " on port: " << i->remotePort() << std::endl;
    }
}