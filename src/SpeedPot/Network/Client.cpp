#include "Client.hpp"
#include "Server.hpp"
#include "../Utils/PointerCleaner.hpp"
#include "../Utils/ExceptionPrinter.hpp"

namespace SpeedPot::Network {
    Client::Client (sockaddr_in const & address, SocketFD const & fd, Server & server) : state (State::HANDSHAKING), address (address), connector (fd), server (server) {
        isDoneProcessing.set ();
        canProcess.set ();
        readThread = new std::thread (&Client::readPackets, this);
    }
    void Client::readPackets () {
        try {
            while (true) {
                std::cout << "reading packet length and id" << std::endl;
                DataTypes::VarIntNR packetIDAndDataLength = DataTypes::VarInt::readFrom (connector).value;
                DataTypes::VarIntNR packetID = DataTypes::VarInt::readFrom (connector).value;
        
                std::cout << "looking up packet with current state " << state << " and id " << packetID << std::endl;
                Packet::List::PacketListEntry packetListEntry;
                try {
                    packetListEntry = server.packetList.SERVERBOUND_PACKET_LIST.at (state).at (packetID);
                } catch (std::out_of_range const & exception) {
                    std::cout << "unable to find handler for given packet, probably unimplemented! rethrowing" << std::endl;
                    throw exception;
                }
                Packet::List::PointerToPacketReadFrom pointerToPacketReadFrom;
                Packet::List::PointerToPacketHandle pointerToPacketHandle;
                std::tie (pointerToPacketReadFrom, pointerToPacketHandle) = packetListEntry;
        
                Packet::Packet* readPacket = pointerToPacketReadFrom (connector);
                Utils::PointerCleaner <Packet::Packet*> readPacketPointerCleaner (readPacket);
        
                canProcess.wait ();
                isDoneProcessing.clear ();
        
                pointerToPacketHandle (readPacket, *this);
        
                std::cout << "done handling packet" << std::endl;
                isDoneProcessing.set ();
            }
        } catch (std::exception & exception) {
            Utils::ExceptionPrinter::print (exception, "Client run loop", std::cerr);
            server.deleteClient (*this);
        }
    }
    void Client::pause () {
        canProcess.clear ();
        isDoneProcessing.wait ();
    }
    void Client::resume () {
        canProcess.set ();
    }
    Client::~Client () {
        connector.close ();
        readThread->join ();
        delete readThread;
    }
}