#include <sstream>
#include "Server.hpp"

namespace SpeedPot::Network {
    const DataTypes::VarIntNR Server::IMPLEMENTS_PROTOCOL_VERSION = 47;
    const DataTypes::StringNR Server::VERSION_NAME = "1.8.9";
    void Server::deleteClient_ () {
        while (true) {
            deleteReadyEvent.wait ();
            deleteReadyEvent.clear ();
            if (clientDeletionThreadIsShuttingDown) {
                break;
            }
            
            Client* target = target_;
            {
                std::lock_guard <std::mutex> clientsLockGuard (clientsLock);
                for (Client* client : clients) { // pause all (other) clients first so we can ensure no work is being done using the target
                    if (client != target) client->pause (); // will wait until client is paused
                }
                // remove the specified client
                std::vector <Client*>::iterator clientsIterator;
                for (clientsIterator = clients.begin (); clientsIterator != clients.end ();) {
                    if (*clientsIterator == target) {
                        delete *clientsIterator;
                        clientsIterator = clients.erase (clientsIterator);
                    } else {
                        clientsIterator++;
                    }
                } // base from https://stackoverflow.com/a/55523963/5037905
                
                for (Client* client : clients) { // resume all clients
                    client->resume ();
                }
            }
            
            deleteSubmissionReadyEvent.set ();
        }
    }
    void Server::deleteClient (Client & target) {
        {
            std::lock_guard <std::mutex> isShuttingDownLockGuard (target.isShuttingDownLock);
            if (target.isShuttingDown) {
                return;
            }
            target.isShuttingDown = true;
        }
        
        deleteSubmissionReadyEvent.wait ();
        deleteSubmissionReadyEvent.clear ();
        target_ = &target;
        deleteReadyEvent.set ();
    }
    Server::Server (uint16_t const & port, std::string const & description) : description (description) {
        int domain = AF_INET;
        serverFD = socket (domain, SOCK_STREAM, IPPROTO_TCP);
        if (serverFD == -1) throw std::system_error (std::error_code (errno, std::system_category ()), "Unable to create server socket");

        sockaddr_in internetAddress;
        internetAddress.sin_family = domain;
        internetAddress.sin_port = htons (port);
        internetAddress.sin_addr.s_addr = htonl (INADDR_ANY);
        int bindResult = bind (serverFD, (sockaddr*) &internetAddress, sizeof (internetAddress));
        if (bindResult == -1) throw std::system_error (std::error_code (errno, std::system_category ()), "Unable to bind server socket to port");
        
        deleteSubmissionReadyEvent.set ();
        clientDeletionThread = new std::thread (&Server::deleteClient_, this);
    }

    void Server::listen (const int & backlog) {
        {
            std::lock_guard <std::mutex> listeningVarsLockGuard (listeningVarsLock);
            listening = true;
            listenIsThreaded = false;
        }

        int listenResult = ::listen (serverFD, backlog);
        if (listenResult == -1) throw std::system_error (std::error_code (errno, std::system_category ()), "Unable to listen on server socket");
        int clientCount = 0;
        while (true) {
            sockaddr_in clientAddress {};
            socklen_t clientAddressSize = sizeof (clientAddress);
            SocketFD clientFD = accept (serverFD, (sockaddr*) &clientAddress, &clientAddressSize);
            if (clientFD == -1) {
                if (errno == EINVAL) break; // Socket closed (server is shutting down)
                throw std::system_error (std::error_code (errno, std::system_category ()), "Unable to accept client socket");
            }

            {
                std::lock_guard <std::mutex> clientsLockGuard (clientsLock);
                auto* newClient = new Client (clientAddress, clientFD, *this);
                clients.push_back (newClient);
            }
        }
    }
    
    void Server::shutdown () {
        if (isShutDown) return;
        ::shutdown (serverFD, SHUT_RDWR);
        close (serverFD);
        
        isShutDown = true;
    }
    
    Server::~Server () {
        shutdown ();
        
        std::vector <Client*> clientsToDelete;
        {
            std::lock_guard <std::mutex> clientsLockGuard (clientsLock);
            for (Client* client : clients) {
                clientsToDelete.push_back (client);
            }
        }
        for (Client* client : clientsToDelete) {
            deleteClient (*client);
        }
        
        deleteSubmissionReadyEvent.wait ();
        deleteSubmissionReadyEvent.clear ();
        clientDeletionThreadIsShuttingDown = true;
        deleteReadyEvent.set ();
        clientDeletionThread->join ();
        delete clientDeletionThread;
    };
}