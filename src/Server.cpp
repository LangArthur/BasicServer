/*
** BasicServer
** File description:
** Server methods
*/

#include "Server.hpp"

/// \file Server.cpp
/// \author Arthur L.
/// \brief Server methods

BasicServer::Server::Server() : _state(false),
    _tcpHandler(_ioContext, std::bind(&Server::tcpCallBack, this, std::placeholders::_1)),
    _udpSocket(_ioContext, std::bind(&Server::udpCallBack, this, std::placeholders::_1))
{
    // launching boost
    _boostThread = std::thread(&BasicServer::Server::launchBoost, this);
    _actions["shutdown"] = std::bind(&BasicServer::Server::shutdown, this);
    _actions["ports"] = std::bind(&BasicServer::Server::displayPort, this);
}

BasicServer::Server::~Server()
{
    _ioContext.stop();
    _boostThread.join();
}

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
    if (_actions.find(_input) != _actions.end())
        _actions[_input]();
    else
        std::cerr << "Invalid command: " << _input << std::endl;
}

void BasicServer::Server::shutdown()
{
    _state = false;
}

void BasicServer::Server::udpCallBack([[maybe_unused]]UdpSocket *socket)
{
    std::cout << "Entering udp calback" << std::endl;
}

void BasicServer::Server::tcpCallBack([[maybe_unused]]TcpSocket *socket)
{
    std::cout << "Entering tcp calback" << std::endl;
}

void BasicServer::Server::displayPort()
{
    std::cout << "Udp local port: " << _udpSocket.port() << std::endl;
    std::cout << "Tcp local port: " << _tcpHandler.port() << std::endl;
}