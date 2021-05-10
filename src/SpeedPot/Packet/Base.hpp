#pragma once

#include <iostream>

#include "../DataTypes/VarInt.hpp"
#include "../DataTypes/String.hpp"
#include "../Network/RawClientConnector.hpp"
#include "../Network/Client.hpp"
#include "Common.hpp"

namespace SpeedPot::Packet {
    class Packet {
    public:
        static Packet* readFrom (Network::RawClientConnector & clientConnector) {
            return new Packet ();
        };
        static void handle (Packet* packet, Network::Client & client) {
            std::cout << "woo! called" << std::endl;
            throw std::runtime_error ("shit went down");
        };
        ~Packet () {
            std::cout << "called ~Packet" << std::endl;
        }
    };
}
