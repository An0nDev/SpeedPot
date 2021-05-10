#pragma once

#include "../../../Base.hpp"
#include "../../../../DataTypes/Natives.hpp"

namespace SpeedPot::Packet::Packets {
    class HandshakePacket : public Packet {
        DataTypes::VarIntNR protocolVersion;
        DataTypes::StringNR serverAddress;
        DataTypes::UnsignedShortNR serverPort;
        DataTypes::VarIntNR nextState;
        HandshakePacket (DataTypes::VarIntNR const & protocolVersion, DataTypes::StringNR const & serverAddress, DataTypes::UnsignedShortNR const & serverPort, DataTypes::VarIntNR const & nextState)
        : protocolVersion (protocolVersion), serverAddress (serverAddress), serverPort (serverPort), nextState (nextState) {};
    public:
        static Packet* readFrom (Network::RawClientConnector & clientConnector) {
            return new HandshakePacket (
                DataTypes::VarInt::readFrom (clientConnector).nativeRepresentation,
                DataTypes::String::readFrom (clientConnector).nativeRepresentation,
                DataTypes::UnsignedShort::readFrom (clientConnector).nativeRepresentation,
                DataTypes::VarInt::readFrom (clientConnector).nativeRepresentation
            );
        }
        static void handle (Packet* packet, Network::Client & client) {
            auto handshakePacket = (HandshakePacket*) packet;
            std::cout << "handling handshake packet, proto ver " << handshakePacket->protocolVersion << ", server addr " << handshakePacket->serverAddress << ", server port " << handshakePacket->serverPort << ", next state " << handshakePacket->nextState << std::endl;
        }
    };
}