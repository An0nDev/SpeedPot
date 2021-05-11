#pragma once

#include "../../../Base.hpp"
#include "../../../../DataTypes/VarInt.hpp"
#include "../../../../DataTypes/String.hpp"
#include "../../../../DataTypes/Natives.hpp"

namespace SpeedPot::Packet::Packets::Serverbound::Handshaking {
    class HandshakePacket : public Packet {
        DataTypes::VarIntNR protocolVersion;
        DataTypes::StringNR serverAddress;
        DataTypes::UnsignedShortNR serverPort;
        DataTypes::VarIntNR nextState;
        HandshakePacket (DataTypes::VarIntNR const & protocolVersion, DataTypes::StringNR const & serverAddress, DataTypes::UnsignedShortNR const & serverPort, DataTypes::VarIntNR const & nextState);
    public:
        static const DataTypes::VarIntNR ID;
        static Packet* readFrom (Network::RawClientConnector & clientConnector);
        static void handle (Packet* packet, Network::Client & client);
    };
}