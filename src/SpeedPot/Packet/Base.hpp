#pragma once

#include <iostream>

#include "../DataTypes/VarInt.hpp"
#include "../Network/RawClientConnector.hpp"

namespace SpeedPot::Network {
    class Client;
}

namespace SpeedPot::Packet {
    class Packet {
        // serverbound packets should have a private constructor (called by readFrom)
    public:
        // all packets must have this (used in List, sendTo)
        static const DataTypes::VarIntNR ID;

        // must be implemented by serverbound packets
        static Packet* readFrom (Network::RawClientConnector & clientConnector) = delete;
        static void handle (Packet* packet, Network::Client & client) = delete;

        // clientbound packets should have a public constructor (called from user code)

        virtual ~Packet () {};
    };
}
