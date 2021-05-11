#include "HandshakePacket.hpp"
#include "../../../../Network/Client.hpp"
#include "../../../../Network/Server.hpp"

namespace SpeedPot::Packet::Packets::Serverbound::Handshaking {
    HandshakePacket::HandshakePacket (DataTypes::VarIntNR const & protocolVersion, DataTypes::StringNR const & serverAddress, DataTypes::UnsignedShortNR const & serverPort, DataTypes::VarIntNR const & nextState)
    : protocolVersion (protocolVersion), serverAddress (serverAddress), serverPort (serverPort), nextState (nextState) {}
    const DataTypes::VarIntNR HandshakePacket::ID = 0x00;
    Packet* HandshakePacket::readFrom (Network::RawClientConnector & clientConnector) {
        using namespace DataTypes;
        return new HandshakePacket (
                VarInt::readFrom (clientConnector).value,
                String::readFrom (clientConnector).value,
                UnsignedShort::readFrom (clientConnector).value,
                VarInt::readFrom (clientConnector).value
        );
    }
    void HandshakePacket::handle (Packet* packet, Network::Client & client) {
        auto handshakePacket = (HandshakePacket*) packet;
        std::cout << "[!] handling handshake packet, contents: proto ver " << handshakePacket->protocolVersion << " (server implements " << client.server.IMPLEMENTS_PROTOCOL_VERSION << "), server addr " << handshakePacket->serverAddress << ", server port " << handshakePacket->serverPort << ", next state " << handshakePacket->nextState << std::endl;
        switch (handshakePacket->nextState) {
            case 1: {
                client.state = Network::State::STATUS;
                std::cout << "switching to next state (STATUS)" << std::endl;
                break;
            }
            case 2: {
                client.state = Network::State::LOGIN;
                std::cout << "switching to next state (LOGIN)" << std::endl;
                break;
            }
            default: {
                throw std::runtime_error ("Unknown next state (not 1 or 2)");
            }
        }
    }
}