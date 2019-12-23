/*
** BasicServer
** File description:
** UdpSocket declaration
*/

/// \file UdpSocket.hpp
/// \author Arthur L.
/// \brief declaration of UdpSocket

#pragma once

#include <array>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "macro.hpp"

/// \namespace BasicServer
/// \brief Used for the all BasicServer project
namespace BasicServer {

    class UdpSocket {

        public:
            UdpSocket(boost::asio::io_context &io, std::function<void(BasicServer::UdpSocket *)> callBack);
            ~UdpSocket();

            void startAccept();
            void write(const std::string &ip, const void *data, unsigned short port);
            void handleRead(const std::size_t size);
            void handleWrite(const std::size_t size);

        private:
            /*! Connection endpoint */
            boost::asio::ip::udp::endpoint _endpoint;
            /*! Udp socket */
            boost::asio::ip::udp::socket _socket;
            /*! Buffer containing data got from remote client */
            std::array<char, BUFFER_SIZE> _buf;
            /*! callback function */
            std::function <void(BasicServer::UdpSocket *)> _callBack;

    };
}