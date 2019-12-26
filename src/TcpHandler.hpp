/*
** BasicServer
** File description:
** TcpHandler declaration
*/

/// \file TcpHandler.hpp
/// \author Arthur L.
/// \brief declaration of TcpHandler

#pragma once

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "TcpSocket.hpp"
#include "macro.hpp"

/// \namespace BasicServer
/// \brief Used for the all BasicServer project
namespace BasicServer {

    class TcpHandler {

        public:
            /// \param io boost io_context
            /// \param fct function call after a read
            /// \brief constructor
            TcpHandler(boost::asio::io_context &io, std::function<void(TcpSocket *)> fct);
            /// \brief destructor
            ~TcpHandler();

            /// \brief Initiialize a callBack function to handle new connections
            void accept();

        private:
            /*! Boost acceptor to allow connections on server */
            boost::asio::ip::tcp::acceptor _acceptor;
            /*! callBack function send to all TcpSocket constructor */
            std::function<void(TcpSocket *)> _callBack;
            /*! vector of all connection */
            std::vector<boost::shared_ptr<TcpSocket>> _sockets;

            /// \brief Callback of Accept
            void handleAcceptance(boost::shared_ptr<TcpSocket> sock, const boost::system::error_code err);
    };
}