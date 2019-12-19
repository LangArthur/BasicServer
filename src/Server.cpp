/*
** BasicServer
** File description:
** Server methods
*/

#include "Server.hpp"

/// \file Server.cpp
/// \author Arthur L.
/// \brief Server methods

BasicServer::Server::Server()
{
    _boostThread = std::thread(&Server::Server::launchBoost, this);
    // launching boost
}

BasicServer::Server::~Server()
{ }
