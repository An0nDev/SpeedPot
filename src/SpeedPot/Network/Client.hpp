#pragma once

#include <netinet/in.h>
#include <mutex>
#include <thread>
#include "Common.hpp"
#include "NetworkedRawClientConnector.hpp"
#include "../Packet/List.hpp"
#include "State.hpp"
#include "../Utils/Event.hpp"

namespace SpeedPot::Network {
    class Server;
    class Client {
        std::thread* readThread;
        void readPackets ();
        
        Utils::Event canProcess;
        Utils::Event isDoneProcessing;
        friend class Server;
        
        std::mutex isShuttingDownLock;
        bool isShuttingDown = false;
    public:
        Server & server;
        NetworkedRawClientConnector connector;
        // ^ I hate making these public, but they need to be accessible by classes derived from Packet,
        // and I can only apply friend to the base class... so we deal with the hack :/
        State state;
        sockaddr_in address;
        Client (sockaddr_in const & address, SocketFD const & fd, Server & server);
        void pause (); // call first
        void resume (); // call after pause
        ~Client ();
    };
}