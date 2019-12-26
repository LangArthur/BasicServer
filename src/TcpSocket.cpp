/*
** BasicServer
** File description:
** TcpSocket declaration
*/

/// \file TcpSocket.cpp
/// \author Arthur L.
/// \brief TcpSocket methods

#include "TcpSocket.hpp"

BasicServer::TcpSocket::TcpSocket(boost::asio::io_context &io, std::function<void(TcpSocket *)> fct) : _isConnected(true), _socket(io), _callBack(fct)
{ }

BasicServer::TcpSocket::~TcpSocket()
{ }

void BasicServer::TcpSocket::start()
{
    read();
}

// tester si le start est vraiment nécessaire

void BasicServer::TcpSocket::read()
{
    _socket.async_read_some(boost::asio::buffer(_buf), boost::bind(&TcpSocket::handleRead,
        this ,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void BasicServer::TcpSocket::handleRead(const boost::system::error_code &err, [[maybe_unused]] const size_t size)
{
    if (err) {
        disconnect(err);
    }
    else {
        _localEndPoint = _socket.local_endpoint();
        _callBack(this);
        _buf.fill(0);
        read();
    }
}

void BasicServer::TcpSocket::write(void *data)
{
    _socket.async_write_some(boost::asio::buffer(data, sizeof(*(static_cast<const char *>(data)))), boost::bind(&TcpSocket::handleWrite, 
        this , boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void BasicServer::TcpSocket::handleWrite(const boost::system::error_code &err, [[maybe_unused]] const size_t size)
{
    if (err) {
        disconnect(err);
    }
}

void BasicServer::TcpSocket::disconnect(const boost::system::error_code &err)
{
    if (err.value() != 2) {
        std::cerr << "An error occured: " << err.message() << std::endl;
    }
    std::cerr << "Socket is disconnected" << std::endl;
    _isConnected = false;
    _socket.close();
}