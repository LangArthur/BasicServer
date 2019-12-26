/*
** BasicServer
** File description:
** TcpSocket declaration
*/

/// \file TcpSocket.hpp
/// \author Arthur L.
/// \brief declaration of TcpSocket

#pragma once

#include <array>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "macro.hpp"

/// \namespace BasicServer
/// \brief Used for the all BasicServer project
namespace BasicServer {

    class TcpSocket {
        public:
            /// \brief constructor
            TcpSocket(boost::asio::io_context &io, std::function<void(TcpSocket *)> fct);
            /// \brief destructor
            ~TcpSocket();

            /// \brief get socket state
            /// \return True or false if the socket is alive or not
            bool state() const { return _isConnected; }
            /// \brief get socket state
            /// \return reference on the boost tcp socket
            boost::asio::ip::tcp::socket &getSocket() { return _socket; }

            /// \brief start the socket for it be able to read data
            void start();
            /// \brief launch an async read
            void read();
            /// \brief launch an async write
            void write(void *data);

        private:
            bool _isConnected;
            /*! local endpoint */
            boost::asio::ip::tcp::endpoint _localEndPoint;
            /*! client endpoint */
            boost::asio::ip::tcp::endpoint _remoteEndPoint;
            /*! tcp socket */
            boost::asio::ip::tcp::socket _socket;
            /*! buffer of the socket */
            std::array<char, BUFFER_SIZE> _buf;
            /*! function call after reading */
            std::function<void(TcpSocket *)> _callBack;

            /// \param err if an error occured
            /// \param size size of reading bytes
            /// \brief callBack of the async write
            void handleWrite(const boost::system::error_code &err, [[maybe_unused]] const size_t size);
            /// \param err if an error occured
            /// \param size size of reading bytes
            /// \brief callBack of the async read
            void handleRead(const boost::system::error_code &err, [[maybe_unused]] const size_t size);
            /// \param err if an error occured
            /// \brief disconnect the socket
            void disconnect(const boost::system::error_code &err);
    };
}