/*
** BasicServer
** File description:
** UdpSocket methods
*/

/// \file UdpSocket.cpp
/// \author Arthur L.
/// \brief UdpSocket methods

#include "UdpSocket.hpp"

BasicServer::UdpSocket::UdpSocket(boost::asio::io_context &io, std::function<void(BasicServer::UdpSocket *)> callBack) :
    _localEndpoint(boost::asio::ip::udp::v4(), 0), _socket(io, _localEndpoint), _callBack(callBack)
{
    _localEndpoint = _socket.local_endpoint();
    startAccept();
}

BasicServer::UdpSocket::~UdpSocket()
{ }

void BasicServer::UdpSocket::startAccept()
{
    _socket.async_receive_from(boost::asio::buffer(_buf), _senderEndpoint,
        boost::bind(&UdpSocket::handleRead, this, boost::asio::placeholders::bytes_transferred, boost::asio::placeholders::error));
}

void BasicServer::UdpSocket::write(const std::string &ip, unsigned short port, const void *data)
{
    boost::asio::ip::udp::endpoint dest(boost::asio::ip::address::from_string(ip.data()), port);
    _socket.async_send_to(boost::asio::buffer(data, sizeof(*(static_cast<const char *>(data)))), dest,
        boost::bind(&UdpSocket::handleWrite, this, boost::asio::placeholders::bytes_transferred, boost::asio::placeholders::error));
}[[maybe_unused]]

void BasicServer::UdpSocket::handleRead([[maybe_unused]]const std::size_t size, const boost::system::error_code &err)
{
    if (err)
        std::cerr << err.category().name() << " : " << err.message() << std::endl;
    else {
        _callBack(this);
        _buf.fill(0);
    }
    startAccept();
}

void BasicServer::UdpSocket::handleWrite([[maybe_unused]]const std::size_t size, const boost::system::error_code &err)
{
    if (err)
        std::cerr << err.category().name() << " : " << err.message() << std::endl;
}