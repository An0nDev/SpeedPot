#include "PongPacket.hpp"
#include "../../../Writer.hpp"

namespace SpeedPot::Packet::Packets::Clientbound::Status {
    const DataTypes::VarIntNR PongPacket::ID = 0x01;
    void PongPacket::sendTo (Network::RawClientConnector & clientConnector, Network::Client & client) {
        Writer::writeTo (clientConnector, PongPacket::ID, {
            DataTypes::Long::toBinaryRepresentation (payload)
        });
    }
}