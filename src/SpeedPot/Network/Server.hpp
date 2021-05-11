#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <mutex>
#include <vector>
#include <thread>

#include "Common.hpp"
#include "Client.hpp"
#include "../Packet/List.hpp"
#include "../Utils/SingleNotifyEvent.hpp"

namespace SpeedPot::Network {
    class Server {
        SocketFD serverFD;

        std::mutex listeningVarsLock;
        bool listening = false;
        bool listenIsThreaded = false;

        std::mutex clientsLock;
        std::vector <Client*> clients;

        Packet::List packetList;
        friend class Client;
        
        Utils::SingleNotifyEvent deleteReadyEvent;
        Utils::Event deleteSubmissionReadyEvent;
        Client* target_;
        std::thread* clientDeletionThread = nullptr;
        bool clientDeletionThreadIsShuttingDown = false;
        void deleteClient_ ();
        
        bool isShutDown = false;
    public:
        static const DataTypes::VarIntNR IMPLEMENTS_PROTOCOL_VERSION;
        static const DataTypes::StringNR VERSION_NAME;
        
        std::string description;
        Server (uint16_t const & port = 25565, std::string const & description = "\u00A7l\u00A7fSpeedPot server");
        void listen (int const & backlog);
        void deleteClient (Client & target);
        void shutdown ();
        ~Server ();
    };
}
