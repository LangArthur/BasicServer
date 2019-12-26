/*
** BasicServer
** File description:
** Server declaration
*/

/// \file BasicServer.hpp
/// \author Arthur L.
/// \brief declaration of BasicServer

#pragma once

#include <thread>
#include <unordered_map>
#include <iostream>

#include <boost/asio.hpp>

#include "UdpSocket.hpp"
#include "TcpHandler.hpp"

/// \namespace BasicServer
/// \brief Used for the all BasicServer project
namespace BasicServer {

    class Server {

        public:
            /// \brief simple constructor
            Server();
            ~Server();

            /// \brief get server state
            /// \return bool with server state
            bool state() { return _state; }

            /// \brief start the server
            void start();
            /// \brief shutdown the server
            void shutdown();

        private:
            /*! Boost contexte */
            boost::asio::io_context _ioContext;
            /*! Thread for running boost */
            std::thread _boostThread;
            /*! state of the server */
            bool _state;
            /*! input from internal shell */
            std::string _input;
            /*! all functions executable from the internal shell */
            std::unordered_map<std::string, std::function<void(void)>> _actions;
            /*! handler for all tcp socket */
            TcpHandler _tcpHandler;
            /*! server's udp socket */
            UdpSocket _udpSocket;

            /// \brief interpret the internal shell input
            void interpret();
            /// \brief launch boost library
            void launchBoost();
            /// \param socket pointer to the concerned udp socket
            /// \brief socket callBack
            void udpCallBack(UdpSocket *socket);
            /// \param socket pointer to the concerned tcp socket
            /// \brief socket callBack
            void tcpCallBack(TcpSocket *socket);
            /// \brief display all current port
            void displayPort();
    };
}