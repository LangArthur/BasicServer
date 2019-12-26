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
            /// \param io boost io_context
            /// \param callBack function call after the socket read something
            /// \brief constructor
            UdpSocket(boost::asio::io_context &io, std::function<void(BasicServer::UdpSocket *)> callBack);
            /// \brief destructor
            ~UdpSocket();

            /// \brief get port of socket
            /// \return port socket
            int port() const { return _localEndpoint.port(); }
            /// \brief get socket's ip
            /// \return ip address in a string
            std::string ip() const { return _localEndpoint.address().to_string(); }
            /// \brief get remote socket's port
            /// \return port of remote socket. If no socket is initialized, it'll return 0
            int remotePort() const { return _senderEndpoint.port(); }
            /// \brief get ip of the sender socket
            /// \return ip address in a string. If no socket is initialized, it'll return 0.0.0.0
            std::string remoteIp() const { return _senderEndpoint.address().to_string(); }

            /// \brief initialise an asynchronous receiver
            void startAccept();
            /// \param ip ip of the destination
            /// \param port port of the targer
            /// \param data data to be send
            /// \brief send message to a client
            void write(const std::string &ip, unsigned short port, const void *data);

        private:
            /*! Local endpoint */
            boost::asio::ip::udp::endpoint _localEndpoint;
            /*! Sender endpoint */
            boost::asio::ip::udp::endpoint _senderEndpoint;
            /*! Udp socket */
            boost::asio::ip::udp::socket _socket;
            /*! Buffer containing data got from remote client */
            std::array<char, BUFFER_SIZE> _buf;
            /*! callback function */
            std::function <void(BasicServer::UdpSocket *)> _callBack;

            /// \brief internal read socket's callback
            /// It will clear the buffer
            void handleRead(const boost::system::error_code &err, const std::size_t size);
            /// \brief internal write socket's callback
            void handleWrite(const boost::system::error_code &err, const std::size_t size);
    };
}