/*
** BasicServer
** File description:
** Server methods
*/

#include "Server.hpp"

/// \file Server.cpp
/// \author Arthur L.
/// \brief Server methods

BasicServer::Server::Server() : _state(false), _udpSocket(_ioContext, std::bind(&Server::callBack, this, std::placeholders::_1))
{
    // launching boost
    _boostThread = std::thread(&BasicServer::Server::launchBoost, this);
    _actions["shutdown"] = std::bind(&BasicServer::Server::shutdown, this);
}

BasicServer::Server::~Server()
{ }

void BasicServer::Server::launchBoost()
{
    _ioContext.run();
}

void BasicServer::Server::start()
{
    _state = true;
    while (_state) {
        std::cout << "$> ";
        std::getline(std::cin, _input);
        if (!_input.empty())
            interpret();
    }
}

void BasicServer::Server::interpret()
{
    if (_actions.find(_input.c_str()) != _actions.end())
        _actions[_input.c_str()]();
    else
        std::cerr << "Invalid command: " << _input << std::endl;
}

void BasicServer::Server::shutdown()
{
    _state = false;
}

void BasicServer::Server::callBack(UdpSocket *socket)
{
    std::cout << "Entering Udp calback" << std::endl;
}