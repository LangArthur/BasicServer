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
    _endpoint(boost::asio::ip::udp::v4(), 0), _socket(io, _endpoint), _callBack(callBack)
{
    startAccept();
}

BasicServer::UdpSocket::~UdpSocket()
{ }

void BasicServer::UdpSocket::startAccept()
{
    _socket.async_receive_from(boost::asio::buffer(_buf), _endpoint,
        boost::bind(&UdpSocket::handleRead, this, boost::asio::placeholders::bytes_transferred));
}

void BasicServer::UdpSocket::write(const std::string &ip, const void *data, unsigned short port)
{
    boost::asio::ip::udp::endpoint dest(boost::asio::ip::address::from_string(ip.data()), port);
    _socket.async_send_to(boost::asio::buffer(data, sizeof(*(static_cast<const char *>(data)))), dest, 
        boost::bind(&UdpSocket::handleWrite, this, boost::asio::placeholders::bytes_transferred));
}

void BasicServer::UdpSocket::handleRead([[maybe_unused]]const std::size_t size)
{
    std::cout << "Read " << size << " bytes" << std::endl;
}

void BasicServer::UdpSocket::handleWrite([[maybe_unused]]const std::size_t size)
{
    std::cout << "Write " << size << " bytes" << std::endl;
}