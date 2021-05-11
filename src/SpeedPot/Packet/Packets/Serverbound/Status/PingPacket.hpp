#pragma once

#include "../../../Base.hpp"
#include "../../../../DataTypes/Natives.hpp"

namespace SpeedPot::Packet::Packets::Serverbound::Status {
    class PingPacket : public Packet {
        DataTypes::LongNR payload;
        PingPacket (DataTypes::LongNR const & payload);
    public:
        static const DataTypes::VarIntNR ID;
        static Packet* readFrom (Network::RawClientConnector & clientConnector);
        static void handle (Packet* packet, Network::Client & client);
    };
}