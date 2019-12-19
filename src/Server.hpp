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
#include <boost/asio.hpp>

/// \namespace BasicServer
/// \brief Used for the all BasicServer project
namespace BasicServer {

    class Server {

        public:
            Server();
            ~Server();

        private:
                /*! Boost contexte */
                boost::asio::io_context _ioContext;
                /*! Thread for running boost */
                std::thread _boostThread;
    };
}