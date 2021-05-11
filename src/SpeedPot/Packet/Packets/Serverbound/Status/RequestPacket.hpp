#pragma once

#include "../../../Base.hpp"

namespace SpeedPot::Packet::Packets::Serverbound::Status {
    class RequestPacket : public Packet {
        RequestPacket ();
    public:
        static const DataTypes::VarIntNR ID;
        static Packet* readFrom (Network::RawClientConnector & clientConnector);
        static void handle (Packet* packet, Network::Client & client);
    };
}